/*
No101.symmetric-tree
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func isSymmetric(root *TreeNode) bool {

	var mirrorEqual func(*TreeNode, *TreeNode) bool
	mirrorEqual = func(src *TreeNode, dst *TreeNode) bool {
		if src == nil && dst == nil {
			return true
		} else if (src == nil && dst != nil) || (src != nil && dst == nil) {
			return false
		}

		if src.Val != dst.Val {
			return false
		}

		return mirrorEqual(src.Left, dst.Right) && mirrorEqual(src.Right, dst.Left)
	}

	return mirrorEqual(root.Left, root.Right)
}