// No162.find-peak-element
func findPeakElement(nums []int) int {
	n := len(nums)

	getNum := func(idx int) int {
		if idx == -1 || idx == n {
			return math.MinInt
		}
		return nums[idx]
	}

	l, r := 0, n-1
	for l < r {
		mid := (l + r) / 2

		// peak point
		if nums[mid] > getNum(mid-1) && nums[mid] > getNum(mid+1) {
			return mid
		}

		if nums[mid] < getNum(mid+1) {
			l = mid + 1
		} else {
			r = mid - 1
		}
	}
	return l
}