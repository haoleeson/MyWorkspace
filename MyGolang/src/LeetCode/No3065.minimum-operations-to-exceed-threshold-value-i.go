/*
3065.minimum-operations-to-exceed-threshold-value-i
*/

func minOperations(nums []int, k int) int {
	sort.Ints(nums)

	// binary search
	l, r := 0, len(nums)-1
	for l <= r {
		mid := (l + r) / 2

		if k > nums[mid] {
			l = mid + 1
		} else {
			r = mid - 1
		}
	}

	return l
}