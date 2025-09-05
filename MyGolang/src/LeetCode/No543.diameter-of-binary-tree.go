/*
No543.diameter-of-binary-tree.go
*/
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func diameterOfBinaryTree(root *TreeNode) int {
	var ret int = 0

	var maxDep func(*TreeNode) int
	maxDep = func(node *TreeNode) int {
		if node == nil {
			return 0
		}

		leftMaxDep := maxDep(node.Left)
		rightMaxDep := maxDep(node.Right)

		// cmp max diameter
		tmpDim := leftMaxDep + rightMaxDep
		if tmpDim > ret {
			ret = tmpDim
		}

		return max(leftMaxDep, rightMaxDep) + 1
	}

	maxDep(root)
	return ret

}

func max(x, y int) int {
	if y > x {
		return y
	}
	return x
}