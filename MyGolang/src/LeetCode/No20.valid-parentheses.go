/*
No20.valid-parentheses
*/
func isValid(s string) bool {
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