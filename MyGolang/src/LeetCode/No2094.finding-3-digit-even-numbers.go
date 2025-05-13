/*
No2094.finding-3-digit-even-numbers
*/
func findEvenNumbers(digits []int) []int {
	// count nums
	digitCnt := make([]int, 10)
	for _, d := range digits {
		digitCnt[d]++
	}

	var isValid func(int) bool
	isValid = func(num int) bool {
		numDigitCnt := make([]int, 10)
		for num > 0 {
			d := num % 10
			numDigitCnt[d]++
			if numDigitCnt[d] > digitCnt[d] {
				return false
			}
			num /= 10
		}
		// // check digit cnt valid
		// for i := 0; i < 10; i++ {
		// 	if numDigitCnt[i] > digitCnt[i] {
		// 		return false
		// 	}
		// }
		return true
	}

	ret := make([]int, 0)
	for num := 100; num < 1000; num += 2 {
		if isValid(num) {
			ret = append(ret, num)
		}
	}
	return ret
}