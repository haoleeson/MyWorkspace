/*
No26.remove-duplicates-from-sorted-array
*/

func removeDuplicates(nums []int) int {
	n := len(nums)
	idx := 0

	for i := 0; i < n; i++ {
		nums[idx] = nums[i]
		idx++
		for i+1 < n && nums[i] == nums[i+1] {
			i++
		}
	}
	return idx
}