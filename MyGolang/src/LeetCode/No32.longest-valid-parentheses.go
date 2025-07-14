/*
No32.longest-valid-parentheses
*/

func longestValidParentheses(s string) int {
	ret := 0
	n := len(s)

	dp := make([]int, n)
	for i := 1; i < n; i++ {
		if s[i] == '(' {
			continue
		}

		if s[i-1] == '(' {
			if i > 1 {
				dp[i] = dp[i-2] + 2
			} else {
				dp[i] = 2
			}
		} else if i-dp[i-1] > 0 && s[i-dp[i-1]-1] == '(' {
			if i-dp[i-1] > 1 {
				// s[i-dp[i-1]-2] + "(" + [, i-1] + ")"
				dp[i] = dp[i-dp[i-1]-2] + dp[i-1] + 2
			} else {
				dp[i] = dp[i-1] + 2
			}
		}

		if dp[i] > ret {
			ret = dp[i]
		}
	}

	return ret
}