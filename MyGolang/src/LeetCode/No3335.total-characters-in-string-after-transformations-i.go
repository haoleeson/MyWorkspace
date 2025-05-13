/*
No3335.total-characters-in-string-after-transformations-i
*/
func lengthAfterTransformations(s string, t int) int {
	const mod = 1e9 + 7
	// count origin char number
	cnt := make([]int, 26)
	for _, ch := range s {
		cnt[ch-'a']++
	}

	for round := 0; round < t; round++ {
		nxt := make([]int, 26)
		nxt[0] = cnt[25]
		nxt[1] = (cnt[25] + cnt[0]) % mod
		for ch := 2; ch < 26; ch++ {
			nxt[ch] = cnt[ch-1]
		}

		cnt = nxt
	}

	ret := 0
	for ch := 0; ch < 26; ch++ {
		ret = (ret + cnt[ch]) % mod
	}
	return ret
}