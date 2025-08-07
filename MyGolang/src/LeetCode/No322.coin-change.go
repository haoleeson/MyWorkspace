/*
No322.coin-change
*/

func coinChange(coins []int, amount int) int {
	// dp[i] = min{dp[i-coins[j]]}, j = [0, n-1]
	dp := make([]int, amount+1)
	MAX_VALUE := amount + 1
	for i := 1; i <= amount; i++ {
		dp[i] = MAX_VALUE
	}
	dp[0] = 0

	for i := 1; i <= amount; i++ {
		// iterator coins
		for _, coin := range coins {
			// skip bigger coin
			if coin > i {
				continue
			}
			// amount == i, dp[amount - coin] + 1
			dp[i] = min(dp[i], dp[i-coin]+1)
		}
	}

	if dp[amount] > amount {
		return -1
	}
	return dp[amount]
}