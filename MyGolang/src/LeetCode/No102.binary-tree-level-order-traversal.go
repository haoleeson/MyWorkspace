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

// 2025-12-01 recoding
func levelOrder(root *TreeNode) [][]int {
	ret := make([][]int, 0)
	if root == nil {
		return ret
	}

	lvlNodes := make([]*TreeNode, 0)
	lvlNodes = append(lvlNodes, root)

	for len(lvlNodes) > 0 {
		lvlVals := make([]int, len(lvlNodes))
		nextLvlNodes := make([]*TreeNode, 0)
		for i, node := range lvlNodes {
			lvlVals[i] = node.Val
			if node.Left != nil {
				nextLvlNodes = append(nextLvlNodes, node.Left)
			}
			if node.Right != nil {
				nextLvlNodes = append(nextLvlNodes, node.Right)
			}
		}
		ret = append(ret, lvlVals)
		lvlNodes = nextLvlNodes
	}
	return ret
}

func levelOrder0(root *TreeNode) [][]int {
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