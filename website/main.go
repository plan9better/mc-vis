package main
import (
	"net/http"
	"encoding/json"
	"net"
	"log"
	"fmt"
	"os"
	"sync"

	"github.com/wasmerio/wasmer-go/wasmer"
)

var addBlockRequested = false;
type coords struct{
	x int
	y int
	z int
}
type blockList struct{
	mu sync.Mutex
	blocks map[coords]string
}

func handleConnections(bList *blockList){
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
				var c coords
				var name string
				fmt.Sscanf(string(msg),"%s %d %d %d" , &name, &c.x, &c.y, &c.z); 
				bList.blocks[c] = name;
			}
		}()
	}


}

func fileServerHandler(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "../static"+ r.URL.Path)
}


func main() {
    var bList blockList;

    http.HandleFunc("/", fileServerHandler)
    http.HandleFunc("/trigger", func(w http.ResponseWriter, r *http.Request) {
		addBlockRequested = true
		w.WriteHeader(http.StatusOK)
    })
    http.HandleFunc("/poll", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		json.NewEncoder(w).Encode(map[string]bool{"addBlock": addBlockRequested})
		addBlockRequested = false
    })

    go handleConnections(&bList);

    log.Println("Server started at :8080")
    if err := http.ListenAndServe(":8080", nil); err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}
