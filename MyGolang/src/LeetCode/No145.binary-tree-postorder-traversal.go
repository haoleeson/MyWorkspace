/*
No145.binary-tree-postorder-traversal
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func postorderTraversal(root *TreeNode) []int {
	ret := make([]int, 0)

	var postOrder func(*TreeNode)
	postOrder = func(node *TreeNode) {
		if node == nil {
			return
		}

		postOrder(node.Left)
		postOrder(node.Right)
		ret = append(ret, node.Val)
	}

	postOrder(root)

	return ret
}
