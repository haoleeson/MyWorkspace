/*
No221.maximal-square
*/

func maximalSquare(matrix [][]byte) int {
	m := len(matrix)
	n := len(matrix[0])

	// count row continue '1' byte num
	matrixRowCnt := make([][]int, m)
	for i := 0; i < m; i++ {
		matrixRowCnt[i] = make([]int, n)
		if matrix[i][0] == '1' {
			matrixRowCnt[i][0] = 1
		}
		for j := 1; j < n; j++ {
			if matrix[i][j] == '0' {
				matrixRowCnt[i][j] = 0
			} else {
				matrixRowCnt[i][j] = matrixRowCnt[i][j-1] + 1
			}
		}
	}

	// count column continue '1' byte num
	matrixColumnCnt := make([][]int, m)
	for i := 0; i < m; i++ {
		matrixColumnCnt[i] = make([]int, n)
	}
	for j := 0; j < n; j++ {
		if matrix[0][j] == '1' {
			matrixColumnCnt[0][j] = 1
		}
		for i := 1; i < m; i++ {
			if matrix[i][j] == '0' {
				matrixColumnCnt[i][j] = 0
			} else {
				matrixColumnCnt[i][j] = matrixColumnCnt[i-1][j] + 1
			}
		}
	}

	var maxLen, tmp int = 0, 0

	// squareCnt[i][j] 表明以 matrix[i][j] 为右下角的正方形的边长
	squareCnt := make([][]int, m)
	for i := 0; i < m; i++ {
		squareCnt[i] = make([]int, n)
		// column[0] is square
		if matrix[i][0] == '1' {
			squareCnt[i][0] = 1
			if maxLen == 0 {
				maxLen = 1
			}
		}
	}
	// row[0] is square
	for j := 1; j < n; j++ {
		if matrix[0][j] == '1' {
			squareCnt[0][j] = 1
			if maxLen == 0 {
				maxLen = 1
			}
		}
	}

	for i := 1; i < m; i++ {
		for j := 1; j < n; j++ {
			if matrix[i][j] == '0' {
				squareCnt[i][j] = 0
				continue
			}
			tmp = min(matrixRowCnt[i][j], matrixColumnCnt[i][j])
			squareCnt[i][j] = min(squareCnt[i-1][j-1]+1, tmp)
			if squareCnt[i][j] > maxLen {
				maxLen = squareCnt[i][j]
			}
		}
	}
	return maxLen * maxLen
}

func min(x, y int) int {
	if y < x {
		return y
	}
	return x
}