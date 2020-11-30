package LeetCode

import (
    "fmt"
    "testing"
)

func TestReorganizeString(t *testing.T) {
    strs := []string{"aab", "aaab", "", "as", "aaabbbcc", "aaaabbb"}
    for i, str := range strs[:] {
        fmt.Printf("Str%d.\"%s\", ans is: \"%s\"\n", i, str, reorganizeString(str))
    }
}