// No1963.minimum-number-of-swaps-to-make-the-string-balanced

func minSwaps(s string) int {
	cnt, mincnt := 0, 0
	for _, ch := range s {
		if ch == '[' {
			cnt++
		} else {
			cnt--
			mincnt = min(mincnt, cnt)
		}
	}
	return (-mincnt + 1) / 2
}