/*
No1745.palindrome-partitioning-iv
*/
func checkPartitioning(s string) bool {
	n := len(s)

	// mem[l][r] record s[l:r] is palindrome
	mem := make([][]bool, n)
	for i := 0; i < n; i++ {
		mem[i] = make([]bool, n)
		mem[i][i] = true
	}
	for length := 2; length < n; length++ {
		for l := 0; l <= n-length; l++ {
			r := l + length - 1
			if length < 4 {
				mem[l][r] = s[l] == s[r]
			} else {
				mem[l][r] = s[l] == s[r] && mem[l+1][r-1]
			}
		}
	}

	// dp[i][j] 表示 s[:i] 是否可分割成 j 个回文字串
	// dp[i][j] = dp[k][j-1] && isPalindrome s[k:i]
	splitNum := 3
	dp := make([][]bool, n+1)
	for i := 0; i < n+1; i++ {
		dp[i] = make([]bool, splitNum+1)
	}
	dp[0][0] = true
	for i := 1; i < n+1; i++ {
		dp[i][1] = mem[0][i-1]
	}

	for i := 1; i < n+1; i++ {
		for j := 2; j <= min(splitNum, i); j++ {
			for k := j - 1; k < i; k++ {
				if dp[k][j-1] && mem[k][i-1] {
					dp[i][j] = true
					break
				}
			}
		}
	}

	return dp[n][splitNum]
}