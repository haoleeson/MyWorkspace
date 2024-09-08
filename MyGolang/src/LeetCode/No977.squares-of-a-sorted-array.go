/*
No977.squares-of-a-sorted-array
*/

func abs(a int) int {
	if a < 0 {
		return -a
	}
	return a
}

func sortedSquares(nums []int) []int {
	n := len(nums)
	res := make([]int, n)

	// double pointer
	var i, j, k int = 0, n - 1, n - 1
	for ; k >= 0; k-- {
		if abs(nums[i]) > abs(nums[j]) {
			res[k] = nums[i] * nums[i]
			i++
		} else {
			res[k] = nums[j] * nums[j]
			j--
		}
	}
	return res
}