/*
No136.single-number
*/

func singleNumber(nums []int) int {
	// 0 ^ a = a
	var res int = 0
	for _, num := range nums {
		res ^= num
	}
	return res
}