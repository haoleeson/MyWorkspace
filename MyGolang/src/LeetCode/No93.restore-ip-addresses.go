/*
No93.restore-ip-addresses
*/

func restoreIpAddresses(s string) []string {
	n := len(s)
	IPs := make([]string, 0)

	idxPath := make([]int, 3)

	// check IP number valid s[start, endIdx]
	var checkIPNumValid func(int, int) bool
	checkIPNumValid = func(startIdx, endIdx int) bool {
		numLen := endIdx - startIdx
		switch numLen {
		case 0:
			// len == 1, all valid
			return true
		case 1:
			// len == 2
			if s[startIdx] == '0' {
				// has pre '0', 0x, invalid
				return false
			}
		case 2:
			// len == 3
			if s[startIdx] != '1' && s[startIdx] != '2' {
				// not 1xx or 2xx, invalid
				return false
			}
			if s[startIdx] == '1' {
				// 1xx, all valid
				return true
			}
			// 2xx
			if s[startIdx+1] > '5' {
				// >= 26x, invalid
				return false
			}
			if s[startIdx+1] == '5' && s[startIdx+2] > '5' {
				// > 255, invalid
				return false
			}
		default:
			// len > 3, return invalid
			return false
		}
		return true
	}

	var genIPStr func() string
	genIPStr = func() string {
		return s[0:idxPath[0]+1] + "." +
			s[idxPath[0]+1:idxPath[1]+1] + "." +
			s[idxPath[1]+1:idxPath[2]+1] + "." +
			s[idxPath[2]+1:]
	}

	var dfs func(int)
	dfs = func(splitNo int) {
		if splitNo == 3 {
			// have max split '.', check if last IP num valid
			if checkIPNumValid(idxPath[2]+1, n-1) {
				IPs = append(IPs, genIPStr())
			}
			return
		}

		lastSplitIdx := -1
		if splitNo > 0 {
			lastSplitIdx = idxPath[splitNo-1]
		}
		probeEndIdx := min(lastSplitIdx+3, n-1)
		// choose next split idx
		for i := lastSplitIdx + 1; i <= probeEndIdx; i++ {
			if checkIPNumValid(lastSplitIdx+1, i) {
				// find i as the splitNo Idx, record it
				idxPath[splitNo] = i
				// find the next splitNo
				dfs(splitNo + 1)
			}
		}
	}

	dfs(0)

	return IPs
}