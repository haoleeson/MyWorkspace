/*
No3403.find-the-lexicographically-largest-string-from-the-box-i
*/
func answerString(word string, numFriends int) string {
	if numFriends == 1 {
		return word
	}
	n := len(word)
	b := []byte(word)
	maxSubStrLen := n - numFriends + 1
	tmpMax := make([]byte, maxSubStrLen)

	isBigger := func(idx, l int) bool {
		for j := 0; j < l; j++ {
			if b[idx+j] == tmpMax[j] {
				continue
			}
			return b[idx+j] > tmpMax[j]
		}
		return false
	}

	saveTmpMax := func(idx int) {
		for k := 0; k < maxSubStrLen; k++ {
			tmpMax[k] = b[idx+k]
		}
	}

	i := 0
	// compare fixed [i:i+maxSubStrLen]
	for ; i < n-maxSubStrLen; i++ {
		if isBigger(i, maxSubStrLen) {
			saveTmpMax(i)
		}
	}

	// compare tail [n-maxSubStrLen:]
	for ; i < n; i++ {
		if isBigger(i, n-i) {
			tmpMax = b[i:]
		}
	}

	return string(tmpMax)
}