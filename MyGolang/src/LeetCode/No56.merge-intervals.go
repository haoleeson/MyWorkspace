/*
No56.merge-intervals
*/
func merge(intervals [][]int) [][]int {
	// sort intervals
	cmpFunc := func(a, b []int) int {
		return a[0] - b[0]
	}
	slices.SortFunc(intervals, cmpFunc)

	ret := make([][]int, 0)
	lenRet := 0
	// iteration and
	for _, interval := range intervals {
		if lenRet > 0 && interval[0] <= ret[lenRet-1][1] {
			// can merge with ret[lenRet-1]
			ret[lenRet-1][1] = max(ret[lenRet-1][1], interval[1])
		} else {
			ret = append(ret, interval)
			lenRet++
		}
	}
	return ret
}