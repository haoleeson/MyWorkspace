/*
LCR143.shu-de-zi-jie-gou-lcof
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func isSubStructure(A *TreeNode, B *TreeNode) bool {
	if A == nil || B == nil {
		return false
	}

	return dfsCmp(A, B) || isSubStructure(A.Left, B) || isSubStructure(A.Right, B)
}

func dfsCmp(nodeA, nodeB *TreeNode) bool {
    if nodeB == nil {
        return true
    }
    if nodeA == nil {
        return false
    }
    if nodeA.Val != nodeB.Val {
        return false
    }
    return dfsCmp(nodeA.Left, nodeB.Left) && dfsCmp(nodeA.Right, nodeB.Right)
}
