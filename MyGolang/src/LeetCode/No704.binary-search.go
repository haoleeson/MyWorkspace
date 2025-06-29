/*
No704.binary-search
*/

func search(nums []int, target int) int {
	l, mid, r := 0, 0, len(nums)-1

	for l <= r {
		mid = (l + r) / 2
		if nums[mid] > target {
			r = mid - 1
		} else if nums[mid] < target {
			l = mid + 1
		} else {
			return mid
		}
	}
	return -1
}