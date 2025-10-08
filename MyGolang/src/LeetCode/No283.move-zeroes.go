/*
No283.move-zeroes
*/
func moveZeroes(nums []int) {
	n := len(nums)
	var idx int = 0
	for i := 0; i < n; i++ {
		if nums[i] == 0 {
			continue
		}
		if i > idx {
			nums[idx] = nums[i]
		}
		idx++
	}
	// set zero
	for i := idx; i < n; i++ {
		nums[i] = 0
	}
}