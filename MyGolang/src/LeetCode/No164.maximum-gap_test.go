package LeetCode

import (
    "fmt"
    "testing"
)

func TestMaximumGap(t *testing.T) {
    nums1 := []int{3,6,9,1}
    fmt.Printf("The maximum gap of num1 is:%d\n", maximumGap(nums1))

    nums2 := []int{10}
    fmt.Printf("The maximum gap of num1 is:%d\n", maximumGap(nums2))

    nums3 := []int{1,10000000}
    fmt.Printf("The maximum gap of num1 is:%d\n", maximumGap(nums3))
}