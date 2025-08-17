/*
No129.sum-root-to-leaf-numbers
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func sumNumbers(root *TreeNode) int {
	var ans int = 0
	var tmpNum int

	var dfs func(*TreeNode)
	dfs = func(node *TreeNode) {
		if node == nil {
			return
		}

		// mid
		tmpNum = tmpNum*10 + node.Val
		if node.Left == nil && node.Right == nil {
			ans += tmpNum
		}

		// left
		if node.Left != nil {
			dfs(node.Left)
		}
		// right
		if node.Right != nil {
			dfs(node.Right)
		}

		tmpNum /= 10
	}

	dfs(root)

	return ans
}