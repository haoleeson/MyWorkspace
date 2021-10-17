package LeetCode

import "testing"

func TestMaxNumber(t *testing.T) {
    arr1 := []int{3, 4, 6, 5}
    arr2 := []int{9, 1, 2, 5, 8, 3}
    k := 5
    result := maxNumber(arr1, arr2, k)
    PrintArray(result)
}