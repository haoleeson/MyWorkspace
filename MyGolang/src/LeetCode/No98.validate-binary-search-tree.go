/*
No98.validate-binary-search-tree
*/
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func isValidBST(root *TreeNode) bool {

	lastVal := math.MinInt

	var checkBST func(*TreeNode) bool
	checkBST = func(node *TreeNode) bool {
		if node == nil {
			return true
		}
		if !checkBST(node.Left) {
			return false
		}
		// check cur node val bigger than lastVal
		if node.Val <= lastVal {
			return false
		}
		lastVal = node.Val
		if !checkBST(node.Right) {
			return false
		}
		return true
	}

	return checkBST(root)
}