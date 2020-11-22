package LeetCode

import (
    "fmt"
    "testing"
)

func TestIsAnagram(t *testing.T) {
    var strS, strT string = "anagram", "nagaram"
    fmt.Printf("\"%s\" is anagram of \"%s\": %t", strS, strT, isAnagram(strS, strT))
}