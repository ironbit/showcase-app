package server

import (
	"log"
	"net/http"

	"github.com/gorilla/mux"

	"sketch-app/typeahead-golang/app/core"
	"sketch-app/typeahead-golang/app/handler"
)

// New factory for a new server.
func New() *Server {
	return &Server{}
}

// Server is the structure used for running a HTTP server.
type Server struct {
	address string
	router  *mux.Router
	server  *http.Server
	factory handler.Factory
}

// Run configures and executes the server.
func (s *Server) Run() {
	// config handlers
	s.configHandlers()

	// config server
	s.server = &http.Server{
		Addr:    s.address,
		Handler: s.router,
	}

	// run server
	err := s.server.ListenAndServe()
	if err != nil {
		log.Println(err.Error())
	}
}

// SetServerAddress sets the server address: "host:port".
func (s *Server) SetServerAddress(address string) {
	s.address = address
}

// SetHandlerFactory sets the factory for the server handlers.
func (s *Server) SetHandlerFactory(factory handler.Factory) {
	s.factory = factory
}

func (s *Server) configHandlers() {
	// create new mux router
	s.router = mux.NewRouter()

	// GET /typeahead/
	// curl -X GET http://localhost:12345/typeahead/
	service := s.factory.Create(core.GetAllAliasSuggestionKind)
	s.router.
		Handle(service.Path(), service).
		Methods(service.Methods())

	// GET /typeahead
	// curl -X GET http://localhost:12345/typeahead
	service = s.factory.Create(core.GetAllSuggestionKind)
	s.router.
		Handle(service.Path(), service).
		Methods(service.Methods())

	// GET /typeahead/{prefix}
	// curl -X GET http://localhost:12345/typeahead/ja
	service = s.factory.Create(core.GetPrefixSuggestionKind)
	s.router.
		Handle(service.Path(), service).
		Methods(service.Methods())

	// POST /typeahead
	// curl -X POST -H "Content-Type: application/json" -d '{"name": "Joanna"}' http://localhost:12345/typeahead
	service = s.factory.Create(core.SetSuggestionKind)
	s.router.
		Handle(service.Path(), service).
		Methods(service.Methods())
}
