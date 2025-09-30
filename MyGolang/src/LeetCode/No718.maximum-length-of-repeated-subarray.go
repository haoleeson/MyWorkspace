/*
No718.maximum-length-of-repeated-subarray
*/

func findLength(nums1 []int, nums2 []int) int {
	var maxLen int = 0

	n, m := len(nums1), len(nums2)
	dp := make([][]int, n+1)
	for i := 0; i < n+1; i++ {
		dp[i] = make([]int, m+1)
	}

	for i := n - 1; i >= 0; i-- {
		for j := m - 1; j >= 0; j-- {
			if nums1[i] == nums2[j] {
				dp[i][j] = dp[i+1][j+1] + 1
				if dp[i][j] > maxLen {
					maxLen = dp[i][j]
				}
			} else {
				dp[i][j] = 0
			}
		}
	}

	return maxLen
}
