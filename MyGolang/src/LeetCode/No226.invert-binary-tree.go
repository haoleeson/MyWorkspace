/*
No226.invert-binary-tree
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func invertTree(root *TreeNode) *TreeNode {
	var invertTree func(*TreeNode)
	invertTree = func(node *TreeNode) {
		if node == nil {
			return
		}

		invertTree(node.Left)
		invertTree(node.Right)

		// exchange left right
		tmp := node.Left
		node.Left = node.Right
		node.Right = tmp
	}

	invertTree(root)
	return root
}