/*
No122.best-time-to-buy-and-sell-stock-ii
*/
func maxProfit(prices []int) int {
	n := len(prices)
	dp := make([][2]int, n)

	// dp[i][1] : 表示第i天还持有股票，根据前一天是否持有股票状态更新状态方程，dp[i][1] = max ( dp[i-1][1], dp[i-1][0] - prices[i])
	// dp[i][0] : 表示第i天不持有股票，根据前一天是否持有股票状态更新状态方程, dp[i][0] = max ( dp[i-1][0], dp[i-1][1] + prices[i])
	dp[0][1] = -prices[0]
	for i := 1; i < n; i++ {
		dp[i][1] = max(dp[i-1][1], dp[i-1][0]-prices[i])
		dp[i][0] = max(dp[i-1][0], dp[i-1][1]+prices[i])
	}

	return dp[n-1][0]
}

func max(x, y int) int {
	if y > x {
		return y
	}
	return x
}