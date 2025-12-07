/*
No20.valid-parentheses
*/

// 2025-12-07 recoding
func isValid(s string) bool {
	n := len(s)
	miniStack := make([]byte, n)
	size := 0

	for i := 0; i < n; i++ {
		ch := byte(s[i])
		switch ch {
		case '(', '[', '{':
			// push
			miniStack[size] = ch
			size++
		case ')', ']', '}':
			if size == 0 {
				return false
			}
			switch ch {
			case ')':
				if miniStack[size-1] != '(' {
					return false
				}
			case ']':
				if miniStack[size-1] != '[' {
					return false
				}
			case '}':
				if miniStack[size-1] != '{' {
					return false
				}
			}
			// pop
			size--
		}
	}

	return size == 0
}

func isValid0(s string) bool {
	n := len(s)
	stack := make([]byte, n)
	sLen := 0

	for i := 0; i < n; i++ {
		switch s[i] {
		case '(', '[', '{':
			stack[sLen] = s[i]
			sLen++
		case ')':
			if sLen > 0 && stack[sLen-1] == '(' {
				// pop
				sLen--
			} else {
				return false
			}
		case ']':
			if sLen > 0 && stack[sLen-1] == '[' {
				// pop
				sLen--
			} else {
				return false
			}
		case '}':
			if sLen > 0 && stack[sLen-1] == '{' {
				// pop
				sLen--
			} else {
				return false
			}
		default:
			return false
		}

	}

	return sLen == 0
}