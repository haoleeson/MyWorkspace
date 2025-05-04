/*
No1128.number-of-equivalent-domino-pairs
*/
func numEquivDominoPairs(dominoes [][]int) int {
	n := len(dominoes)
	preCnt := make([]int, 100)
	ans := 0

	for i := 0; i < n; i++ {
		numA := dominoes[i][0]*10 + dominoes[i][1]
		numB := dominoes[i][1]*10 + dominoes[i][0]
		if numA != numB {
			ans += preCnt[numA] + preCnt[numB]
		} else {
			ans += preCnt[numA]
		}

		preCnt[numA]++
	}
	return ans
}