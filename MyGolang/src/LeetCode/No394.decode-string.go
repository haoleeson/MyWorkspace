/*
No394.decode-string
*/

func decodeString(s string) string {
	n := len(s)
	origBuf := []byte(s)

	var subDecode func(int, int) []byte
	subDecode = func(startIdx, EndIdx int) []byte {
		subBuf := []byte{}
		var i, preStrIdx int = startIdx, startIdx
		for ; i <= EndIdx; i++ {
			// pre string
			if origBuf[i] < '0' || origBuf[i] > '9' {
				continue
			}
			// add pre str
			if i > startIdx {
				subBuf = append(subBuf, origBuf[preStrIdx:i]...)
			}

			// get num value
			dupTimes := 0
			for ; origBuf[i] >= '0' && origBuf[i] <= '9'; i++ {
				dupTimes = dupTimes*10 + int(origBuf[i]-'0')
			}
			// find compare ']'
			cntLeft, cntRight := 1, 0
			j := i + 1
			for ; ; j++ {
				switch origBuf[j] {
				case '[':
					cntLeft++
				case ']':
					cntRight++
				}
				if cntLeft == cntRight {
					break
				}
			}

			// decode encoded_string
			subDecodeBuf := subDecode(i+1, j-1)

			// duplicate encoded string
			for k := 0; k < dupTimes; k++ {
				subBuf = append(subBuf, subDecodeBuf...)
			}

			i = j
			preStrIdx = j + 1
		}

		// add tail string
		if i > preStrIdx {
			subBuf = append(subBuf, origBuf[preStrIdx:i]...)
		}

		return subBuf
	}

	return string(subDecode(0, n-1))
}
