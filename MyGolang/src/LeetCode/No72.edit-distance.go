/*
No72.edit-distance
*/
func minDistance(word1 string, word2 string) int {
	n1 := len(word1)
	n2 := len(word2)

	var minOfThree func(int, int, int) int
	minOfThree = func(a, b, c int) int {
		return min(min(a, b), c)
	}

	// dp[i][j] means: cost of word1[0:i] -> word2[0:j]
	dp := make([][]int, n1+1)
	for i := 0; i < n1+1; i++ {
		dp[i] = make([]int, n2+1)
	}
	// word1[:0] -> word2[0:j]
	for j := 1; j <= n2; j++ {
		dp[0][j] = j // add
	}

	// word1[0:i] ->word2[:0]
	for i := 1; i <= n1; i++ {
		dp[i][0] = i // del
	}

	// dp[i][j]
	for i := 1; i <= n1; i++ {
		for j := 1; j <= n2; j++ {
			if word1[i-1] == word2[j-1] {
				// char equal, no need operate
				dp[i][j] = dp[i-1][j-1]
			} else {
				// 1 + min of three methord
				// insert: dp[i][j-1] insert word2[j]
				// delete: dp[i-1][j] del word1[i]
				// replace: dp[i-1][j-1] word1[i] -> word2[j]
				dp[i][j] = 1 + minOfThree(dp[i][j-1], dp[i-1][j], dp[i-1][j-1])
			}
		}
	}

	return dp[n1][n2]
}