/*
No3244.shortest-distance-after-road-addition-queries-ii
*/

func shortestDistanceAfterQueries(n int, queries [][]int) []int {
	roads := make([]int, n)
	for i := 0; i < n; i++ {
		roads[i] = i + 1
	}
	lenQ := len(queries)

	ans := make([]int, lenQ)
	dist := n - 1

	i := 0
	for _, q := range queries {
		l, r := q[0], q[1]

		k := roads[l]
		for k != -1 && k < r {
			if k < r {
				roads[l] = r
			}
			k, roads[k] = roads[k], -1
			dist--
		}
		ans[i] = dist
		i++
	}
	return ans
}