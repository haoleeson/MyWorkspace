/*
No2595.number-of-even-and-odd-bits
*/
func evenOddBit(n int) []int {
	ans := make([]int, 2)
	evenFlag := true
	for n > 0 {
		if n&1 == 1 {
			if evenFlag {
				ans[0]++
			} else {
				ans[1]++
			}

		}
		n >>= 1
		evenFlag = !evenFlag
	}
	return ans
}