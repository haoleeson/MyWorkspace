/*
No198.house-robber
*/
func rob(nums []int) int {
	n := len(nums)

	dp_choose_i := make([]int, n)
	dp_choose_i[0] = nums[0]
	dp_skip_i := make([]int, n)
	dp_skip_i[0] = 0

	for i := 1; i < n; i++ {
		// choose i
		dp_choose_i[i] = nums[i] + dp_skip_i[i-1]
		// skip i
		dp_skip_i[i] = max(dp_choose_i[i-1], dp_skip_i[i-1])
	}

	return max(dp_choose_i[n-1], dp_skip_i[n-1])
}

func max(x, y int) int {
	if y > x {
		return y
	}
	return x
}