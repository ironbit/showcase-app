package model

import (
	"fmt"
	"log"
	"sketch-app/typeahead-golang/app/data"
	"sync"

	"github.com/armon/go-radix"
)

// container is a 'static' variable used by the models.
var container *markContainer

// newContainer is used to create a new suggester object.
func newContainer(size int) *markContainer {
	t := radix.New()
	return &markContainer{trie: t, size: size}
}

type markContainer struct {
	mutex sync.RWMutex
	trie  *radix.Tree
	size  int
}

// populate is used to store data into the radix tree.
func (mc *markContainer) populate(s []*data.Suggestion) {
	mc.mutex.Lock()
	defer mc.mutex.Unlock()

	for _, d := range s {
		mc.store(d)
	}
}

// update is used to increment by one an element in the radix tree.
func (mc *markContainer) update(name string) (*data.Suggestion, error) {
	mc.mutex.Lock()
	defer mc.mutex.Unlock()

	s, err := mc.fetch(name)
	if err != nil {
		log.Print(err)
		return nil, err
	}

	s.Times++
	mc.store(s)
	return s, nil
}

// retrieve is used to load a group of elements from the radix tree.
// The elements are sorted based on the maximum value (times) and in
// the ascending order of the names in case the times are equal. In
// case of an exact match in the name, the element will be the first
// element of the array.
func (mc *markContainer) retrieve(s string) []*data.Suggestion {
	mc.mutex.RLock()
	defer mc.mutex.RUnlock()

	// create and config walker.
	// create a walker for each request.
	w := newWalker(s, mc.size)

	// visitor for the trie.
	// trie is not changed, only the walker is updated.
	mc.trie.WalkPrefix(s, w.walkTrie)

	// create answer stored in the walker.
	return w.createArray()
}

func (mc *markContainer) fetch(name string) (*data.Suggestion, error) {
	value, status := mc.trie.Get(name)
	if !status {
		return nil, fmt.Errorf("name not found: %s", name)
	}
	return &data.Suggestion{Name: name, Times: value.(int)}, nil
}

func (mc *markContainer) store(s *data.Suggestion) {
	mc.trie.Insert(s.Name, s.Times)
}
