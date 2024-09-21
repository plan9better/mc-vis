package main
import (
	"net/http"
	"net"
	"log"
	"fmt"
)

func handleConnections(ch<- chan []byte){
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
			msg := make([]byte, 1024)
			_, err := conn.Read(msg)
			if err != nil {
				log.Println("Error reading a msg from client: local: %s, remote: %s", conn.LocalAddr(), conn.RemoteAddr())
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
		fmt.Println("new message: %v", <-ch)
	    }
    }()

    log.Println("Server started at :8080")
    if err := http.ListenAndServe(":8080", nil); err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}
