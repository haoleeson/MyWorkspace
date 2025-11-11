/*
No45.jump-game-ii
*/

// O(n)
func jump(nums []int) int {
	n := len(nums)
	n_1 := n - 1

	var max func(int, int) int
	max = func(x, y int) int {
		if y > x {
			return y
		}
		return x
	}

	maxIdx, step, stepEndIdx := 0, 0, 0
	for i := 0; i < n_1; i++ {
		maxIdx = max(maxIdx, i+nums[i])

		// reach step end, update step and next stepEndIdx
		if i == stepEndIdx {
			stepEndIdx = maxIdx
			step++
		}
	}
	return step
}

// O(n^2)
func jump0(nums []int) int {
	n := len(nums)
	n_1 := n - 1

	var min func(int, int) int
	min = func(x, y int) int {
		if y < x {
			return y
		}
		return x
	}

	dp := make([]int, n)
	for i := 1; i < n; i++ {
		dp[i] = n_1
	}

	for i := 0; i < n_1; i++ {
		if i+nums[i] >= n_1 {
			return dp[i] + 1
		}

		for j := i + 1; j <= i+nums[i]; j++ {
			dp[j] = min(dp[j], dp[i]+1)
		}
	}
	return dp[n_1]
}
