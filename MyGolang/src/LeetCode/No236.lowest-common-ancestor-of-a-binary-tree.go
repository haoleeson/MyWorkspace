/*
No236.lowest-common-ancestor-of-a-binary-tree
*/
func lowestCommonAncestor(root, p, q *TreeNode) *TreeNode {
	if root == nil {
		return nil
	}

	if root == p || root == q {
		return root
	}

	leftRet := lowestCommonAncestor(root.Left, p, q)
	rightRet := lowestCommonAncestor(root.Right, p, q)

	if leftRet != nil && rightRet != nil {
		return root
	} else if leftRet != nil {
		return leftRet
	} else if rightRet != nil {
		return rightRet
	}
	return nil
}