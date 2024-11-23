/*
No3243.shortest-distance-after-road-addition-queries-i
*/
func shortestDistanceAfterQueries(n int, queries [][]int) []int {
	lenQ := len(queries)
	ans := make([]int, lenQ)

	// from[i] 记录终点为 i 的近道列表
	from := make([][]int, n)

	// dp[i] means min paths from 0 to i
	dp := make([]int, n)
	for i := 1; i < n; i++ {
		dp[i] = i
	}

	for qi, q := range queries {
		l, r := q[0], q[1]
		from[r] = append(from[r], l)
		// 如果有值得走的近道
		if dp[l]+1 < dp[r] {
			dp[r] = dp[l] + 1
			// 更新 dp[r] 后方 dp[i]
			for i := r + 1; i < n; i++ {
				dp[i] = min(dp[i], dp[i-1]+1)
				// 遍历前方可一步到 i 的近路列表，尝试找更近
				for _, j := range from[i] {
					dp[i] = min(dp[i], dp[j]+1)
				}
			}
		}
		ans[qi] = dp[n-1]
	}
	return ans
}