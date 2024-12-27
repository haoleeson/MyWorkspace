/*
No3083.existence-of-a-substring-in-a-string-and-its-reverse
*/

func isSubstringPresent(s string) bool {
	n := len(s)

	// record char index list
	charIdxList := make([][]int, 26)
	charIdxList[s[0]-'a'] = make([]int, 0)
	charIdxList[s[0]-'a'] = append(charIdxList[s[0]-'a'], 0)
	for i := 0; i < n; i++ {
		if len(charIdxList[s[i]-'a']) > 0 {
			// check existed, add index
			charIdxList[s[i]-'a'] = append(charIdxList[s[i]-'a'], i)
		} else {
			// not found, add index
			charIdxList[s[i]-'a'] = make([]int, 1)
			charIdxList[s[i]-'a'][0] = i
		}
	}

	// compare
	for i := 0; i < n-1; i++ {
		for _, idx := range charIdxList[s[i]-'a'] {
			if idx-1 >= 0 && s[idx-1] == s[i+1] {
				return true
			}
		}
	}

	return false
}