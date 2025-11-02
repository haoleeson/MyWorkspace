/*
No442.find-all-duplicates-in-an-array
*/

func findDuplicates(nums []int) []int {
	n := len(nums)
	dupNumList := make([]int, 0)

	var abs func(int) int
	abs = func(x int) int {
		if x < 0 {
			return -x
		}
		return x
	}

	for i := 0; i < n; i++ {
		num := abs(nums[i])
		// check existed?
		if nums[num-1] < 0 {
			dupNumList = append(dupNumList, num)
		} else {
			// add existed flag
			nums[num-1] = -nums[num-1]
		}
	}

	return dupNumList
}
