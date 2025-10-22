/*
No518.coin-change-ii
*/

func change(amount int, coins []int) int {
	var chkHasRes func() bool
	chkHasRes = func() bool {
		valid := make([]bool, amount+1)
		valid[0] = true
		for _, coin := range coins {
			for i := coin; i <= amount; i++ {
				valid[i] = valid[i] || valid[i-coin]
			}
		}
		return valid[amount]
	}

	if !chkHasRes() {
		return 0
	}

	dp := make([]int, amount+1)
	dp[0] = 1

	// if for coins in inner, has duplicate result
	// for i := 1; i <= amount; i++ {
	// 	for _, coin := range coins {
	//         if i < coin {
	//             break
	//         }
	// 		dp[i] += dp[i-coin]
	// 	}
	//     fmt.Printf("dp[%d]: %d\n", i, dp[i])
	// }

	for _, coin := range coins {
		// add use coin
		for i := coin; i <= amount; i++ {
			dp[i] += dp[i-coin]
		}
	}

	return dp[amount]
}
