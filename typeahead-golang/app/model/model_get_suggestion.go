package model

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
)

type modelGetSuggestion struct{}

func (*modelGetSuggestion) Process(w http.ResponseWriter, param interface{}) {
	name, err := processString(param)
	if err != nil {
		msg := fmt.Sprintf("can't obtain param %s", err)
		http.Error(w, msg, http.StatusBadRequest)
		log.Println("modelGetSuggestion: " + msg)
		return
	}

	suggestions := container.retrieve(name)
	ans, err := json.Marshal(suggestions)
	if err != nil {
		ans = make([]byte, 0)
		log.Printf("json marshal: %s", err)
	}
	w.Header().Set("Content-Type", "application/json")
	w.Write(ans)
}
