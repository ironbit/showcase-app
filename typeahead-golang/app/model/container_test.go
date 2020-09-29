package model

import (
	"testing"

	"sketch-app/typeahead-golang/app/data"
)

func TestSuggesterPopulate(t *testing.T) {
	// parameters
	const size = 10
	var data = []*data.Suggestion{
		{Name: "aa", Times: 1},
		{Name: "ab", Times: 2},
		{Name: "ac", Times: 2},
		{Name: "ad", Times: 3},
		{Name: "ae", Times: 3},
	}

	// populate data
	CreateContainer(size)
	container.populate(data)

	// verify data
	for _, d := range data {
		times, ok := container.trie.Get(d.Name)
		if !ok {
			t.Errorf("Name not found %s", d.Name)
		}
		if d.Times != times.(int) {
			t.Errorf("Times mismatch: %d - %d", d.Times, times.(int))
		}
	}
}

func TestSuggesterUpdate(t *testing.T) {
	// parameters
	const size = 10
	var dat = []*data.Suggestion{
		{Name: "aa", Times: 1},
		{Name: "ab", Times: 2},
		{Name: "ac", Times: 2},
		{Name: "ad", Times: 3},
		{Name: "ae", Times: 3},
	}

	// populate data
	CreateContainer(size)
	container.populate(dat)

	for _, d := range dat {
		// perform operation
		u, err := container.update(d.Name)

		// verify data
		if err != nil {
			t.Errorf("Update: %s", err)
		}
		if u.Name != d.Name {
			t.Errorf("name mismatch: %s - %s", d.Name, u.Name)
		}
		if u.Times != (d.Times + 1) {
			t.Errorf("Update: times mismatch: %d - %d", d.Times, u.Times)
		}
	}
}

func TestSuggesterRetrieve(t *testing.T) {
	// parameters
	const size = 2
	dat := []*data.Suggestion{
		{Name: "aa", Times: 1},
		{Name: "ab", Times: 2},
		{Name: "ac", Times: 4},
		{Name: "ad", Times: 3},
		{Name: "az", Times: 5},
	}
	ans := []*data.Suggestion{
		{Name: "az", Times: 5},
		{Name: "ac", Times: 4},
	}

	// populate data
	CreateContainer(size)
	container.populate(dat)

	// perform operation
	test := container.retrieve("a")

	// verify test size
	if len(ans) != len(test) {
		t.Errorf("size mismatch %d - %d", len(ans), len(test))
	}

	// verify answer
	for i, v := range test {
		if ans[i].Name != v.Name {
			t.Errorf("name mismatch: %s - %s", ans[i].Name, v.Name)
		}
		if ans[i].Times != v.Times {
			t.Errorf("times mismatch: %d - %d", ans[i].Times, v.Times)
		}
	}
}

func TestSuggesterRetrieveWithEqualTimes(t *testing.T) {
	// parameters
	const size = 2
	dat := []*data.Suggestion{
		{Name: "aa", Times: 2},
		{Name: "ab", Times: 2},
		{Name: "ac", Times: 2},
		{Name: "ad", Times: 2},
		{Name: "az", Times: 2},
	}
	ans := []*data.Suggestion{
		{Name: "aa", Times: 2},
		{Name: "ab", Times: 2},
	}

	// populate data
	CreateContainer(size)
	container.populate(dat)

	// perform operation
	test := container.retrieve("a")

	// verify test size
	if len(ans) != len(test) {
		t.Errorf("size mismatch %d - %d", len(ans), len(test))
	}

	// verify answer
	for i, v := range test {
		if ans[i].Name != v.Name {
			t.Errorf("name mismatch: %s - %s", ans[i].Name, v.Name)
		}
		if ans[i].Times != v.Times {
			t.Errorf("times mismatch: %d - %d", ans[i].Times, v.Times)
		}
	}
}

func TestSuggesterRetrieveWithExactMatch(t *testing.T) {
	// parameters
	const size = 3
	var dat = []*data.Suggestion{
		{Name: "aa", Times: 1},
		{Name: "ab", Times: 1},
		{Name: "ac", Times: 2},
		{Name: "ad", Times: 2},
		{Name: "ba", Times: 3},
		{Name: "a", Times: 1},
	}
	ans := []*data.Suggestion{
		{Name: "a", Times: 1},
		{Name: "ac", Times: 2},
		{Name: "ad", Times: 2},
	}

	// populate data
	CreateContainer(size)
	container.populate(dat)

	// perform operation
	test := container.retrieve("a")

	// verify test size
	if len(ans) != len(test) {
		t.Errorf("size mismatch %d - %d", len(ans), len(test))
	}

	// verify answer
	for i, v := range test {
		if ans[i].Name != v.Name {
			t.Errorf("name mismatch: %s - %s", ans[i].Name, v.Name)
		}
		if ans[i].Times != v.Times {
			t.Errorf("times mismatch: %d - %d", ans[i].Times, v.Times)
		}
	}
}

func TestSuggesterRetrieveFromRoot(t *testing.T) {
	// parameters
	const size = 3
	var dat = []*data.Suggestion{
		{Name: "aa", Times: 1},
		{Name: "ab", Times: 1},
		{Name: "ac", Times: 2},
		{Name: "ad", Times: 2},
		{Name: "ba", Times: 3},
		{Name: "a", Times: 2},
	}
	ans := []*data.Suggestion{
		{Name: "ba", Times: 3},
		{Name: "a", Times: 2},
		{Name: "ac", Times: 2},
	}

	// populate data
	CreateContainer(size)
	container.populate(dat)

	// perform operation
	test := container.retrieve("")

	// verify test size
	if len(ans) != len(test) {
		t.Errorf("size mismatch %d - %d", len(ans), len(test))
	}

	// verify answer
	for i, v := range test {
		if ans[i].Name != v.Name {
			t.Errorf("name mismatch: %s - %s", ans[i].Name, v.Name)
		}
		if ans[i].Times != v.Times {
			t.Errorf("times mismatch: %d - %d", ans[i].Times, v.Times)
		}
	}
}
