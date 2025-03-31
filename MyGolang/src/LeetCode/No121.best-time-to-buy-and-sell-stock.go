/*
No121.best-time-to-buy-and-sell-stock
*/
func maxProfit(prices []int) int {
	minVal, ret := prices[0], 0
	for _, price := range prices {
		minVal = min(minVal, price)
		ret = max(ret, price-minVal)
	}
	return ret
}