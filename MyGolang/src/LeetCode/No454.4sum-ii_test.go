package LeetCode

import (
    "fmt"
    "testing"
)

func TestFourSumCount(t *testing.T) {
    A := []int{1, 2}
    B := []int{-2, -1}
    C := []int{-1, 2}
    D := []int{0, 2}
    fmt.Printf("The ans of four count is:%d\n", fourSumCount(A, B, C, D))
}