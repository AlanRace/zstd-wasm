package main

import (
	"flag"
	"log"
	"net/http"
)

func main() {
	addr := flag.String("addr", ":5555", "server address:port")
	directory := flag.String("d", ".", "the directory of static file to host")
	flag.Parse()

	http.Handle("/", http.FileServer(http.Dir(*directory)))

	fs := http.FileServer(http.Dir("../src"))
	http.Handle("/src/", http.StripPrefix("/src", fs))

	binfs := http.FileServer(http.Dir("../bin"))
	http.Handle("/bin/", http.StripPrefix("/bin", binfs))

	log.Printf("listening on %q...", *addr)
	log.Fatal(http.ListenAndServe(*addr, nil))
}
