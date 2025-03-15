// No3.longest-substring-without-repeating-characters
func lengthOfLongestSubstring(s string) int {
	n := len(s)
	ans := 0
	flag := make([]bool, 256)

	for l, r := 0, 0; l < n; l++ {
		// move r still duplicate
		for r < n && !flag[s[r]] {
			flag[s[r]] = true
			r++
		}

		ans = max(ans, r-l)

		if r >= n {
			break
		}

		// move r still s[l] == s[r]
		for l < r && s[l] != s[r] {
			flag[s[l]] = false
			l++
		}
		r++
	}

	return ans
}