package config

type configurer struct {
	serverPort     string
	suggestionSize int
	suggestionFile string
}

func (c *configurer) ServerPort() string {
	return c.serverPort
}

func (c *configurer) SuggestionFile() string {
	return c.suggestionFile
}

func (c *configurer) MaxSuggestionSize() int {
	return c.suggestionSize
}
