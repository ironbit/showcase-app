package model

import (
	"container/heap"

	"sketch-app/typeahead-golang/app/data"
)

func newWalker(name string, size int) *walker {
	h := &suggestionHeap{}
	heap.Init(h)

	return &walker{
		same: nil,
		heap: h,
		name: name,
		size: size,
	}
}

type walker struct {
	same *data.Suggestion
	heap *suggestionHeap
	name string
	size int
}

func (w *walker) walkTrie(s string, v interface{}) bool {
	if s == w.name {
		w.size--
		w.same = &data.Suggestion{Name: s, Times: v.(int)}
	} else {
		heap.Push(w.heap, &data.Suggestion{Name: s, Times: v.(int)})
	}
	if w.size < w.heap.Len() {
		heap.Pop(w.heap)
	}
	return false
}

func (w *walker) createArray() []*data.Suggestion {
	heapSize := w.heap.Len()
	arraySize := w.heap.Len()
	if w.same != nil {
		arraySize++
	}

	ans := make([]*data.Suggestion, arraySize)
	for i := 0; i < heapSize; i++ {
		ans[arraySize-1-i] = heap.Pop(w.heap).(*data.Suggestion)
	}

	if w.same != nil {
		ans[0] = w.same
	}

	return ans
}
