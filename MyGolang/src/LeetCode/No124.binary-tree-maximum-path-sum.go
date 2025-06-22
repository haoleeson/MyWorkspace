/*
No124.binary-tree-maximum-path-sum
*/
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func maxPathSum(root *TreeNode) int {
	maxSum := math.MinInt32

	// get sum of the single path with node as root
	var getRootSingleSum func(*TreeNode) int
	getRootSingleSum = func(node *TreeNode) int {
		if node == nil {
			return 0
		}

		leftNodeMaxGain := max(getRootSingleSum(node.Left), 0)
		rightNodeMaxGain := max(getRootSingleSum(node.Right), 0)

		// extra record max path sum
		pathSum := node.Val + leftNodeMaxGain + rightNodeMaxGain
		if pathSum > maxSum {
			maxSum = pathSum
		}

		return node.Val + max(leftNodeMaxGain, rightNodeMaxGain)
	}

	getRootSingleSum(root)
	return maxSum
}

func max(a, b int) int {
	if b > a {
		return b
	}
	return a
}