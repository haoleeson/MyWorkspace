/*
No2080.range-frequency-queries
*/
type RangeFreqQuery struct {
	m map[int][]int
}

func Constructor(arr []int) RangeFreqQuery {
	m := make(map[int][]int)
	for i, v := range arr {
		m[v] = append(m[v], i)
	}
	return RangeFreqQuery{m: m}
}

func (this *RangeFreqQuery) Query(left int, right int, value int) int {
	a, existed := this.m[value]
	if !existed {
		return 0
	}

	l := leftFind(a, left)
	r := rightFind(a, right)
	return r - l
}

func leftFind(a []int, v int) int {
	l, r := 0, len(a)-1
	for l <= r {
		mid := (l + r) / 2
		if a[mid] < v {
			l = mid + 1
		} else {
			r = mid - 1
		}
	}
	return l
}

func rightFind(a []int, v int) int {
	l, r := 0, len(a)-1
	for l <= r {
		mid := (l + r) / 2
		if a[mid] <= v {
			l = mid + 1
		} else {
			r = mid - 1
		}
	}
	return l
}
