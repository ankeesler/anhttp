package main

import (
	"log"

	"github.com/ankeesler/anhttp"
)

func main() {
	log.Printf("ListenAndServe returned: %s", anhttp.ListenAndServe(&anhttp.Config{}).Error())
}
