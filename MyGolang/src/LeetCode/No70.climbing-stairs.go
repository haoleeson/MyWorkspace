/*
No70.climbing-stairs
*/

func climbStairs(n int) int {
	if n < 2 {
		return 1
	}

	// dp_n = dp_n_1 + dp_n_2
	dp_n_2 := 1
	dp_n_1 := 1
	dp_n := 0
	for i := 2; i <= n; i++ {
		dp_n = dp_n_1 + dp_n_2
		dp_n_2 = dp_n_1
		dp_n_1 = dp_n
	}

	return dp_n
}