/*
No678.valid-parenthesis-string
*/

func checkValidString(s string) bool {
	n := len(s)

	dp := make([][]bool, n)
	for i := 0; i < n; i++ {
		dp[i] = make([]bool, n)
	}

	// sub len = 1,  s[i]
	for i, ch := range s {
		if ch == '*' {
			dp[i][i] = true
		}
	}

	// sub len = 2,  s[i-1, i]
	for i := 1; i < n; i++ {
		lc, rc := s[i-1], s[i]
		// (), (*, *), **
		dp[i-1][i] = (lc == '(' || lc == '*') && (rc == '*' || rc == ')')
	}

	// sub len > 2, s[i, j]
	for i := n - 3; i >= 0; i-- {
		lc := s[i]

		for j := i + 2; j < n; j++ {
			rc := s[j]

			// 1. can sub start, end
			if (lc == '(' || lc == '*') && (rc == '*' || rc == ')') {
				dp[i][j] = dp[i+1][j-1]
			}
			// 2. can merge
			for k := i; k < j && !dp[i][j]; k++ {
				dp[i][j] = dp[i][k] && dp[k+1][j]
			}
		}
	}
	return dp[0][n-1]
}

