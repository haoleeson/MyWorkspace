/*
No2269.find-the-k-beauty-of-a-number
*/
func divisorSubstrings(num int, k int) int {
	numStr := strconv.Itoa(num)
	lenNumStr := len(numStr)
	if k == lenNumStr {
		return 1
	}

	ans := 0
	for i := k - 1; i < lenNumStr; i++ {
		subNum, _ := strconv.Atoi(numStr[i-k+1 : i+1])
		if subNum == 0 {
			continue
		}
		if num%subNum == 0 {
			ans++
		}
	}

	return ans
}