/*
No139.word-break
*/

// dp
func wordBreak(s string, wordDict []string) bool {
	n := len(s)
	wordDictMap := make(map[string]bool)
	for _, word := range wordDict {
		wordDictMap[word] = true
	}

	dp := make([]bool, n+1)
	dp[0] = true

	for i := 1; i <= n; i++ {
		for j := 0; j < i; j++ {
			if dp[j] && wordDictMap[s[j:i]] {
				dp[i] = true
				break
			}
		}
	}
	return dp[n]
}

// dfs 超时
func wordBreak0(s string, wordDict []string) bool {
	var spillAble bool = false

	var startEqual func(string, string) bool
	startEqual = func(cmpStr, cmpWord string) bool {
		lenW := len(cmpWord)
		if len(cmpStr) < lenW {
			return false
		}
		for chIdx := 0; chIdx < lenW; chIdx++ {
			if cmpStr[chIdx] != cmpWord[chIdx] {
				return false
			}
		}
		return true
	}

	var dfs func(string)
	dfs = func(str string) {
		if len(str) == 0 {
			spillAble = true
			return
		}

		for _, word := range wordDict {
			if startEqual(str, word) {
				dfs(str[len(word):])
			}
		}
	}

	dfs(s)

	return spillAble
}