/*
No3110.score-of-a-string
*/
func scoreOfString(s string) int {
	b := []byte(s)
	n := len(b)
	ans := 0

	absSub := func(a, b byte) int {
		if b > a {
			return int(b - a)
		}
		return int(a - b)
	}

	for i := 1; i < n; i++ {
		ans += absSub(b[i], b[i-1])
	}
	return ans
}