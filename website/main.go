package main
import (
	"net/http"
	"encoding/json"
	"net"
	"log"
	"fmt"
	"sync"
)

var addBlockRequested = false;
type blockList struct{
	mu sync.Mutex
	blocks []string
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
		log.Println("Accepted a connection");
		go func(){
			for conn != nil {
				msg := make([]byte, 128)
				_, err := conn.Read(msg)
				log.Println("MSG: ", msg);
				if err != nil {
					log.Printf("Error reading a msg from client: local: %s, remote: %s\n", conn.LocalAddr(), conn.RemoteAddr())
					conn.Close()
					return
				}
				var msgStr string
				for i := 0; msg[i] != '\u0000'; i++{
					msgStr += string(msg[i]);
				}

				bList.mu.Lock();
				bList.blocks = append(bList.blocks, msgStr);
				bList.mu.Unlock();
				fmt.Println("in func: ", bList.blocks);
			}
		}()
	}


}

func fileServerHandler(w http.ResponseWriter, r *http.Request) {
	http.ServeFile(w, r, "../static"+ r.URL.Path)
}


func main() {
    var bList blockList;
    bList.blocks = make([]string, 0);

    http.HandleFunc("/", fileServerHandler)
    http.HandleFunc("/trigger", func(w http.ResponseWriter, r *http.Request) {
		addBlockRequested = true
		w.WriteHeader(http.StatusOK)
    })
    http.HandleFunc("/poll", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")

		bList.mu.Lock();
		json.NewEncoder(w).Encode(bList.blocks);
		bList.blocks = make([]string, 0);
		bList.mu.Unlock();

		fmt.Println("in main: ", bList.blocks);
		addBlockRequested = false
    })

    go handleConnections(&bList);

    log.Println("Server started at :8080")
    if err := http.ListenAndServe(":8080", nil); err != nil {
        log.Fatal("ListenAndServe: ", err)
    }
}
