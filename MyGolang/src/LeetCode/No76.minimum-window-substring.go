/*
No76.minimum-window-substring
*/

func minWindow(s string, t string) string {
	n := len(s)
	MAX_LEN := n + 1
	// count need chars number
	needCharCnt := make(map[byte]int)
	for _, ch := range t {
		needCharCnt[byte(ch)]++
	}

	var ret string = ""

	minLen := MAX_LEN
	curCharCnt := make(map[byte]int)

	var checkContainCh func() bool
	checkContainCh = func() bool {
		for ch, cnt := range needCharCnt {
			if curCnt, existed := curCharCnt[ch]; !existed || curCnt < cnt {
				return false
			}
		}
		return true
	}

	for l, r := 0, 0; r < n; r++ {
		// move right pointer to contain all ch
		for ; r < n; r++ {
			curCharCnt[byte(s[r])]++
			if checkContainCh() {
				break
			}
		}
		if r == n {
			break
		}

		// move left pointer to smaller sub str
		for l <= r && checkContainCh() {
			if (r - l + 1) < minLen {
				minLen = r - l + 1
				ret = s[l : r+1]
			}
			// remove left ch
			if curCharCnt[s[l]] == 1 {
				delete(curCharCnt, byte(s[l]))
			} else {
				curCharCnt[byte(s[l])]--
			}
			l++
		}

	}

	fmt.Printf("minLen: %d\n", minLen)
	if minLen == MAX_LEN {
		return ""
	}
	return ret
}
