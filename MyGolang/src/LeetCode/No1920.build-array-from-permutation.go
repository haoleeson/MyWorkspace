/*
No1920.build-array-from-permutation
*/
func buildArray(nums []int) []int {
	n := len(nums)
	ans := make([]int, n)

	for i := 0; i < n; i++ {
		ans[i] = nums[nums[i]]
	}
	return ans
}