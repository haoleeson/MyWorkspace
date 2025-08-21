/*
No64.minimum-path-sum
*/
func minPathSum(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])

	dp := make([][]int, m+1)
	for i := 0; i < m+1; i++ {
		dp[i] = make([]int, n+1)
	}
	// first row init
	for j := 1; j < n+1; j++ {
		dp[1][j] = dp[1][j-1] + grid[0][j-1]
	}
	// first column init
	for i := 1; i < m+1; i++ {
		dp[i][1] = dp[i-1][1] + grid[i-1][0]
	}

	// dp[i][j] = grid[i-1][j-1] + min(left: dp[i][j-1],  up: dp[i-1][j])
	for i := 2; i <= m; i++ {
		for j := 2; j <= n; j++ {
			dp[i][j] = grid[i-1][j-1] + min(dp[i][j-1], dp[i-1][j])
		}
	}

	return dp[m][n]
}

func min(x, y int) int {
	if y < x {
		return y
	}
	return x
}