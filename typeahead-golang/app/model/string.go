package model

import (
	"errors"
	"strings"
	"unicode"
)

func processString(param interface{}) (string, error) {
	name, ok := param.(string)
	if !ok {
		return "", errors.New("can't convert to string")
	}
	return formatString(name), nil
}

func formatString(input string) string {
	var sb strings.Builder
	isUpper := true
	for _, r := range input {
		switch r {
		case '-', ' ':
			sb.WriteRune(r)
			isUpper = true
		default:
			if isUpper {
				isUpper = false
				sb.WriteRune(unicode.ToUpper(r))
			} else {
				sb.WriteRune(unicode.ToLower(r))
			}
		}
	}
	return sb.String()
}
