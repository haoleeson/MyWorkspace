/*
No2566.maximum-difference-by-remapping-a-digit
*/
func minMaxDifference(num int) int {
	minNum, maxNum := num, num

	for chgNum := 0; chgNum <= 9; chgNum++ {
		tmpMinNum, tmpMaxNum := num, num
		for i, numIter := 1, 0; i <= num; i *= 10 {
			numIter = (num / i % 10)

			// skip not base num
			if numIter != chgNum {
				continue
			}

			// change numIter of tmpMinNum to 0
			if numIter != 0 {
				tmpMinNum -= numIter * i
			}

			// change numIter of tmpMaxNum to 9
			if numIter != 9 {
				tmpMaxNum += (9 - numIter) * i
			}
		}
		maxNum = max(maxNum, tmpMaxNum)
		minNum = min(minNum, tmpMinNum)
	}

	return maxNum - minNum
}