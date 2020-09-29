package model

import "sketch-app/typeahead-golang/app/core"

func makeFactory() Factory {
	return &factory{}
}

type factory struct{}

func (f *factory) Create(kind core.Kind) Interface {
	switch kind {
	case core.GetAllAliasSuggestionKind:
		return &modelGetSuggestion{}
	case core.GetAllSuggestionKind:
		return &modelGetSuggestion{}
	case core.GetPrefixSuggestionKind:
		return &modelGetSuggestion{}
	case core.SetSuggestionKind:
		return &modelSetSuggestion{}
	}
	return nil
}
