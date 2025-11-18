/*
No230.kth-smallest-element-in-a-bst
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func kthSmallest(root *TreeNode, k int) int {
	ret, idx := 0, 0

	var midOrder func(*TreeNode)
	midOrder = func(node *TreeNode) {
		if node == nil {
			return
		}

		// left
		midOrder(node.Left)
		// root
		idx++
		if idx == k {
			ret = node.Val
			return
		}
		// right
		midOrder(node.Right)
	}

	midOrder(root)

	return ret
}
