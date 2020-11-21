package LeetCode

import "fmt"

// Definition for singly-linked list.
type ListNode struct {
    Val int
    Next *ListNode
}

/**
 * 构造链表
 */
func GenList(arr []int) *ListNode {
    var i, size int = 0, len(arr)
    if size == 0 {
        return nil
    }
    var head = new(ListNode)
    head.Val = arr[i]
    i++
    var ptr = head
    for i < size {
        ptr.Next = new(ListNode)
        ptr = ptr.Next
        ptr.Val = arr[i]
        i++
    }
    return head
}

/**
 * 打印链表
 */
func PrintList(head *ListNode) {
    if head != nil {
        var ptr = head
        for ptr.Next != nil {
            fmt.Print(ptr.Val, "->")
            ptr = ptr.Next
        }
        fmt.Print(ptr.Val)
    }
    fmt.Println()
}