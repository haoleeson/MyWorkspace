/*
No2070.most-beautiful-item-for-each-query
*/
func maximumBeauty(items [][]int, queries []int) []int {
	m := make(map[int]int)
	for _, item := range items {
		if v, existed := m[item[0]]; !existed {
			m[item[0]] = item[1]
		} else {
			m[item[0]] = max(v, item[1])
		}
	}

	lenPrices := len(m)
	priceSet := make([]int, lenPrices)
	idx := 0
	for k, _ := range m {
		priceSet[idx] = k
		idx++
	}
	sort.Ints(priceSet)

	beautySet := make([]int, lenPrices)
	beautySet[0] = m[priceSet[0]]
	for i := 1; i < lenPrices; i++ {
		beautySet[i] = max(beautySet[i-1], m[priceSet[i]])
	}

	minPrice := priceSet[0]
	maxPrice := priceSet[lenPrices-1]
	queryMaxBeauty := func(queryPrice int) int {
		if queryPrice < minPrice {
			return 0
		} else if queryPrice >= maxPrice {
			return beautySet[lenPrices-1]
		}

		l, r := 0, lenPrices-1
		for l < r {
			mid := (l + r) / 2
			if priceSet[mid] > queryPrice {
				r = mid
			} else {
				l = mid + 1
			}
		}
		return beautySet[l-1]
	}

	ans := make([]int, len(queries))
	idx = 0
	for _, query := range queries {
		ans[idx] = queryMaxBeauty(query)
		idx++
	}

	return ans
}