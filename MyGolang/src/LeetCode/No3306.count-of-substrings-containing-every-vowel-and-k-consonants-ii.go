/*
No3306.count-of-substrings-containing-every-vowel-and-k-consonants-ii
*/
func countOfSubstrings(word string, k int) int64 {
	n := len(word)
	eveVowCharIdxSet := map[byte]int{'a': 0, 'e': 1, 'i': 2, 'o': 3, 'u': 4}

	isEveVowCharOnce := func(eveVowCharCnt []int) bool {
		for _, cnt := range eveVowCharCnt {
			if cnt < 1 {
				return false
			}
		}
		return true
	}

	subCountOfK := func(kk int) int64 {
		var ans int64 = 0
		eveVowCharCnt := make([]int, 5)
		otherCharCnt := 0

		for l, r := 0, 0; l < n; l++ {
			// move r to isEveVowCharOnce()
			for r < n && (!isEveVowCharOnce(eveVowCharCnt) || otherCharCnt < kk) {
				if idx, existed := eveVowCharIdxSet[word[r]]; existed {
					eveVowCharCnt[idx]++
				} else {
					otherCharCnt++
				}
				r++
			}

			if isEveVowCharOnce(eveVowCharCnt) && otherCharCnt >= kk {
				ans += int64(n - r + 1)
			}

			// move l one by one step
			if idx, existed := eveVowCharIdxSet[word[l]]; existed {
				eveVowCharCnt[idx]--
			} else {
				otherCharCnt--
			}
		}
		return ans
	}

	return subCountOfK(k) - subCountOfK(k+1)
}