package LeetCode

import (
    "fmt"
    "testing"
)

func TestLargestPerimeter(t *testing.T) {
    nums1 := []int{2,1,2}
    fmt.Println(nums1,  "ans = ", largestPerimeter(nums1))
    nums2 := []int{1,2,1}
    fmt.Println(nums1,  "ans = ", largestPerimeter(nums2))
    nums3 := []int{3,2,3,4}
    fmt.Println(nums1,  "ans = ", largestPerimeter(nums3))
    nums4 := []int{3,6,2,3}
    fmt.Println(nums1,  "ans = ", largestPerimeter(nums4))
}