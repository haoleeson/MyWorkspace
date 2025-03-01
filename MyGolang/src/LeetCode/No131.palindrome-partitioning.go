/*
No131.palindrome-partitioning
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

func deepCopyStringList(origin []string) []string {
	newL := make([]string, 0)
	for _, s := range origin {
		newL = append(newL, s)
	}
	return newL
}

func partition(s string) [][]string {
	n := len(s)
	b := []byte(s)
	dp := make([][][]string, n)
	dp[0] = make([][]string, 0)
	dp[0] = append(dp[0], []string{string(b[0])})

	// dp[i] = dp[i-1] 各数组追加 "b[i]"， + 可与 dp[j] + "b[j:i]" 组成回文字符的子串
	for i := 1; i < n; i++ {
		dp[i] = make([][]string, 0)

		// dp[i-1] 各数组追加 "b[i]"
		for _, subList := range dp[i-1] {
			tmp := deepCopyStringList(subList)
			tmp = append(tmp, string(b[i]))
			dp[i] = append(dp[i], tmp)
		}

		// 尝试向前遍历字符串本身 b[l:i] ，看是否能组成回文串，若有则追加前缀 b[l:i-1]
		for j := i - 1; j >= 0; j-- {
			if isPalindrome(b, j, i) {
				if j == 0 {
					if i == n {
						dp[i] = append(dp[i], []string{s})
					} else {
						dp[i] = append(dp[i], []string{string(b[0 : i+1])})
					}
				} else {
					for _, subList := range dp[j-1] {
						tmp := deepCopyStringList(subList)
						if i == n {
							tmp = append(tmp, string(b[j:]))
						} else {
							tmp = append(tmp, string(b[j:i+1]))
						}
						dp[i] = append(dp[i], tmp)
					}
				}
			}
		}
	}

	return dp[n-1]
}