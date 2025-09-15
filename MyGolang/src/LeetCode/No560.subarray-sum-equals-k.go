/*
No560.subarray-sum-equals-k
*/
func subarraySum(nums []int, k int) int {
	n := len(nums)
	var cnt int = 0

	// curPreSum sum of nums[0...i]
	var curPreSum int = 0

	// mark history counts of sum value of nums[0...j]
	preSumCnt := map[int]int{}
	preSumCnt[0] = 1

	for i := 0; i < n; i++ {
		// calc cur pre sum nums[0...i]
		curPreSum += nums[i]

		// find nums(j...i] == k
		// means find history counts of sum value of nums[0...j], which == nums[0...i] - k
		if _, existed := preSumCnt[curPreSum-k]; existed {
			cnt += preSumCnt[curPreSum-k]
		}
		// 统计前缀和出现次数
		preSumCnt[curPreSum]++
	}
	return cnt
}