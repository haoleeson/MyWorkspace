/*
No2274.maximum-consecutive-floors-without-special-floors
*/
func maxConsecutive(bottom int, top int, special []int) int {
	sort.Ints(special)
	ret := special[0] - bottom
	n := len(special)

	last, tmp := special[0], 0

	for i := 1; i < n; i++ {
		tmp := special[i] - last - 1
		if tmp > ret {
			ret = tmp
		}
		last = special[i]
	}

	tmp = top - last
	if tmp > ret {
		ret = tmp
	}
	return ret
}