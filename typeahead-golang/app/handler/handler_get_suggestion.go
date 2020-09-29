package handler

import (
	"net/http"
	"sketch-app/typeahead-golang/app/model"

	"github.com/gorilla/mux"

	"sketch-app/typeahead-golang/app/core"
)

type handlerGetAllSuggestion struct {
	m model.Interface
}

func (*handlerGetAllSuggestion) Path() string {
	return core.BasePath
}

func (*handlerGetAllSuggestion) Methods() string {
	return http.MethodGet
}

func (hg *handlerGetAllSuggestion) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	hg.m.Process(w, "")
}

type handlerGetAllAliasSuggestion struct {
	m model.Interface
}

func (*handlerGetAllAliasSuggestion) Path() string {
	return core.BasePath + "/"
}

func (*handlerGetAllAliasSuggestion) Methods() string {
	return http.MethodGet
}

func (hg *handlerGetAllAliasSuggestion) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	hg.m.Process(w, "")
}

type handlerGetPrefixSuggestion struct {
	m model.Interface
}

func (*handlerGetPrefixSuggestion) Path() string {
	return core.BasePath + "/{prefix}"
}

func (*handlerGetPrefixSuggestion) Methods() string {
	return http.MethodGet
}

func (hg *handlerGetPrefixSuggestion) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	hg.m.Process(w, vars["prefix"])
}
