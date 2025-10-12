/*
No79.word-search
*/
func exist(board [][]byte, word string) bool {
	m := len(board)
	n := len(board[0])
	lenW := len(word)
	visitFlag := make([][]bool, m)
	for i := 0; i < m; i++ {
		visitFlag[i] = make([]bool, n)
	}

	var dfsCheck func(int, int, int) bool
	dfsCheck = func(x, y, wIdx int) bool {
		if visitFlag[x][y] {
			return false
		}
		if board[x][y] != word[wIdx] {
			return false
		}
		// if all char searched, return searched
		if wIdx == lenW-1 {
			return true
		}

		// set visit flag
		visitFlag[x][y] = true

		// try check next index char
		// UP
		if x > 0 {
			if dfsCheck(x-1, y, wIdx+1) {
				return true
			}
		}
		// DOWN
		if x+1 < m {
			if dfsCheck(x+1, y, wIdx+1) {
				return true
			}
		}
		// LEFT
		if y > 0 {
			if dfsCheck(x, y-1, wIdx+1) {
				return true
			}
		}
		// RIGHT
		if y+1 < n {
			if dfsCheck(x, y+1, wIdx+1) {
				return true
			}
		}

		// clear visit flag
		visitFlag[x][y] = false

		return false
	}

	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			if dfsCheck(i, j, 0) {
				return true
			}
		}
	}

	return false
}