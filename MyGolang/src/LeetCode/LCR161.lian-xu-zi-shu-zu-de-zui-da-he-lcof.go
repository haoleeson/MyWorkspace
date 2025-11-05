/*
LCR161.lian-xu-zi-shu-zu-de-zui-da-he-lcof
*/

func maxSales(sales []int) int {
	n := len(sales)
	ret := sales[0]

	dp_i, dp_i_1 := 0, sales[0]

	for i := 1; i < n; i++ {
		// dp
		if sales[i]+dp_i_1 > sales[i] {
			// choose last
			dp_i = sales[i] + dp_i_1
		} else {
			// non choose last
			dp_i = sales[i]
		}

		if dp_i > ret {
			ret = dp_i
		}

		dp_i_1 = dp_i
	}

	return ret
}
