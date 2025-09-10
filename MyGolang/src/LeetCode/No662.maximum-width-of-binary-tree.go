/*
No662.maximum-width-of-binary-tree
*/
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func widthOfBinaryTree(root *TreeNode) int {
	eachLvlMinIdx := make(map[int]int)
	var maxWidth int = 0

	var dfs func(*TreeNode, int, int)
	dfs = func(node *TreeNode, depth, index int) {
		if node == nil {
			return
		}
		// mark first left node index
		if _, existed := eachLvlMinIdx[depth]; !existed {
			eachLvlMinIdx[depth] = index
		}

		// left
		dfs(node.Left, depth+1, index*2)
		// right
		dfs(node.Right, depth+1, index*2+1)
		// root
		tmpWidth := index - eachLvlMinIdx[depth] + 1
		if tmpWidth > maxWidth {
			maxWidth = tmpWidth
		}
	}

	dfs(root, 1, 1)
	return maxWidth
}