/*
No53.maximum-subarray
*/
// 2025-11-28 recoding
func maxSubArray(nums []int) int {
	n := len(nums)
	maxSubSum := nums[0]
	var dp_i, dp_i_1 int = 0, nums[0]

	var max func(int, int) int
	max = func(x, y int) int {
		if y > x {
			return y
		}
		return x
	}

	for i := 1; i < n; i++ {
		dp_i = max(dp_i_1+nums[i], nums[i])
		if dp_i > maxSubSum {
			maxSubSum = dp_i
		}

		dp_i_1 = dp_i
	}

	return maxSubSum
}

func maxSubArray0(nums []int) int {
	dp_i, dp_i_1, ret := 0, 0, math.MinInt

	for _, num := range nums {
		dp_i = max(dp_i_1+num, num)
		dp_i_1 = dp_i
		if dp_i > ret {
			ret = dp_i
		}
	}
	return ret
}