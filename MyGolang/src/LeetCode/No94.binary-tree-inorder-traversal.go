/*
No94.binary-tree-inorder-traversal
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func inorderTraversal(root *TreeNode) []int {
	ret := make([]int, 0)

	var iterator func(*TreeNode)
	iterator = func(node *TreeNode) {
		if node != nil {
			iterator(node.Left)
			ret = append(ret, node.Val)
			iterator(node.Right)
		}
	}

	iterator(root)

	return ret
}