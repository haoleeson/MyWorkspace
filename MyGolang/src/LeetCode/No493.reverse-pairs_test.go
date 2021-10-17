package LeetCode

import (
    "fmt"
    "testing"
)

func TestReversePairs(t *testing.T) {
    nums1 := []int{1,3,2,3,1}
    fmt.Printf("The ans of reverse pairs arr is:%d\n", reversePairs(nums1))
    nums2 := []int{2,4,3,5,1}
    fmt.Printf("The ans of reverse pairs arr is:%d\n", reversePairs(nums2))
}