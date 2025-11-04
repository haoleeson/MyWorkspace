/*
LCR159.zui-xiao-de-kge-shu-lcof
*/

func inventoryManagement(stock []int, cnt int) []int {
	sort.Ints(stock)
	return stock[:cnt]
}
