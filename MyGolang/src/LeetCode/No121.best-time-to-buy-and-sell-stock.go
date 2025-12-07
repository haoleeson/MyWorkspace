/*
No121.best-time-to-buy-and-sell-stock
*/
// 2025-12-08 recoding
func maxProfit(prices []int) int {
	profit := 0
	minPric := prices[0]

	var max func(int, int) int
	max = func(x, y int) int {
		if y > x {
			return y
		}
		return x
	}

	for _, price := range prices {
		if price <= minPric {
			minPric = price
		} else {
			profit = max(profit, price-minPric)
		}
	}

	return profit
}

func maxProfit0(prices []int) int {
	minVal, ret := prices[0], 0
	for _, price := range prices {
		minVal = min(minVal, price)
		ret = max(ret, price-minVal)
	}
	return ret
}