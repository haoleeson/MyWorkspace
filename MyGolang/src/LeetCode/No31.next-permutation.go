/*
No31.next-permutation
*/

func nextPermutation(nums []int) {
	n := len(nums)

	var reverse func(int, int)
	reverse = func(startIdx, endIdx int) {
		for startIdx < endIdx {
			nums[startIdx], nums[endIdx] = nums[endIdx], nums[startIdx]
			startIdx++
			endIdx--
		}
	}

	// find pair smaller, a[i] < a[i+1]
	i := n - 2
	for i >= 0 && nums[i] >= nums[i+1] {
		i--
	}
	// not found
	if i < 0 {
		reverse(0, n-1)
		return
	}

	// find pair bigger, a[j] > a[i], j: [i+1, n)
	j := n - 1
	for j >= 0 && nums[j] <= nums[i] {
		j--
	}

	// swap a[i], a[j]
	nums[i], nums[j] = nums[j], nums[i]

	reverse(i+1, n-1)
}
