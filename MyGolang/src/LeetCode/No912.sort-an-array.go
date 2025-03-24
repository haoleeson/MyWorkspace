/*
No912.sort-an-array
*/
func sortArray(nums []int) []int {
	quickSort(nums, 0, len(nums)-1)
	return nums
}

func quickSort(nums []int, l, r int) {
	if l >= r {
		return
	}

	partition := nums[l]
	i, j := l-1, r+1

	for i < j {
		// find left invalid
		for i++; nums[i] < partition; i++ {
		}
		// find right invalid
		for j--; nums[j] > partition; j-- {
		}
		if i < j {
			nums[i], nums[j] = nums[j], nums[i]
		}
	}
	// left: nums[l, j], right: nums[j+1, r]
	quickSort(nums, l, j)
	quickSort(nums, j+1, r)
}