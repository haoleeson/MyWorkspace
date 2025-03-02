/*
No132.palindrome-partitioning-ii
*/
func isPalindrome(b []byte, l int, r int) bool {
	for l < r {
		if b[l] != b[r] {
			return false
		}
		l++
		r--
	}

	return true
}

func minCut(s string) int {
	n := len(s)
	b := []byte(s)

	dp := make([]int, n)
	// dp[i] = min{dp[i-1] + 1, dp[l-1] + 1 if s[l:i] is palindrome}
	dp[0] = 0

	for i := 1; i < n; i++ {
		dp[i] = dp[i-1] + 1
		for l := 0; l < i; l++ {
			if isPalindrome(b, l, i) {
				if l == 0 {
					dp[i] = 0
				} else {
					dp[i] = min(dp[i], dp[l-1]+1)
				}
			}
		}
	}
	return dp[n-1]
}