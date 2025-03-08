/*
No410.split-array-largest-sum
*/
func splitArray(nums []int, k int) int {
	n := len(nums)

	// memSum[i]: calc sum of nums[0:i)
	memSum := make([]int, n+1)
	for i := 0; i < n; i++ {
		memSum[i+1] = memSum[i] + nums[i]
	}

	// dp[i][j] 表示 nums[0:i) 分割成 j 个子数组的和的最大值的最小值
	dp := make([][]int, n+1)
	for i := 0; i <= n; i++ {
		dp[i] = make([]int, k+1)
		for j := 0; j <= k; j++ {
			dp[i][j] = math.MaxInt
		}
	}
	dp[0][0] = 0

	// dp[i][j] = min( max(dp[s][j-1], sum(nums[s:i])) )  for s in 1:i
	for i := 1; i <= n; i++ {
		for j := 1; j <= min(i, k); j++ {
			tmpMin := math.MaxInt
			for s := 0; s < i; s++ {
				tmpMin = min(tmpMin, max(dp[s][j-1], memSum[i]-memSum[s]))
			}
			dp[i][j] = tmpMin
		}
	}
	return dp[n][k]
}