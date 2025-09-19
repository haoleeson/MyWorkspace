/*
No112.path-sum
*/
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func hasPathSum(root *TreeNode, targetSum int) bool {
	if root == nil {
		return false
	}
	var hasPath bool = false

	var findTree func(*TreeNode, int)
	findTree = func(node *TreeNode, left int) {
		if node == nil {
			return
		}
		if node.Left == nil && node.Right == nil {
			if left == node.Val {
				hasPath = true
				return
			}
		}

		findTree(node.Left, left-node.Val)
		findTree(node.Right, left-node.Val)
	}

	findTree(root, targetSum)
	return hasPath
}