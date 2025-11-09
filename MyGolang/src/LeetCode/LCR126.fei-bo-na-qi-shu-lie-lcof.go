/*
LCR126.fei-bo-na-qi-shu-lie-lcof
*/

func fib(n int) int {
	switch n {
	case 0:
		return 0
	case 1:
		return 1
	}

	var f_i, f_i_1, f_i_2 int = 0, 1, 0
	var modVal int = 1000000007
	for i := 2; i <= n; i++ {
		f_i = (f_i_1 + f_i_2) % modVal
		f_i_2 = f_i_1
		f_i_1 = f_i
	}
	return f_i
}

