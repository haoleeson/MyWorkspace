/*
No2390.removing-stars-from-a-string
*/
func removeStars(s string) string {
	n := len(s)
	b := []byte(s)
	starCnt := 0
	arr := make([]byte, n)
	j := 0
	chCnt := 0

	for i := n - 1; i >= 0; i-- {
		if b[i] == '*' {
			starCnt++
		} else if starCnt > 0 {
			starCnt--
		} else {
			arr[j] = b[i]
			j++
			chCnt++
		}
	}

	ans := make([]byte, chCnt)
	for i := 0; i < chCnt; i++ {
		ans[i] = arr[chCnt-i-1]
	}
	return string(ans)
}