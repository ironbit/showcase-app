package data

import "strings"

// Suggestion data type.
type Suggestion struct {
	Name  string `json:"name"`
	Times int    `json:"times"`
}

// Less is used to compare between Suggestion elements.
func (lhs *Suggestion) Less(rhs *Suggestion) bool {
	// compare Times
	if lhs.Times < rhs.Times {
		return true
	}
	if lhs.Times > rhs.Times {
		return false
	}

	// compare Names (when Times are equal)
	value := strings.Compare(lhs.Name, rhs.Name)
	// case when lhs < rhs
	if value > 0 {
		return true
	}
	// case when lhs == rhs or lhs > rhs
	return false
}
