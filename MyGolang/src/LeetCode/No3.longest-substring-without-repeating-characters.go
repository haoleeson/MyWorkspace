/*
No3.longest-substring-without-repeating-characters
*/
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

		if r-l > ans {
			ans = r - l
		}

		if r >= n {
			break
		}

		// move l still s[l] == s[r]
		for l < r && s[l] != s[r] {
			flag[s[l]] = false
			l++
		}
		r++
	}

	return ans
}

func lengthOfLongestSubstring2(s string) int {
	n := len(s)
	maxSubLen := 0
	chMap := make(map[byte]bool)

	// split window
	for l, r := 0, 0; r < n; r++ {
		ch := s[r]
		if !chMap[ch] {
			// not dumplicate
			chMap[ch] = true
			if r-l+1 > maxSubLen {
				maxSubLen = r - l + 1
			}
		} else {
			// dumplicate
			// move left to the dumplicate ch idx
			for ; s[l] != ch; l++ {
				chMap[s[l]] = false
			}
			// move left to behind the dumplicate ch idx
			l++
		}
	}
	return maxSubLen
}