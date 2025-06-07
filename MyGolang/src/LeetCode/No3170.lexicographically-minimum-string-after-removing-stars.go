/*
No3170.lexicographically-minimum-string-after-removing-stars
*/
func clearStars(s string) string {
	n := len(s)
	b := []byte(s)
	var charCnt int = 0
	var DEL_CHAR byte = '_'
	var MAX_BYTE byte = byte(127)
	var smallestChar byte = MAX_BYTE
	charIdxs := make([][]int, 26)
	for i := 0; i < 26; i++ {
		charIdxs[i] = make([]int, 0)
	}

	findSmallestChar := func() byte {
		for j := 'a'; j <= 'z'; j++ {
			if len(charIdxs[j-'a']) > 0 {
				return byte(j)
			}
		}
		return MAX_BYTE
	}

	for i := 0; i < n; i++ {
		if b[i] == '*' {
			// could delete '*' and a smallest
			if charCnt == 0 {
				// none char, skip
				b[i] = DEL_CHAR
				continue
			}
			lenSmallestChar := len(charIdxs[smallestChar-'a'])
			if lenSmallestChar > 0 {
				// delete leftest of smallest char
				b[charIdxs[smallestChar-'a'][lenSmallestChar-1]] = DEL_CHAR
				// if last smallestChar end, find new smallestChar
				if lenSmallestChar == 1 {
					charIdxs[smallestChar-'a'] = make([]int, 0)
					smallestChar = findSmallestChar()
				} else {
					charIdxs[smallestChar-'a'] = charIdxs[smallestChar-'a'][:lenSmallestChar-1]
				}
				b[i] = DEL_CHAR
				charCnt--
			}
		} else {
			// add a-z char
			if b[i] < smallestChar {
				smallestChar = b[i]
			}
			charIdxs[b[i]-'a'] = append(charIdxs[b[i]-'a'], i)
			charCnt++
		}
	}

	//fmt.Printf("debug b : " + string(b))

	result := make([]byte, charCnt)
	for i, j := 0, 0; i < n; i++ {
		if b[i] == DEL_CHAR {
			continue
		}
		result[j] = b[i]
		j++
	}

	return string(result)
}