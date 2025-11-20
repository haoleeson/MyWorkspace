/*
No96.unique-binary-search-trees
*/

func numTrees(n int) int {
	dp := make([]int, n+1)
	dp[0] = 1
	dp[1] = 1

	// accumulate calc num [2, n]
	for num := 2; num < n+1; num++ {
		// choose root as each calc [1, num]
		for root := 1; root < num+1; root++ {
			// left node cnt: root - 1
			// right node cnt: num - root
			dp[num] += dp[root-1] * dp[num-root]
		}
	}
	return dp[n]
}
