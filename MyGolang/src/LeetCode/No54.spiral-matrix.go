/*
No54.spiral-matrix
*/
func spiralOrder(matrix [][]int) []int {
	m := len(matrix)
	n := len(matrix[0])
	total := m * n
	ret := make([]int, total)
	idx := 0

	// direct:  0: right, 1: down, 2: left, 3: up
	direct := 0
	maxRight, maxDown, minLeft, minUp := n-1, m-1, 0, 1

	i, j := 0, 0
	for idx < total {
		switch direct {
		// right
		case 0:
			for j <= maxRight {
				ret[idx] = matrix[i][j]
				idx++
				j++
			}
			j--
			maxRight--
			i++
		// down
		case 1:
			for i <= maxDown {
				ret[idx] = matrix[i][j]
				idx++
				i++
			}
			i--
			maxDown--
			j--
		// left
		case 2:
			for j >= minLeft {
				ret[idx] = matrix[i][j]
				idx++
				j--
			}
			j++
			minLeft++
			i--
		// up
		case 3:
			for i >= minUp {
				ret[idx] = matrix[i][j]
				idx++
				i--
			}
			i++
			minUp++
			j++
		}

		direct = (direct + 1) % 4
	}

	return ret
}