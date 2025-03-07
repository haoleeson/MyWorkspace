/*
No2597.the-number-of-beautiful-subsets
*/
func beautifulSubsets(nums []int, k int) int {
	dp := make([][]int, 0)

	isBeautifulAdd := func(list []int, minNum, maxNum int) bool {
		for _, l := range list {
			if l == minNum || l == maxNum {
				return false
			}
		}
		return true
	}

	deepAdd := func(idx, num int) {
		tmpList := make([]int, len(dp[idx])+1)
		k := 0
		for k < len(dp[idx]) {
			tmpList[k] = dp[idx][k]
			k++
		}
		tmpList[k] = num
		dp = append(dp, tmpList)
	}

	for _, num := range nums {
		tmpLen := len(dp)
		for i := 0; i < tmpLen; i++ {
			if isBeautifulAdd(dp[i], num-k, num+k) {
				deepAdd(i, num)
			}
		}
		singleList := []int{num}
		dp = append(dp, singleList)
	}

	return len(dp)
}