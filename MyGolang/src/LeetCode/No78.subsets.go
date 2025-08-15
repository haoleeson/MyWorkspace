/*
No78.subsets
*/

// method1: iterator
func subsets(nums []int) [][]int {
	n := len(nums)
	iterEnd := (1 << n) - 1
	ans := make([][]int, 0)

	for mask := 0; mask <= iterEnd; mask++ {
		set := []int{}
		// choose num of nums by binary num idx
		// 0: 000
		// 1: 001
		for i, v := range nums {
			if mask>>i&1 > 0 {
				set = append(set, v)
			}
		}
		ans = append(ans, append([]int(nil), set...))
	}

	return ans
}

// method2: dfs
func subsets2(nums []int) [][]int {
	n := len(nums)
	set := []int{}
	ans := make([][]int, 0)

	var dfs func(int)
	dfs = func(cur int) {
		// if get enough num, add path num set to ans
		if cur == n {
			ans = append(ans, append([]int(nil), set...))
			return
		}

		// choose cur idx num
		set = append(set, nums[cur])
		dfs(cur + 1)

		// do not choose cur idx num
		set = set[:len(set)-1]
		dfs(cur + 1)
	}

	dfs(0)

	return ans
}
