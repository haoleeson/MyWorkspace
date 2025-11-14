/*
No213.house-robber-ii
*/

func rob(nums []int) int {
	n := len(nums)

	var max func(int, int) int
	max = func(x, y int) int {
		if y > x {
			return y
		}
		return x
	}

	switch n {
	case 1:
		return nums[0]
	case 2:
		return max(nums[0], nums[1])
	}

	// no choose nums[n-1], range: [0,n-2]
	dp_0_n_2 := make([]int, n)
	dp_0_n_2[0] = nums[0]
	dp_0_n_2[1] = max(nums[0], nums[1])
	for i := 2; i < n-1; i++ {
		dp_0_n_2[i] = max(dp_0_n_2[i-1], dp_0_n_2[i-2]+nums[i])
	}

	// may choose nums[n-1], range: [1, n-1]
	dp_1_n_1 := make([]int, n)
	dp_1_n_1[1] = nums[1]
	dp_1_n_1[2] = max(nums[1], nums[2])
	for i := 3; i < n; i++ {
		dp_1_n_1[i] = max(dp_1_n_1[i-1], dp_1_n_1[i-2]+nums[i])
	}

	return max(dp_0_n_2[n-2], dp_1_n_1[n-1])
}
