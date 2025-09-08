/*
No14.longest-common-prefix
*/

func longestCommonPrefix(strs []string) string {
	n := len(strs)
	b := []byte(strs[0])
	preLen := 0

	for i, j := 0, 0; j < len(b); j++ {
		// cmp other str
		for i = 1; i < n; i++ {
			if j >= len(strs[i]) || b[j] != strs[i][j] {
				break
			}
		}
		if i < n {
			break
		}
		preLen++
	}

	return string(b[:preLen])
}
