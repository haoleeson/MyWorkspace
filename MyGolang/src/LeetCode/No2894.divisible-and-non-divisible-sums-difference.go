/*
No2894.divisible-and-non-divisible-sums-difference
*/
func differenceOfSums(n int, m int) int {
	sumNot, sumCould := 0, 0
	for i := 1; i <= n; i++ {
		if i%m == 0 {
			sumCould += i
		} else {
			sumNot += i
		}
	}

	return sumNot - sumCould
}