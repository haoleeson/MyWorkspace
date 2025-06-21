/*
No42.trapping-rain-water
*/
func trap(height []int) int {
	n := len(height)

	// find left max num
	leftMax := make([]int, n)
	leftMax[0] = height[0]
	for i := 1; i < n; i++ {
		leftMax[i] = max(leftMax[i-1], height[i])
	}

	// find right max num
	rightMax := make([]int, n)
	rightMax[n-1] = height[n-1]
	for i := n - 2; i >= 0; i-- {
		rightMax[i] = max(rightMax[i+1], height[i])
	}

	// iterator diff height of rainHeight
	var accumulateRain, rainHeight int = 0, 0
	for i := 1; i < n-1; i++ {
		rainHeight = min(leftMax[i], rightMax[i])
		if rainHeight > height[i] {
			accumulateRain += rainHeight - height[i]
		}
	}

	return accumulateRain
}