package LeetCode

import (
    "fmt"
    "testing"
)

func TestCountNodes(t *testing.T) {
    var root *TreeNode = NewTreeNode(1)
    root.Left = NewTreeNode(2)
    root.Right = NewTreeNode(3)
    root.Left.Left = NewTreeNode(4)
    root.Left.Right = NewTreeNode(5)
    root.Right.Left = NewTreeNode(6)
    fmt.Printf("The num of complete binary tree is: %d", countNodes(root))
}