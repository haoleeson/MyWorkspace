/*
No790.domino-and-tromino-tiling
*/
func numTilings(n int) int {
	const modVal int = 1e9 + 7

	// dp[n]
	dp := make([][4]int, n+1)
	dp[0][3] = 1

	for i := 1; i <= n; i++ {
		dp[i][0] = dp[i-1][3]
		dp[i][1] = (dp[i-1][0] + dp[i-1][2]) % modVal
		dp[i][2] = (dp[i-1][0] + dp[i-1][1]) % modVal
		dp[i][3] = (((dp[i-1][3]+dp[i-1][1])%modVal+dp[i-1][2])%modVal + dp[i-1][0]) % modVal
	}

	return dp[n][3]
}