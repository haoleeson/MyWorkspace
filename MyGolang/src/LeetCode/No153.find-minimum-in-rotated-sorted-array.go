/*
No153.find-minimum-in-rotated-sorted-array
*/

func findMin(nums []int) int {
	n := len(nums)
	l, r, mid := 0, n-1, 0

	for l < r {
		mid = (l + r) / 2
		if nums[mid] < nums[r] {
			r = mid
		} else {
			l = mid + 1
		}
	}
	return nums[l]
}