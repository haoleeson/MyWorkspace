/*
LCR174.er-cha-sou-suo-shu-de-di-kda-jie-dian-lcof
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

func findTargetNode(root *TreeNode, cnt int) int {
	var ret, idx int = 0, 0

	var mirrorMidOrder func(*TreeNode)
	mirrorMidOrder = func(node *TreeNode) {
		if node == nil {
			return
		}

		// right
		mirrorMidOrder(node.Right)

		// node
		idx++
		if idx == cnt {
			ret = node.Val
			return
		}

		// left
		mirrorMidOrder(node.Left)
	}

	mirrorMidOrder(root)
	return ret
}
