package model

import (
	"bytes"
	"io/ioutil"
	"log"
	"strconv"

	"sketch-app/typeahead-golang/app/data"
)

// CreateContainer creates a new container variable.
func CreateContainer(maxSuggestionSize int) {
	container = newContainer(maxSuggestionSize)
}

// PopulateContainerValues populates the initial information
// to the container variable using an array of data.Suggestion
// as input.
func PopulateContainerValues(values []*data.Suggestion) {
	for _, v := range values {
		n := formatString(v.Name)
		d := &data.Suggestion{
			Name:  n,
			Times: v.Times,
		}
		container.store(d)
	}
	log.Printf("data populated: %d\n", len(values))
}

// PopulateContainerFile populates the initial information
// to the container variable using a file as input.
func PopulateContainerFile(fileName string) {
	// read file
	b, err := ioutil.ReadFile(fileName)
	if err != nil {
		log.Fatalf("file not found: %s\n", fileName)
	}

	// erase brackets
	t1 := byte('{')
	i1 := 0
	for i1 < len(b) && b[i1] != t1 {
		i1++
	}
	t2 := byte('}')
	i2 := len(b) - 1
	for 0 < i2 && b[i2] != t2 {
		i2--
	}

	if i2 < i1 {
		log.Fatalf("read file - indexes mismatch: %d - %d\n", i1, i2)
	}

	b = b[i1+1 : i2]

	// read each pair of data
	counter := 0
	ba := bytes.Split(b, []byte(","))
	for _, v := range ba {
		// split the byte array into ("name") and (number).
		vv := bytes.Split(v, []byte(":"))

		// obtain the string without quotation marks.
		name := string(vv[0][1 : len(vv[0])-1])
		name = formatString(name)

		// obtain the number
		times, err := strconv.Atoi(string(vv[1]))
		if err != nil {
			log.Fatalf("unable to convert byte to number: %s", err)
		}

		// store data.Suggestion into the container
		counter++
		container.store(&data.Suggestion{Name: name, Times: times})
	}

	log.Printf("data populated: %d\n", counter)
}
