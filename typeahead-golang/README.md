# Typeahead - Golang

## Description
It's a server implementation of the typeahead functionality, and the interface of the server is a Rest API.

The typeahead functionality is understood as a suggestion list of values ordered by specific criteria.

The client sends a string, which could be a complete word or part of it, and the server returns a list of names that begins or are equal to the string sent by the client. The list is ordered based on some criteria.

## Folder Structure
* **api**
It contains an OpenAPI file description in `yaml` of the Rest API.

* **app**
It contains the application written in golang, and it's organized in different folders.

* **data**
The 'names.json' file contains a list of suggestions, which it's added when the application starts.

* **docker**
It contains the `Dockerfile` used to deploy the application.

## Functionality
### Concepts
* prefix: parameter given by the client.
* suggestion: structure that contains a 'name' (string) and a 'times' (int).
* list: a group of suggestions ordered by an order criteria returned by the server.

### Requirements
* In case of an error, the server will return the 400 HTTP status response.

#### Retrieve Names
* The order criteria are:
  * suggestion is greater when 'times' is greater.
  * In case 'times' are equal, it is considered a suggestion greater when 'names' are compared in ascending order.
* The prefix needs to match the beginning of the name or the whole name in order to consider the suggestion in the list.
* In case the prefix match a name, the name will be first in the list.
* In case the prefix does not match any name, the list is empty.
* The list will have a maximum size based on the environmental variable (SUGGESTION_NUMBER).

#### Update Names
* It consists in increment by one the 'times' value when the name match exactly the 'name' parameter.
* The only parameter of the request is the 'name' parameter.
* It returns the suggestion with the value updated.

## Web API
The definition of the [Rest API](./api/api.yaml) is defined in the yaml document (api/api.yaml).

##### **GET /typeahead**
curl -X GET http://localhost:12345/typeahead
```
[{"name":"Fidela","times":999},{"name":"Gert","times":999},{"name":"Guinna","times":999},{"name":"Jenica","times":999},{"name":"Merle","times":999}]
```

##### **GET /typeahead/{prefix}**
curl -X GET http://localhost:12345/typeahead/ja
```
[{"name":"Janetta","times":973},{"name":"Janel","times":955},{"name":"Jazmin","times":951},{"name":"Janette","times":947},{"name":"Janet","times":936}]
```

##### **POST /typeahead**
curl -X POST -H "Content-Type: application/json" -d '{"name": "Janetta"}' http://localhost:12345/typeahead
```
{"name":"Janetta","times":974}
```

## Implementation
It uses a radix tree and a heap in order to fulfill the typeahead functionality.

In a request, it walks through the radix tree using the prefix given by the request, and it puts the suggestion into the heap in each walk. When it finishes, the heap contains the list (ordered) that will be returned by the server.

Consider k the maximum length of the names in the set.
Consider n the total number names with the same prefix.
Consider q the size of the queue.

The complexity of search operation in the radix tree is `O(k)` and the insert operation in the heap is `O(lg(q))`; that's why the time complexity of the functionality is `O(nk lg(q))`. The heap size is a fixed value (SUGGESTION_NUMBER), so the time complexity is `O(nk)`.

The worst and common case is when the prefix is an empty string; for that case will be useful a cache structure (not implemented).

## Execution

### Configuration
* Resources
  * data/names.json
* Environmental variables
  * PORT: the port of the url for the server.
  * FILE_NAME: path of the file that contains the names (data).
  * SUGGESTION_NUMBER: Define the maximum number of names in the list returned by the server.

### Using Local Machine
1. Set the following enviromental variables:
```bash
$ export PORT=12345
$ export FILE_NAME=../data/names.json
$ export SUGGESTION_NUMBER=5
```

2. In 'typeahead-golang/app' folder, execute the application:
```bash
$ go run main/main.go
```

### Using Virtual Machine (Docker)
1. In the 'typeahead-golang' folder, execute the following line in bash in order to create an image of the application:
```bash
$ docker build -f docker/Dockerfile -t app-web .
```

2. Start the container:
```bash
$ docker run -p 12345:12345 app-web
```

## Packages Dependencies
* github.com/armon/go-radix
* github.com/gorilla/mux
