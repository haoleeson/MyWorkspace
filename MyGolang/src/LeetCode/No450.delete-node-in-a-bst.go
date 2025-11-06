/*
No450.delete-node-in-a-bst
*/
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func deleteNode(root *TreeNode, key int) *TreeNode {
	if root == nil {
		return nil
	} else if root.Val > key {
		// search left
		root.Left = deleteNode(root.Left, key)
	} else if root.Val < key {
		// search right
		root.Right = deleteNode(root.Right, key)
	} else if root.Left == nil || root.Right == nil {
		// find key, not both has left and right child
		if root.Left != nil {
			// use left ans new root
			return root.Left
		}
		return root.Right
	} else {
		// find key, both has left and right child
		// find left min node as new root
		successor := root.Right
		for successor.Left != nil {
			successor = successor.Left
		}
		// set successor as new root
		// delete the min node from root.Right tree
		successor.Right = deleteNode(root.Right, successor.Val)
		successor.Left = root.Left
		return successor
	}
	return root
}