/*
No53.maximum-subarray
*/
func maxSubArray(nums []int) int {
	n := len(nums)
	dp := make([]int, n)
	dp[0] = nums[0]
	ret := nums[0]

	for i := 1; i < n; i++ {
		dp[i] = max(dp[i-1]+nums[i], nums[i])
		ret = max(ret, dp[i])
	}
	return ret
}