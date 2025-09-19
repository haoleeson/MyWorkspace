/*
No152.maximum-product-subarray
*/

func maxProduct(nums []int) int {
	var preProduct_i, preProduct_i_1 int = 0, 1
	var hasNegPre bool = false
	var negMaxPreProduct int = math.MinInt32
	var ret, tmp int = math.MinInt32, 0

	for _, num := range nums {
		preProduct_i = preProduct_i_1 * num

		if preProduct_i > 0 {
			tmp = max(preProduct_i, num)
		} else if preProduct_i < 0 {
			if hasNegPre {
				tmp = max(preProduct_i/negMaxPreProduct, num)
			} else {
				tmp = max(preProduct_i, num)
				hasNegPre = true
			}
			negMaxPreProduct = max(negMaxPreProduct, preProduct_i)
		} else {
			// == 0
			tmp = max(0, num)
			// clear flag
			preProduct_i = 1
			hasNegPre = false
			negMaxPreProduct = math.MinInt32
		}

		if tmp > ret {
			ret = tmp
		}
		preProduct_i_1 = preProduct_i
	}

	return ret
}

func max(x, y int) int {
	if y > x {
		return y
	}
	return x
}
