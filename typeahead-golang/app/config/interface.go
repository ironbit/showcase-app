package config

// Interface contains the different parameters for the Application.
type Interface interface {
	// ServerPort is the port value for the server.
	ServerPort() string

	// SuggestionFile is the name of the file where the initial data is
	// stored.
	SuggestionFile() string

	// MaxSuggestionSize is the maximum number of suggestions that the
	// application can bring on a request.
	MaxSuggestionSize() int
}
