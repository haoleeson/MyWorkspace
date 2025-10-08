/*
No739.daily-temperatures
*/
func dailyTemperatures(temperatures []int) []int {
	n := len(temperatures)
	ans := make([]int, n)
	leftMaxTemp := temperatures[n-1]

	for i := n - 2; i >= 0; i-- {
		if temperatures[i] >= leftMaxTemp {
			ans[i] = 0
			leftMaxTemp = temperatures[i]
			continue
		}

		j := i + 1
		for j < n {
			if temperatures[j] > temperatures[i] {
				break
			}
			j += ans[j]
		}
		ans[i] = j - i
	}
	return ans
}