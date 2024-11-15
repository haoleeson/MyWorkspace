/*
No3239.minimum-number-of-flips-to-make-binary-grid-palindromic-i
*/
func minFlips(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])

	// row
	cntRow := 0
	for i := 0; i < m; i++ {
		for j := 0; j < n/2; j++ {
			if grid[i][j] != grid[i][n-1-j] {
				cntRow++
			}
		}
	}

	// column
	cntColumn := 0
	for j := 0; j < n; j++ {
		for i := 0; i < m/2; i++ {
			if grid[i][j] != grid[m-1-i][j] {
				cntColumn++
			}
		}
	}
	return min(cntRow, cntColumn)
}