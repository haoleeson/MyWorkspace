/*
No200.number-of-islands
*/
func bfs(grid [][]byte, visitFlag [][]bool, x, y, m, n int) {
	visitFlag[x][y] = true
	// up
	if y-1 >= 0 && !visitFlag[x][y-1] && grid[x][y-1] == '1' {
		bfs(grid, visitFlag, x, y-1, m, n)
	}
	// down
	if y+1 < n && !visitFlag[x][y+1] && grid[x][y+1] == '1' {
		bfs(grid, visitFlag, x, y+1, m, n)
	}
	// left
	if x-1 >= 0 && !visitFlag[x-1][y] && grid[x-1][y] == '1' {
		bfs(grid, visitFlag, x-1, y, m, n)
	}
	// right
	if x+1 < m && !visitFlag[x+1][y] && grid[x+1][y] == '1' {
		bfs(grid, visitFlag, x+1, y, m, n)
	}
}

func numIslands(grid [][]byte) int {
	m := len(grid)
	n := len(grid[0])

	visitFlag := make([][]bool, m)
	for i := 0; i < m; i++ {
		visitFlag[i] = make([]bool, n)
	}

	ret := 0
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if visitFlag[i][j] || grid[i][j] == '0' {
				continue
			}
			ret++
			bfs(grid, visitFlag, i, j, m, n)
		}
	}
	return ret
}
