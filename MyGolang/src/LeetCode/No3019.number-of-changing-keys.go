/*
No3019.number-of-changing-keys
*/

func convtNum(b byte) byte {
	if b >= 'A' && b <= 'Z' {
		return b - 'A'
	}
	if b >= 'a' && b <= 'z' {
		return b - 'a'
	}
	return b
}

func countKeyChanges(s string) int {
	n := len(s)
	ret := 0

	var last byte = convtNum(s[0])
	for i := 1; i < n; i++ {
		tmp := convtNum(s[i])
		if tmp != last {
			ret++
			last = tmp
		}
	}

	return ret
}
