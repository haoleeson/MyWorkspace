/*
No3240.minimum-number-of-flips-to-make-binary-grid-palindromic-ii
*/

func minFlips(grid [][]int) int {
	m := len(grid)
	n := len(grid[0])
	ans := 0

	var pointOne, pointZero int = 0, 0
	var lineOne, lineZero int = 0, 0
	var cntOne, cntZero int
	var changeNum int = 0
	for i := 0; i < (m+1)/2; i++ {
		for j := 0; j < (n+1)/2; j++ {
			// cnt 4 part num
			cntOne = 0
			cntZero = 0

			// (i, j)
			cntOne += grid[i][j] ^ 0
			cntZero += grid[i][j] ^ 1

			// (i, n-1-j)
			if j != n-1-j {
				cntOne += grid[i][n-1-j] ^ 0
				cntZero += grid[i][n-1-j] ^ 1
			}

			// (m-1-i, j)
			if m-1-i != i {
				cntOne += grid[m-1-i][j] ^ 0
				cntZero += grid[m-1-i][j] ^ 1
			}

			// (m-1-i, n-1-j)
			if (m-1-i != i) && (j != n-1-j) {
				cntOne += grid[m-1-i][n-1-j] ^ 0
				cntZero += grid[m-1-i][n-1-j] ^ 1
			}

			// palindromic grid
			switch cntOne + cntZero {
			case 1:
				pointOne += cntOne
				pointZero += cntZero
			case 2:
				lineOne += cntOne
				lineZero += cntZero
				if cntOne == cntZero {
					changeNum += 1
					ans += 1
				}

			case 4:
				if cntOne == 0 || cntZero == 0 {
					continue
				}
				ans += min(cntOne, cntZero)
			}
		}
	}

	// mod 4
	if pointOne != 0 {
		ans += 1
	}

	cntNeedDel := (lineOne - changeNum) % 4
	switch cntNeedDel {
	case 2:
		if changeNum == 0 {
			ans += 2
		}

	}

	return ans
}