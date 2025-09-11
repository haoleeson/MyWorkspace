/*
No113.path-sum-ii
*/
/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
func pathSum(root *TreeNode, targetSum int) [][]int {
	ret := make([][]int, 0)
	path := make([]int, 0)

	var dfs func(*TreeNode, int)
	dfs = func(node *TreeNode, left int) {
		if node == nil {
			return
		}

		// add node value into path
		path = append(path, node.Val)
		left -= node.Val

		defer func() {
			// del node value from path
			path = path[:len(path)-1]
		}()

		// if leaf node
		if node.Left == nil && node.Right == nil && left == 0 {
			// fmt.Printf("path: %+v,  left: %d\n", path, left)
			ret = append(ret, append([]int(nil), path...))
			return

		}

		// left
		dfs(node.Left, left)
		// right
		dfs(node.Right, left)

	}

	dfs(root, targetSum)

	return ret
}