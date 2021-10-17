package LeetCode

import "testing"

func TestSortList(t *testing.T) {
    var arr []int = []int{-1, 5, 3, 4, 0}
    var head *ListNode = GenList(arr)
    PrintList(head)
    sortList(head)
    PrintList(head)
}