/*
No5.longest-palindromic-substring
*/

func longestPalindrome(s string) string {
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