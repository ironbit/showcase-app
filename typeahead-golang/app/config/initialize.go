package config

import (
	"log"
	"os"
	"strconv"
)

const (
	port             = "PORT"
	fileName         = "FILE_NAME"
	suggestionNumber = "SUGGESTION_NUMBER"
)

func init() {
	ps := os.Getenv(port)
	if ps == "" {
		log.Fatalf("Environment Variable %s not found", port)
	}

	fn := os.Getenv(fileName)
	if fn == "" {
		log.Fatalf("Environment Variable %s not found", fileName)
	}

	sn := os.Getenv(suggestionNumber)
	if sn == "" {
		log.Fatalf("Environment Variable %s not found", suggestionNumber)
	}

	si, err := strconv.Atoi(sn)
	if err != nil {
		log.Fatalf("%s must be a number: %s", suggestionNumber, err)
	}

	Configurer = &configurer{
		serverPort:     ps,
		suggestionSize: si,
		suggestionFile: fn,
	}
}
