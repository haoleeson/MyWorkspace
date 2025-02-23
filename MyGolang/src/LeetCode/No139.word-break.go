/*
No139.word-break
*/

func cmpString(s string, startIdx int, word string) bool {
	n := len(s)
	m := len(word)
	if startIdx+m > n {
		return false
	}
	for i := 0; i < m; i++ {
		if s[startIdx+i] != word[i] {
			return false
		}
	}
	return true
}

func dps(s string, wordDict []string, startIdx int, chooseWord string) bool {
	n := len(s)
	if startIdx == n {
		return true
	}

	// this choose
	if len(chooseWord) > 0 {
		if cmpString(s, startIdx, chooseWord) {
			startIdx += len(chooseWord)
			if startIdx == n {
				return true
			}
		} else {
			return false
		}
	}

	// next choose
	for _, word := range wordDict {
		if dps(s, wordDict, startIdx, word) {
			return true
		}
	}
	return false
}

// 深度优先搜索（超时）
func wordBreak0(s string, wordDict []string) bool {
	return dps(s, wordDict, 0, "")
}

// 动态规划
func wordBreak(s string, wordDict []string) bool {
	wordDictSet := make(map[string]bool)
	for _, w := range wordDict {
		wordDictSet[w] = true
	}

	dp := make([]bool, len(s)+1)
	dp[0] = true

	// dp[i] = dp[j] && s[j:i] in wordDict
	for i := 1; i <= len(s); i++ {
		for j := 0; j < i; j++ {
			if dp[j] && wordDictSet[s[j:i]] {
				dp[i] = true
				break
			}
		}
	}

	return dp[len(s)]
}