/*
No144.binary-tree-preorder-traversal
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func preorderTraversal(root *TreeNode) []int {
	ans := make([]int, 0)

	var preorderTraversal func(*TreeNode)
	preorderTraversal = func(node *TreeNode) {
		if node == nil {
			return
		}

		ans = append(ans, node.Val)
		preorderTraversal(node.Left)
		preorderTraversal(node.Right)
	}

	preorderTraversal(root)
	return ans
}