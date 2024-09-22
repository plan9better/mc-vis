package main
import (
	"net/http"
	"net"
	"log"
	"fmt"
	"os"

	"github.com/wasmerio/wasmer-go/wasmer"
)

func callWasm(){
	// Read the WASM file
	wasmBytes, err := os.ReadFile("../static/index.wasm")
	if err != nil {
		log.Fatal(err)
	}

	// Instantiate the WebAssembly runtime
	engine := wasmer.NewEngine()
	store := wasmer.NewStore(engine)

	// Compile the module
	module, err := wasmer.NewModule(store, wasmBytes)
	if err != nil {
		log.Fatal(err)
	}

	// Create an empty import object
	importObject := wasmer.NewImportObject()

	// Instantiate the WebAssembly module
	instance, err := wasmer.NewInstance(module, importObject)
	if err != nil {
		log.Fatal(err)
	}

	// Get the `add` exported function
	initFunc, err := instance.Exports.GetFunction("initBlocks")
	if err != nil {
		log.Fatal(err)
	}
	addFunc, err := instance.Exports.GetFunction("addBlock")
	if err != nil {
		log.Fatal(err)
	}

	// Call the `add` function with arguments 2 and 3
	result, err := initFunc(1)
	if err != nil {
		log.Fatal(err)
	}
	result, err = addFunc("Water -96 62 224")
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("Result: %v\n", result)
}

func handleConnections(ch chan []byte){
	listener, err := net.Listen("tcp", ":8337")
	if err != nil{
		log.Fatal("Could not start a tcp socket")
	}

	for{
		conn, err := listener.Accept();
		if err != nil{
			log.Println("Could not accept a connection")
		}
		go func(){
			for conn != nil {
				msg := make([]byte, 4096)
				_, err := conn.Read(msg)
				if err != nil {
					log.Printf("Error reading a msg from client: local: %s, remote: %s\n", conn.LocalAddr(), conn.RemoteAddr())
					conn.Close()
					return
				}
				ch<-msg
			}
		}()
	}


}

func fileServerHandler(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "../static"+ r.URL.Path)
}

func main() {
    http.HandleFunc("/", fileServerHandler)

    go func(){
	    ch := make(chan []byte)
	    go handleConnections(ch)
	    for{
		fmt.Printf("new message: %s\n", <-ch)
		fmt.Printf("initializing and adding block...\n")
		callWasm();
	    }
    }()

    log.Println("Server started at :8080")
    if err := http.ListenAndServe(":8080", nil); err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}
