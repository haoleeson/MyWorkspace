/*
No1.two-sum
*/

// 2025-12-04 recoding
func twoSum(nums []int, target int) []int {
	preNeedMap := make(map[int]int)

	for i, num := range nums {
		if idx, existed := preNeedMap[num]; existed {
			return []int{idx, i}
		} else {
			preNeedMap[target-num] = i
		}
	}
	return []int{-1, -1}
}

func twoSum0(nums []int, target int) []int {
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