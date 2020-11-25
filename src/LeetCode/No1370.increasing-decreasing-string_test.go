package LeetCode

import (
    "fmt"
    "testing"
)

func TestSortString(t *testing.T) {
    var s string = "aaaabbbbcccc"
    fmt.Printf("The ans of sort string(\"%s\") is:\"%s\"\n", s, sortString(s))
}