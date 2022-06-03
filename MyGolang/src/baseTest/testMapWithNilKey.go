package main
import (
	"fmt"
)

type myStruct struct {
	str string
}

func getMapValue(key string) string {
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
	fmt.Println(getMapValue("A"))
	s := myStruct{}
	fmt.Println(getMapValue(s.str))
	fmt.Println(getMapValue("B"))
}
