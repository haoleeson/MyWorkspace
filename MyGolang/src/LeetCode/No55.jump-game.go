/*
No55.jump-game
*/
func canJump(nums []int) bool {
	n := len(nums)
	maxIdx := 0

	for i, maxNextIdx := 0, 0; i < n && i <= maxIdx; i++ {
		maxNextIdx = i + nums[i]
		if maxNextIdx >= n-1 {
			return true
		}
		if maxNextIdx > maxIdx {
			maxIdx = maxNextIdx
		}
	}

	return false
}
