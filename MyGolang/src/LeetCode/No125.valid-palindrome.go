/*
No125.valid-palindrome
*/

func isPalindrome(s string) bool {
	n := len(s)

	// trim string
	var sLen int = 0
	trimS := make([]byte, n)
	for _, ch := range s {
		if ch >= 'A' && ch <= 'Z' {
			trimS[sLen] = byte(ch) + byte(32)
			sLen++
		} else if ch >= 'a' && ch <= 'z' {
			trimS[sLen] = byte(ch)
			sLen++
		} else if ch >= '0' && ch <= '9' {
			trimS[sLen] = byte(ch)
			sLen++
		}
	}

	// check trim string
	l, r := 0, sLen-1
	for l < r {
		if trimS[l] != trimS[r] {
			return false
		}
		l++
		r--
	}
	return true
}
