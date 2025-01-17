/*
No3295.shortest-subarray-with-or-at-least-k-i
*/

func minimumSubarrayLength(nums []int, k int) int {
	n := len(nums)
	ret := math.MaxInt

	// [i,j]
	for i := 0; i < n; i++ {
		tmp := 0
		for j := i; j < n; j++ {
			tmp |= nums[j]
			if tmp >= k {
				ret = min(ret, j-i+1)
				break
			}
		}
	}

	if ret == math.MaxInt {
		return -1
	}
	return ret
}