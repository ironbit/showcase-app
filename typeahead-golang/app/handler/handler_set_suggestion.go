package handler

import (
	"encoding/json"
	"log"
	"net/http"

	"sketch-app/typeahead-golang/app/core"
	"sketch-app/typeahead-golang/app/data"
	"sketch-app/typeahead-golang/app/model"
)

type handlerSetSuggestion struct {
	m model.Interface
}

func (*handlerSetSuggestion) Path() string {
	return core.BasePath
}

func (*handlerSetSuggestion) Methods() string {
	return http.MethodPost
}

func (hs *handlerSetSuggestion) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	// verify the request header
	value := r.Header.Get("Content-Type")
	if value != "" && value != "application/json" {
		msg := "Content-Type header is not application/json"
		http.Error(w, msg, http.StatusBadRequest)
		log.Println("handlerSetSuggestion: " + msg)
		return
	}

	// process the input information
	len := r.ContentLength
	body := make([]byte, len)
	r.Body.Read(body)

	var name data.Name
	err := json.Unmarshal(body, &name)
	if err != nil {
		msg := "Request Body (name data) contains badly-formed JSON"
		http.Error(w, msg, http.StatusBadRequest)
		log.Println("handlerSetSuggestion: " + msg)
		return
	}

	// process request
	hs.m.Process(w, name.Name)
}
