/*
No3046.split-the-array
*/

func isPossibleToSplit(nums []int) bool {
	count := make([]int, 101)

	for _, num := range nums {
		count[num]++
		if count[num] > 2 {
			return false
		}
	}
	return true
}