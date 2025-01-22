/*
No3097.shortest-subarray-with-or-at-least-k-ii
*/

func bitsListAddNum(b []int, num int) {
	for i := 0; i < 30; i++ {
		b[i] += (num >> i) & 1
	}
}

func bitsListSubNum(b []int, num int) {
	for i := 0; i < 30; i++ {
		b[i] -= (num >> i) & 1
	}
}

func bitsListToNum(b []int) int {
	n := 0
	for i := 0; i < len(b); i++ {
		if b[i] > 0 {
			n |= 1 << i
		}
	}
	return n
}

func minimumSubarrayLength(nums []int, k int) int {
	n := len(nums)
	ret := math.MaxInt32
	bitSum := make([]int, 30)

	// slip window [i,j]
	for i, j := 0, 0; j < n; j++ {

		// move j to right
		bitsListAddNum(bitSum, nums[j])

		// try move i to right to find smaller slip window
		for i <= j && bitsListToNum(bitSum) >= k {
			ret = min(ret, j-i+1)
			bitsListSubNum(bitSum, nums[i])
			i++
		}
	}

	if ret == math.MaxInt32 {
		return -1
	}
	return ret
}


