/*
No5.longest-palindromic-substring
*/

// 2025-11-30 recoding
func longestPalindrome(s string) string {
	n := len(s)
	maxSubLen := 0
	var maxSubStr string = s[0:1]

	// dp[i][j] means sub str s[i:j] is palindromic
	dp := make([][]bool, n)
	for i := 0; i < n; i++ {
		dp[i] = make([]bool, n)
		dp[i][i] = true
	}

	// calc len == 2
	for i := 0; i <= n-2; i++ {
		if s[i] == s[i+1] {
			dp[i][i+1] = true
			if maxSubLen < 2 {
				maxSubLen = 2
				maxSubStr = s[i : i+2]
			}
		}
	}

	// calc len > 2
	for len := 3; len <= n; len++ {
		for i := 0; i <= n-len; i++ {
			if s[i] == s[i+len-1] && dp[i+1][i+len-2] {
				dp[i][i+len-1] = true
				if maxSubLen < len {
					maxSubLen = len
					maxSubStr = s[i : i+len]
				}
			}
		}
	}

	return maxSubStr
}

func longestPalindrome0(s string) string {
	n := len(s)
	maxLen := 1
	longestSubStr := s[0:1]

	// record s[i:j] is palindromic
	memPalindromic := make([][]bool, n)
	for i := 0; i < n; i++ {
		memPalindromic[i] = make([]bool, n)
		memPalindromic[i][i] = true
	}

	for length := 2; length <= n; length++ {
		for i := 0; i < n-length+1; i++ {
			j := i + length - 1
			if s[i] == s[j] {
				if length < 4 {
					memPalindromic[i][j] = true
					if length > maxLen {
						maxLen = length
						longestSubStr = s[i : j+1]
					}
				} else if memPalindromic[i+1][j-1] {
					memPalindromic[i][j] = true
					if length > maxLen {
						maxLen = length
						longestSubStr = s[i : j+1]
					}
				}
			}
		}
	}
	return longestSubStr
}