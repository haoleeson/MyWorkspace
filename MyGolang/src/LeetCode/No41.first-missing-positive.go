/*
No41.first-missing-positive
*/
func firstMissingPositive(nums []int) int {
	n := len(nums)
	MAX_VAL := n + 1

	var abs func(int) int
	abs = func(num int) int {
		if num < 0 {
			return -num
		}
		return num
	}

	// mark all <= 0 num as MAX_VAL, ignore
	for i := 0; i < n; i++ {
		if nums[i] <= 0 {
			nums[i] = MAX_VAL
		}
	}

	// mark [0, n] num existed with num idx
	for i, tmpVal := 0, 0; i < n; i++ {
		tmpVal = abs(nums[i])
		if tmpVal <= n && nums[tmpVal-1] > 0 {
			nums[tmpVal-1] = -nums[tmpVal-1]
		}
	}

	// find first not negtive idx, the ans is idx+1
	for i := 0; i < n; i++ {
		if nums[i] > 0 {
			return i + 1
		}
	}

	return MAX_VAL
}
