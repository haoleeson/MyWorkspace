/*
LCR.121.er-wei-shu-zu-zhong-de-cha-zhao-lcof
*/

func findTargetIn2DPlants(plants [][]int, target int) bool {
	m := len(plants)
	if m == 0 {
		return false
	}
	n := len(plants[0])
	if n == 0 {
		return false
	}

	var l, r, mid int
	for i := 0; i < m; i++ {
		if plants[i][0] > target {
			return false
		}
		if plants[i][n-1] < target {
			continue
		}

		l, r = 0, n-1
		for l <= r {
			mid = (l + r) / 2
			if plants[i][mid] > target {
				r = mid - 1
			} else if plants[i][mid] < target {
				l = mid + 1
			} else {
				return true
			}
		}
	}

	return false
}
