/*
No1366.rank-teams-by-votes
*/
func better(orderBucketCnt [][]int, teamNum, a, b int) bool {
	for i := 0; i < teamNum; i++ {
		if orderBucketCnt[i][a] == orderBucketCnt[i][b] {
			continue
		}
		return orderBucketCnt[i][a] > orderBucketCnt[i][b]
	}
	return a < b
}

func rankTeams(votes []string) string {
	teamNum := len(votes[0])
	ans := make([]byte, teamNum)

	// count order
	orderBucketCnt := make([][]int, teamNum)
	for i := 0; i < teamNum; i++ {
		orderBucketCnt[i] = make([]int, 26)
	}
	for _, v := range votes {
		for i := 0; i < teamNum; i++ {
			orderBucketCnt[i][v[i]-'A']++
		}
	}

	// order
	orderedF := make([]bool, 26)
	ans_idx := 0
	for i := 0; i < teamNum; i++ {
		for {
			// find the bettest team from the least
			tmpMaxCnt, tmpMaxIdx := 0, -1
			for j := 0; j < 26; j++ {
				if orderedF[j] {
					continue
				}
				if orderBucketCnt[i][j] > tmpMaxCnt {
					tmpMaxCnt = orderBucketCnt[i][j]
					tmpMaxIdx = j
					continue
				}
				if orderBucketCnt[i][j] == tmpMaxCnt && tmpMaxIdx != -1 {
					if better(orderBucketCnt, teamNum, j, tmpMaxIdx) {
						tmpMaxIdx = j
					}
				}
			}
			// not found, break
			if tmpMaxIdx == -1 {
				break
			}
			ans[ans_idx] = 'A' + byte(tmpMaxIdx)
			ans_idx++
			orderedF[tmpMaxIdx] = true
			orderBucketCnt[i][tmpMaxIdx] = 0
		}
	}

	return string(ans)
}