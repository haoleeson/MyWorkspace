package LeetCode

import (
    "fmt"
    "testing"
)

func TestMaxProfit(t *testing.T) {
    prices := []int{1, 3, 2, 8, 4, 9}
    fee := 2
    fmt.Println(maxProfit(prices, fee))
}