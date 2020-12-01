package LeetCode

import "fmt"

// Definition for singly-linked list.
type ListNode struct {
    Val int
    Next *ListNode
}

/** ListNode 构造函数 */
func NewListNode(val int) *ListNode {
    return &ListNode{Val: val, Next: nil}
}

// Definition for a binary tree node.
type TreeNode struct {
    Val int
    Left *TreeNode
    Right *TreeNode
}

/** TreeNode 构造函数 */
func NewTreeNode(val int) *TreeNode {
    return &TreeNode{Val: val, Left: nil, Right: nil}
}

/**
 * 构造链表
 */
func GenList(arr []int) *ListNode {
    var i, size int = 0, len(arr)
    if size == 0 {
        return nil
    }
    var head = NewListNode(arr[i])
    i++
    var ptr = head
    for i < size {
        ptr.Next = NewListNode(arr[i])
        ptr = ptr.Next
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

/**
 * 打印数组
 */
func PrintArray(arr []int) {
    size := len(arr)
    fmt.Print("[")
    if size > 0 {
        fmt.Print(arr[0])
        for i := 1; i < size; i++ {
            fmt.Print(", ", arr[i])
        }
    }
    fmt.Println("]")
}