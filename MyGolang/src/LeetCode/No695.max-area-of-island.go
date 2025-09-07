/*
No695.max-area-of-island
*/

func maxAreaOfIsland(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])
	var ret, area = 0, 0

	visit := make([][]bool, m)
	for i := 0; i < m; i++ {
		visit[i] = make([]bool, n)
	}

	var getValue func(int, int) int
	getValue = func(x, y int) int {
		if grid[x][y] == 0 {
			return 0
		}

		tmp := 1
		visit[x][y] = true

		// UP
		if x-1 >= 0 && !visit[x-1][y] {
			tmp += getValue(x-1, y)
		}

		// DOWN
		if x+1 < m && !visit[x+1][y] {
			tmp += getValue(x+1, y)
		}

		// LEFT
		if y-1 >= 0 && !visit[x][y-1] {
			tmp += getValue(x, y-1)
		}

		// RIGHT
		if y+1 < n && !visit[x][y+1] {
			tmp += getValue(x, y+1)
		}

		return tmp
	}

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if visit[i][j] {
				continue
			}

			area = getValue(i, j)
			if area > ret {
				ret = area
			}
		}
	}

	return ret
}