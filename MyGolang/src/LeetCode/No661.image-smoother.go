/*
No661.image-smoother
*/

func imageSmoother(img [][]int) [][]int {
	m := len(img)
	n := len(img[0])

	ans := make([][]int, m)
	for i := 0; i < m; i++ {
		ans[i] = make([]int, n)
	}

	var tmpSum, tmpCnt int
	for i := 0; i < m; i++ {
		for j := 0; j < n; j++ {
			// (i, j)
			tmpSum, tmpCnt = img[i][j], 1

			// (i-1, j-1)
			if i-1 >= 0 && j-1 >= 0 {
				tmpSum += img[i-1][j-1]
				tmpCnt += 1
			}

			// (i-1, j)
			if i-1 >= 0 {
				tmpSum += img[i-1][j]
				tmpCnt += 1
			}

			// (i-1, j+1)
			if i-1 >= 0 && j+1 < n {
				tmpSum += img[i-1][j+1]
				tmpCnt += 1
			}

			// (i, j-1)
			if j-1 >= 0 {
				tmpSum += img[i][j-1]
				tmpCnt += 1
			}

			// (i,j+1)
			if j+1 < n {
				tmpSum += img[i][j+1]
				tmpCnt += 1
			}

			// (i+1, j-1)
			if i+1 < m && j-1 >= 0 {
				tmpSum += img[i+1][j-1]
				tmpCnt += 1
			}

			// (i+1, j)
			if i+1 < m {
				tmpSum += img[i+1][j]
				tmpCnt += 1
			}

			// (i+1, j+1)
			if i+1 < m && j+1 < n {
				tmpSum += img[i+1][j+1]
				tmpCnt += 1
			}

			ans[i][j] = tmpSum / tmpCnt

		}
	}

	return ans
}