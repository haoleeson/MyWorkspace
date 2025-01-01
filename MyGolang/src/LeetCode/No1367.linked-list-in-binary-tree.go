/*
No1367.linked-list-in-binary-tree
*/
/**
 * Definition for singly-linked list.
 * type ListNode struct {
 *     Val int
 *     Next *ListNode
 * }
 */
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

// preorder func
func preorder(root *TreeNode, head *ListNode) bool {
	if head == nil {
		return true
	}
	if root == nil {
		return false
	}

	// not equal, return false
	if root.Val != head.Val {
		return false
	}

    // equal, continue left child or right child
	return preorder(root.Left, head.Next) || preorder(root.Right, head.Next)
}

func isSubPath(head *ListNode, root *TreeNode) bool {
	if root == nil {
		return false
	}
	return preorder(root, head) || isSubPath(head, root.Left) || isSubPath(head, root.Right)
}