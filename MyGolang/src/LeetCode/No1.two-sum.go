/*
No1.two-sum
*/
func twoSum(nums []int, target int) []int {
	n := len(nums)

	needNumMap := make(map[int]int)
	for i := 0; i < n; i++ {
		if idx, existed := needNumMap[nums[i]]; existed {
			return []int{i, idx}
		}
		needNumMap[target-nums[i]] = i
	}
	return []int{}
}