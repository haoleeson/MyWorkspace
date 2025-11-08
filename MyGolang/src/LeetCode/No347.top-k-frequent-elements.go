/*
No347.top-k-frequent-elements
*/

func topKFrequent(nums []int, k int) []int {
	// count each elems
	cntSet := make(map[int]int)
	for _, num := range nums {
		if cnt, exist := cntSet[num]; exist {
			cntSet[num] = cnt + 1
		} else {
			cntSet[num] = 1
		}
	}

	// group elems by cnt
	cntElemArr := make(map[int][]int)
	cntArr := make([]int, 0)
	for elem, cnt := range cntSet {
		if _, exist := cntElemArr[cnt]; !exist {
			cntElemArr[cnt] = make([]int, 0)
			cntArr = append(cntArr, cnt)
		}
		cntElemArr[cnt] = append(cntElemArr[cnt], elem)
	}

	// sort cnt array
	sort.Ints(cntArr)

	// output
	ret := make([]int, k)
    var idx int = 0
	for i := len(cntArr) - 1; idx < k && i >= 0; i-- {
		elemArr := cntElemArr[cntArr[i]]
		for _, elem := range elemArr {
			ret[idx] = elem
			idx++
			if idx == k {
				break
			}
		}
	}
	return ret
}
