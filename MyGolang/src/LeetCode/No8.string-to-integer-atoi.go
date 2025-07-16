/*
No8.string-to-integer-atoi
*/

func myAtoi(s string) int {
	n := len(s)
	var ret int64 = 0
	negFlag := false

	idx := 0

	// skip pre space
	for idx < n && s[idx] == ' ' {
		idx++
	}
	if idx == n {
		return 0
	}

	// '-' or '+'
	if s[idx] == '-' {
		negFlag = true
		idx++
	} else if s[idx] == '+' {
		idx++
	}

	// skip pre zero
	for idx < n && s[idx] == '0' {
		idx++
	}

	// parse num
	for idx < n {
		// break if not number char
		if s[idx] < '0' || s[idx] > '9' {
			break
		}

		ret *= 10
		ret += int64(s[idx] - '0')

		// limit range
		if negFlag {
			// -
			if (-1 * ret) < math.MinInt32 {
				return math.MinInt32
			}
		} else {
			// +
			if ret > math.MaxInt32 {
				return math.MaxInt32
			}
		}

		idx++
	}

	if negFlag {
		ret *= -1
	}

	return int(ret)
}
