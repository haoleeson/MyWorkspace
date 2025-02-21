/*
No624.maximum-distance-in-arrays
*/
func maxDistance(arrays [][]int) int {
	res := 0
	minVal := arrays[0][0]
	maxVal := arrays[0][len(arrays[0])-1]

	for i := 1; i < len(arrays); i++ {
		res = max(res, max(abs(maxVal-arrays[i][0])), abs(arrays[i][len(arrays[i])-1]-minVal))

		minVal = min(minVal, arrays[i][0])
		maxVal = max(maxVal, arrays[i][len(arrays[i])-1])
	}
	return res
}

func abs(x int) int {
	if x < 0 {
		return -x
	}
	return x
}