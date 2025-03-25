/*
No102.binary-tree-level-order-traversal
*/
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func levelOrder(root *TreeNode) [][]int {
	var curLevel, nextLevel []*TreeNode
	ret := make([][]int, 0)

	if root != nil {
		curLevel = append(curLevel, root)
	}

	for len(curLevel) > 0 {
		curNums := make([]int, len(curLevel))
		nextLevel = make([]*TreeNode, 0)

		for i := 0; i < len(curLevel); i++ {
			curNums[i] = curLevel[i].Val
			if curLevel[i].Left != nil {
				nextLevel = append(nextLevel, curLevel[i].Left)
			}
			if curLevel[i].Right != nil {
				nextLevel = append(nextLevel, curLevel[i].Right)
			}
		}
		ret = append(ret, curNums)
		curLevel = nextLevel
	}

	return ret
}