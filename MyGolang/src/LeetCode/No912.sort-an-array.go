/*
No912.sort-an-array
*/
func sortArray(nums []int) []int {
	quickSort(nums)
	return nums
}

func quickSort(nums []int) {
	n := len(nums)
	if n <= 1 {
		return
	}

	// rand choose partition
	randIdx := rand.IntN(n)
	partition := nums[randIdx]
	nums[randIdx], nums[0] = nums[0], nums[randIdx]

	// sort nums as two part: [... ,partition) and [partition, ...]
	i, j := -1, n
	for i < j {
		// find a num in left part which >= partition
		i++
		for nums[i] < partition {
			i++
		}

		// find a num in right part which <= partition
		j--
		for nums[j] > partition {
			j--
		}

		// swap those two invalid index nums
		if i < j {
			nums[i], nums[j] = nums[j], nums[i]
		}
	}

	// divide
	quickSort(nums[:i])
	quickSort(nums[i:])
}