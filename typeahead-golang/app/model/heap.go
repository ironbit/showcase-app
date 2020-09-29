package model

import "sketch-app/typeahead-golang/app/data"

type suggestionHeap []*data.Suggestion

func (sh suggestionHeap) Len() int {
	return len(sh)
}

func (sh suggestionHeap) Less(i, j int) bool {
	return sh[i].Less(sh[j])
}

func (sh suggestionHeap) Swap(i, j int) {
	sh[i], sh[j] = sh[j], sh[i]
}

func (sh *suggestionHeap) Push(s interface{}) {
	*sh = append(*sh, s.(*data.Suggestion))
}

func (sh *suggestionHeap) Pop() interface{} {
	s := (*sh)[len(*sh)-1]
	*sh = (*sh)[:len(*sh)-1]
	return s
}
