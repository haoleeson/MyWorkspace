/*
No2012.sum-of-beauty-in-the-array
*/
func sumOfBeauties(nums []int) int {
	n := len(nums)
	minOfRight := make([]int, n)
	minOfRight[n-1] = nums[n-1]
	for i := n - 2; i >= 0; i-- {
		minOfRight[i] = min(minOfRight[i+1], nums[i])
	}

	ans := 0
	maxOfLeft := nums[0]
	for i := 1; i < n-1; i++ {
		if maxOfLeft < nums[i] && nums[i] < minOfRight[i+1] {
			ans += 2
		} else if nums[i-1] < nums[i] && nums[i] < nums[i+1] {
			ans++
		}
		maxOfLeft = max(maxOfLeft, nums[i])
	}
	return ans
}