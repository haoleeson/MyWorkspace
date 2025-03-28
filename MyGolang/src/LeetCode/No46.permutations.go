/*
No46.permutations
*/

func permute(nums []int) [][]int {
	n := len(nums)
	path := make([]int, n)
	visited := make([]bool, n)

	ret := make([][]int, 0)

	var dfs func(int)
	dfs = func(i int) {
		if i == n {
			ret = append(ret, append([]int(nil), path...))
			return
		}
		for idx, vi := range visited {
			if !vi {
				path[i] = nums[idx]
				visited[idx] = true
				dfs(i + 1)
				visited[idx] = false
			}
		}
	}

	dfs(0)
	return ret
}