/*
No91.decode-ways
*/

func numDecodings(s string) int {
	n := len(s)
	dp := make([]int, n+2)
	dp[0] = 1
	dp[1] = 1

	var validCurNum func(int) bool
	validCurNum = func(idx int) bool {
		return s[idx] != '0'
	}

	var validPreTwoNum func(int) bool
	validPreTwoNum = func(idx int) bool {
		if idx <= 0 {
			return false
		}
		if s[idx-1] < '1' || s[idx-1] > '2' {
			return false
		}
		if s[idx-1] == '2' && s[idx] > '6' {
			return false
		}
		return true
	}

	for i := 0; i < n; i++ {
		if validCurNum(i) {
			dp[i+2] += dp[i+1]
		}
		if validPreTwoNum(i) {
			dp[i+2] += dp[i]
		}
	}
	return dp[n+1]
}
