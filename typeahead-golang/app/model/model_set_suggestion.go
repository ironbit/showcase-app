package model

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
)

type modelSetSuggestion struct{}

func (*modelSetSuggestion) Process(w http.ResponseWriter, param interface{}) {
	name, err := processString(param)
	if err != nil {
		msg := fmt.Sprintf("can't obtain param %s", err)
		http.Error(w, msg, http.StatusBadRequest)
		log.Println("modelSetSuggestion: " + msg)
		return
	}

	out, err := container.update(name)
	if err != nil {
		msg := fmt.Sprintf("can't update %s: %s", name, err)
		http.Error(w, msg, http.StatusBadRequest)
		log.Println("modelSetSuggestion: " + msg)
		return
	}

	ans, err := json.Marshal(out)
	if err != nil {
		msg := fmt.Sprintf("can't marshal %s: %s", name, err)
		http.Error(w, msg, http.StatusBadRequest)
		log.Println("modelSetSuggestion: " + msg)
	}

	w.Header().Set("Content-Type", "application/json")
	w.Write(ans)
	w.WriteHeader(http.StatusOK)
}
