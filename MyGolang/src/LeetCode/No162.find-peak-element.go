/*
No162.find-peak-element
*/

// method 1: bio-search
func findPeakElement1(nums []int) int {
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

// methord 2: rand iterator
func findPeakElement2(nums []int) int {
	n := len(nums)

	// find a rand i
	i := rand.Intn(n)

	var getVal func(int) int
	getVal = func(idx int) int {
		if idx < 0 || idx >= n {
			return math.MinInt64
		}
		return nums[idx]
	}

	for {
		// 若为峰值，返回
		if getVal(i) > getVal(i-1) && getVal(i) > getVal(i+1) {
			return i
		}
		if getVal(i) < getVal(i+1) {
			i++
		} else {
			i--
		}
	}
	return 0
}