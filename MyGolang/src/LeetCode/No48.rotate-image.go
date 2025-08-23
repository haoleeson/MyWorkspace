/*
No48.rotate-image
*/

func rotate(matrix [][]int) {
	n := len(matrix)
	if n < 2 {
		// no need rotate
		return
	}
	// printMatrix(matrix)

	var tmp, half int = 0, n / 2

	// 斜对角对称变换
	for i := 1; i < n; i++ {
		for j := 0; j < i; j++ {
			tmp = matrix[i][j]
			matrix[i][j] = matrix[j][i]
			matrix[j][i] = tmp
		}
	}

	// 垂直对称变换
	for i := 0; i < n; i++ {
		for j := 0; j < half; j++ {
			tmp = matrix[i][j]
			matrix[i][j] = matrix[i][n-1-j]
			matrix[i][n-1-j] = tmp
		}
	}

	// printMatrix(matrix)
}

func printMatrix(matrix [][]int) {
	n := len(matrix)
	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			fmt.Printf("\t%d", matrix[i][j])
		}
		fmt.Println()
	}
	fmt.Println()
}