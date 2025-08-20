/*
No39.combination-sum
*/
func combinationSum(candidates []int, target int) [][]int {
	n := len(candidates)
	ans := make([][]int, 0)
	comb := []int{}

	var dfs func(int, int)
	dfs = func(target, idx int) {
		// if used all candidates num, break dfs
		if idx == n {
			return
		}
		// if find comb nums equal target, break dfs
		if target == 0 {
			ans = append(ans, append([]int(nil), comb...))
			return
		}

		// do not choose candidates[idx], find next
		dfs(target, idx+1)

		// choose candidates[idx]
		if target-candidates[idx] >= 0 {
			comb = append(comb, candidates[idx])
			dfs(target-candidates[idx], idx) // candidates[idx] can choose again
			comb = comb[:len(comb)-1]
		}
	}

	dfs(target, 0)
	return ans
}