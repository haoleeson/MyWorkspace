/*
No240.search-a-2d-matrix-ii
*/
func searchMatrix(matrix [][]int, target int) bool {
	m := len(matrix)
	n := len(matrix[0])

	var l, r, mid int
	for i := 0; i < m; i++ {
		if matrix[i][n-1] < target {
			continue
		}
		if matrix[i][0] > target {
			break
		}
		// search in line [i]
		l, r = 0, n-1
		for l <= r {
			mid = (l + r) / 2
			if matrix[i][mid] < target {
				l = mid + 1
			} else if matrix[i][mid] > target {
				r = mid - 1
			} else {
				return true
			}
		}
	}

	return false
}