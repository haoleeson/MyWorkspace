/*
No110.balanced-binary-tree
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func isBalanced(root *TreeNode) bool {
	var balanceFlag bool = true

	var treeDeepth func(*TreeNode) int
	treeDeepth = func(node *TreeNode) int {
		if node == nil {
			return 0
		}

		leftDeepth := treeDeepth(node.Left)
		rightDeepth := treeDeepth(node.Right)

		if rightDeepth > leftDeepth {
			if rightDeepth-leftDeepth > 1 {
				balanceFlag = false
			}
			return rightDeepth + 1
		}
		if leftDeepth-rightDeepth > 1 {
			balanceFlag = false
		}
		return leftDeepth + 1
	}

	treeDeepth(root)

	return balanceFlag
}