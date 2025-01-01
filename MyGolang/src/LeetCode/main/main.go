package main

import "fmt"

func validStrings(n int) []string {
	tmp := make([]string, 2)
	tmp[0] = "0"
	tmp[1] = "1"
	var l int = 0

	for i := 2; i <= n; i++ {
		l = i - 2
		tmpAdd := make([]string, 0)
		for _, s := range tmp {
			// try add "0"
			if s[l] != '0' {
				tmpAdd = append(tmpAdd, s + "0")
			}
			// try add "1"
			tmpAdd = append(tmpAdd, s + "1")
		}
		tmp = tmpAdd
	}
	return tmp
}

func main() {
	fmt.Println("hello world")

	result := validStrings(3)
	for _, v := range result {
		fmt.Println("'", v, "'")
	}
}
