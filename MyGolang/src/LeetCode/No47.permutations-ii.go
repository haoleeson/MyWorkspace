/*
No47.permutations-ii
*/

func permuteUnique(nums []int) [][]int {
	n := len(nums)
	sort.Ints(nums)
	visit := make([]bool, n)
	path := make([]int, n)
	ret := make([][]int, 0)

	var traceback func(int)
	traceback = func(idx int) {
		if idx == n {
			ret = append(ret, append([]int(nil), path...))
			return
		}

		for i, num := range nums {
			if visit[i] || (i > 0 && !visit[i-1] && num == nums[i-1]) {
				continue
			}
			visit[i] = true
			path[idx] = num
			traceback(idx + 1)
			visit[i] = false
		}
	}

	traceback(0)

	return ret
}