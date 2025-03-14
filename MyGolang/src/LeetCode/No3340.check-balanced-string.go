/*
No3340.check-balanced-string
*/
func isBalanced(num string) bool {
	b := []byte(num)
	tmp := 0
	flag := true
	for _, ch := range b {
		if flag {
			tmp += int(ch - '0')
		} else {
			tmp -= int(ch - '0')
		}
		flag = !flag
	}
	return tmp == 0
}