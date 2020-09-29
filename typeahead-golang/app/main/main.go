package main

import (
	"sketch-app/typeahead-golang/app/config"
	"sketch-app/typeahead-golang/app/core"
	"sketch-app/typeahead-golang/app/handler"
	"sketch-app/typeahead-golang/app/model"
	"sketch-app/typeahead-golang/app/server"
)

func main() {
	// create factories
	modelFactory := model.MakeFactory()
	handlerFactory := handler.MakeFactory()
	handlerFactory.SetModelFactory(modelFactory)

	// initialize model
	model.CreateContainer(config.Configurer.MaxSuggestionSize())
	model.PopulateContainerFile(config.Configurer.SuggestionFile())

	// create server
	server := server.New()

	// configure server
	url := core.Host + ":" + config.Configurer.ServerPort()
	server.SetServerAddress(url)
	server.SetHandlerFactory(handlerFactory)

	// run server
	server.Run()
}
