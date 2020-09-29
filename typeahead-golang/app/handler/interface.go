package handler

import (
	"net/http"

	"sketch-app/typeahead-golang/app/core"
	"sketch-app/typeahead-golang/app/model"
)

// Interface is used to define a web handler.
type Interface interface {
	Path() string
	Methods() string
	ServeHTTP(w http.ResponseWriter, r *http.Request)
}

// Factory is used to create the different handlers.
type Factory interface {
	Create(core.Kind) Interface
	SetModelFactory(model.Factory)
}

// MakeFactory is a package variable used to create a
// a handler factory.
var MakeFactory func() Factory
