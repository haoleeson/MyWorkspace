/*
No46.permutations
*/

// 2025-12-05 recoding
func permute(nums []int) [][]int {
	n := len(nums)
	ret := make([][]int, 0)
	path := make([]int, n)
	vis := make([]bool, n)

	var dfs func(int)
	dfs = func(idx int) {
		if idx == n {
			ret = append(ret, append([]int(nil), path...))
			return
		}

		for i := 0; i < n; i++ {
			if vis[i] {
				continue
			}

			vis[i] = true
			path[idx] = nums[i]
			dfs(idx + 1)
			vis[i] = false
		}
	}

	dfs(0)

	return ret
}

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