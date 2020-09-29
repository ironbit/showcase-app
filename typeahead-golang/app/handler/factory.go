package handler

import (
	"sketch-app/typeahead-golang/app/core"
	"sketch-app/typeahead-golang/app/model"
)

func makeFactory() Factory {
	return &factory{}
}

type factory struct {
	factory model.Factory
}

func (f *factory) Create(kind core.Kind) Interface {
	switch kind {
	case core.GetAllAliasSuggestionKind:
		return &handlerGetAllAliasSuggestion{m: f.factory.Create(core.GetAllAliasSuggestionKind)}
	case core.GetAllSuggestionKind:
		return &handlerGetAllSuggestion{m: f.factory.Create(core.GetAllSuggestionKind)}
	case core.GetPrefixSuggestionKind:
		return &handlerGetPrefixSuggestion{m: f.factory.Create(core.GetPrefixSuggestionKind)}
	case core.SetSuggestionKind:
		return &handlerSetSuggestion{m: f.factory.Create(core.SetSuggestionKind)}
	}
	return nil
}

func (f *factory) SetModelFactory(factory model.Factory) {
	f.factory = factory
}
