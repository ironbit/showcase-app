package model

import (
	"net/http"

	"sketch-app/typeahead-golang/app/core"
)

// Interface is the interface used by the models.
type Interface interface {
	Process(w http.ResponseWriter, param interface{})
}

// Factory is the interface used to create the models.
type Factory interface {
	Create(core.Kind) Interface
}

// MakeFactory is the package variable used to create a model factory.
var MakeFactory func() Factory
