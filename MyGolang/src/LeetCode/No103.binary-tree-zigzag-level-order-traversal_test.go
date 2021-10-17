package LeetCode

import "testing"

func TestZigzagLevelOrder(t *testing.T) {
    root := NewTreeNode(3)
    root.Left = NewTreeNode(9)
    root.Right = NewTreeNode(20)
    root.Right.Left = NewTreeNode(15)
    root.Right.Right = NewTreeNode(7)

    result := zigzagLevelOrder(root)
    printArray2D(result)
}