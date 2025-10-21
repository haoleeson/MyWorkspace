/*
No958.check-completeness-of-a-binary-tree
*/

/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */

type ANode struct {
	Node *TreeNode
	Code int
}

func isCompleteTree(root *TreeNode) bool {
	nodes := []*ANode{&ANode{Node: root, Code: 1}}
	i := 0

	for i < len(nodes) {
		aNode := nodes[i]
		i++
		if aNode.Node != nil {
			// add left node
			nodes = append(nodes, &ANode{Node: aNode.Node.Left, Code: aNode.Code * 2})
			// add right node
			nodes = append(nodes, &ANode{Node: aNode.Node.Right, Code: aNode.Code*2 + 1})
		}
	}

	return nodes[len(nodes)-1].Code == len(nodes)
}
