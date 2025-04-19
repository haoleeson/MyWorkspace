/*
No2563.count-the-number-of-fair-pairs
*/
func countFairPairs(nums []int, lower int, upper int) int64 {
	n := len(nums)
	sort.Ints(nums)

	var ans int64 = 0
	var l, r, mid, target, lowIdx, upIdx int

	for i := 0; i < n && nums[i]*2 <= upper; i++ {
		// bioSearch smaller index
		l, r, target = i+1, n-1, lower-nums[i]
		for l <= r {
			mid = (r + l) / 2
			if nums[mid] >= target {
				r = mid - 1
			} else {
				l = mid + 1
			}
		}
		lowIdx = l

		// bioSearch bigger index
		l, r, target = i+1, n-1, upper-nums[i]
		for l <= r {
			mid = (l + r) / 2
			if nums[mid] <= target {
				l = mid + 1
			} else {
				r = mid - 1
			}
		}
		upIdx = r

		ans += int64(upIdx - lowIdx + 1)
	}
	return ans
}