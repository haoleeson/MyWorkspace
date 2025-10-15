/*
No40.combination-sum-ii
*/

func combinationSum2(candidates []int, target int) [][]int {
	n := len(candidates)

	sort.Ints(candidates)
	visit := make([]bool, n)
	var path []int = make([]int, 0)
	ret := make([][]int, 0)

	var dfsSearch func(int, int)
	dfsSearch = func(startIdx, subTarget int) {
		// find
		if subTarget == 0 {
			ret = append(ret, append([]int(nil), path...))
			return
		}

		for i := startIdx; i < n; i++ {
			if visit[i] {
				continue
			}
			// acc
			if candidates[i] > subTarget {
				break
			}

			visit[i] = true
			path = append(path, candidates[i])
			dfsSearch(i+1, subTarget-candidates[i])
			path = path[:len(path)-1]
			visit[i] = false
			// skip same last visted and free num
			for ; i+1 < n && candidates[i+1] == candidates[i]; i++ {
			}
		}
	}

	dfsSearch(0, target)
	return ret
}