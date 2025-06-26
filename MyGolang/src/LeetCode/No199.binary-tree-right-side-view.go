/*
No199.binary-tree-right-side-view
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func rightSideView(root *TreeNode) []int {
	ret := make([]int, 0)
	if root == nil {
		return ret
	}

	curLevel := make([]*TreeNode, 0)
	curLevel = append(curLevel, root)
	curLevelSize := len(curLevel)
	var nextLevel []*TreeNode

	for curLevelSize > 0 {
		nextLevel = make([]*TreeNode, 0)

		// append curLevel rightest node val
		ret = append(ret, curLevel[curLevelSize-1].Val)

		for _, node := range curLevel {
			if node.Left != nil {
				nextLevel = append(nextLevel, node.Left)
			}
			if node.Right != nil {
				nextLevel = append(nextLevel, node.Right)
			}
		}

		curLevel = nextLevel
		curLevelSize = len(curLevel)
	}

	return ret
}