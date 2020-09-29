package model

import "testing"

func TestFormatString(t *testing.T) {
	input := []string{
		"a b", "a-b", "a - b", "ab-bc", "ab bc",
	}
	expected := []string{
		"A B", "A-B", "A - B", "Ab-Bc", "Ab Bc",
	}

	for i, v := range input {
		s := formatString(v)
		if expected[i] != s {
			t.Errorf("strings mismatch: %s - %s", expected[i], s)
		}
	}
}
