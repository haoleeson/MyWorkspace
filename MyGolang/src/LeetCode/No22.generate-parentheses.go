/*
No22.generate-parentheses
*/
func generateParenthesis(n int) []string {
	parenthesesNum := n * 2
	path := make([]byte, parenthesesNum)
	ret := make([]string, 0)

	lCnt, rCnt := 0, 0

	var dfs func(int)
	dfs = func(idx int) {
		if idx == parenthesesNum {
			if lCnt == rCnt {
				ret = append(ret, string(path))
			}
			return
		}

		// invalid check
		if rCnt > lCnt {
			return
		}

		for i := 0; i < 2; i++ {
			if i == 0 {
				lCnt++
				path[idx] = '('
				dfs(idx + 1)
				lCnt--
			} else {
				rCnt++
				path[idx] = ')'
				dfs(idx + 1)
				rCnt--
			}
		}
	}

	dfs(0)

	return ret
}