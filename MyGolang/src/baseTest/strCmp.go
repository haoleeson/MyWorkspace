package main

import (
	"fmt"
	"strings"
)

func cmpStr(s, t string, ignoreCase bool) bool {
	if len(s) != len(t) {
		return false
	}

	var ss string
	var tt string
	if ignoreCase {
		ss, tt = strings.ToLower(s), strings.ToLower(s)
	} else {
		ss, tt = s, t
	}

	for i := 0; i < len(ss); i++ {
		if ss[i] != tt[i] {
			return false
		}
	}
	return true
}

func main() {
	s := "hello world"
	t := "HELLO world"

	fmt.Println("compare s and t: ", cmpStr(s, t, false))
	fmt.Println("compare s and t ignore case: ", cmpStr(s, t, true))
}
