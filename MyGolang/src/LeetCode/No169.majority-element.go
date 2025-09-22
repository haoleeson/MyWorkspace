/*
No169.majority-element
*/
func majorityElement(nums []int) int {
	n := len(nums)
	cntMap := make(map[int]int)

	for _, num := range nums {
		cntMap[num]++
	}

	var half int
	if n%2 == 0 {
		half = n/2 - 1
	} else {
		half = n / 2
	}

	for k, v := range cntMap {
		if v > half {
			return k
		}
	}

	return 0
}