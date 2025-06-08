/*
No53.maximum-subarray
*/
func maxSubArray(nums []int) int {
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