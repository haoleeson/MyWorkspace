/*
No498.diagonal-traverse
*/

func findDiagonalOrder(mat [][]int) []int {
	m, n := len(mat), len(mat[0])
	totalElem := m * n
	ret := make([]int, totalElem)
	idx := 0

	isArrowLeftDown := false
	i, j := 0, 0
	diagTime := 0

	for {
		if isArrowLeftDown {
			// arrow Left Down

			// calc start point
			if diagTime < n {
				j, i = diagTime, 0
			} else {
				j, i = n-1, diagTime-n+1
			}

			// iterator left down
			for j >= 0 && i < m {
				ret[idx] = mat[i][j]
				idx++
				i++
				j--
			}
		} else {
			// arrow Right Up

			// calc start point
			if diagTime < m {
				i, j = diagTime, 0
			} else {
				i, j = m-1, diagTime-m+1
			}

			// iterator right up
			for i >= 0 && j < n {
				ret[idx] = mat[i][j]
				idx++
				i--
				j++
			}
		}

		if idx >= totalElem {
			break
		}
		diagTime++
		isArrowLeftDown = !isArrowLeftDown
	}

	return ret

}