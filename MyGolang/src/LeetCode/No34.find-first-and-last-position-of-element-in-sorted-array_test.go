package LeetCode

import "testing"

func TestSearchRange(t *testing.T) {
    arr := []int{5,7,7,8,8,10}
    target := 8
    result := searchRange(arr, target)
    PrintArray(result)
}