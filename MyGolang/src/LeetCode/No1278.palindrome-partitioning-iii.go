/*
No1278.palindrome-partitioning-iii
*/
func palindromePartition(s string, k int) int {
	n := len(s)

	cost := func(leftIndex, rightIndex int) int {
		c := 0
		l, r := leftIndex, rightIndex
		for l < r {
			if s[l] != s[r] {
				c++
			}
			l++
			r--
		}
		return c
	}

	// dp[i][j] 表示字符串 s[:i] 分割成 j 个 回文子串的最小消耗
	// dp[i][j] = min{dp[k][j-1] + cost(k, i-1)}
	dp := make([][]int, n+1)
	for i := 0; i < n+1; i++ {
		dp[i] = make([]int, k+1)
		for j := 0; j < k+1; j++ {
			dp[i][j] = math.MaxInt
		}
	}
	dp[0][0] = 0

	for i := 1; i < n+1; i++ {
		for j := 1; j <= min(k, i); j++ {
			if j == 1 {
				dp[i][j] = cost(0, i-1)
			} else {
				for k := j - 1; k < i; k++ {
					dp[i][j] = min(dp[i][j], dp[k][j-1]+cost(k, i-1))
				}
			}
		}
	}

	return dp[n][k]
}