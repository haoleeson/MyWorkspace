/*
No114.flatten-binary-tree-to-linked-list
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func flatten(root *TreeNode) {
	var preHeader *TreeNode = &TreeNode{}
	ptrPreNode := preHeader

	var firstOrder func(*TreeNode)
	firstOrder = func(node *TreeNode) {
		if node == nil {
			return
		}

		ptrPreNode.Left = nil
		ptrPreNode.Right = node
		ptrPreNode = ptrPreNode.Right

		l, r := node.Left, node.Right

		firstOrder(l)
		firstOrder(r)
	}

	firstOrder(root)
}
