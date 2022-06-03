package main
import (
	"fmt"
)

type myStruct struct {
	str string
}

func getMapVlaue(key string) string {
	str2StrMap := map[string]string{
		"A": "aaa",
		"B": "bbb",
	}

	if val, ok := str2StrMap[key]; ok {
		return val
	}
	return ""
}


func main() {
	fmt.Println(getMapVlaue("A"))
	s := myStruct{}
	fmt.Println(getMapVlaue(s.str))
	fmt.Println(getMapVlaue("B"))
}
