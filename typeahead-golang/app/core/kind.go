package core

// Kind is an alias type.
type Kind int

const (
	// GetAllSuggestionKind token: GET /typeahead
	GetAllSuggestionKind Kind = iota

	// GetAllAliasSuggestionKind token: GET /typeahead/
	GetAllAliasSuggestionKind

	// GetPrefixSuggestionKind token: GET /typeahead/{prefix}
	GetPrefixSuggestionKind

	// SetSuggestionKind token: POST /typeahead
	SetSuggestionKind
)
