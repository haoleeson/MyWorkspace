/*
LCR127.qing-wa-tiao-tai-jie-wen-ti-lcof
*/

func trainWays(num int) int {
	var dp_i, dp_i_1, dp_i_2 int64 = 1, 1, 0
	var modVal int64 = 1000000007

	for i := 1; i <= num; i++ {
		dp_i = (dp_i_1 + dp_i_2) % modVal

		dp_i_2 = dp_i_1
		dp_i_1 = dp_i
	}

	return int(dp_i)
}
