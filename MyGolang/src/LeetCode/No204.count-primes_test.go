package LeetCode

import (
    "fmt"
    "testing"
)

func TestCountPrimes(t *testing.T) {
    arr := []int{0, 1, 2, 4, 16, 64, 100}
    for _, num := range arr {
        fmt.Printf("countPrimes(%d) = %d\n", num, countPrimes(num))
    }
}