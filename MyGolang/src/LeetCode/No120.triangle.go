/*
No120.triangle
*/

func minimumTotal(triangle [][]int) int {
	n := len(triangle)

	dp_last := make([]int, n)
	dp_this := make([]int, n)
	dp_last[0] = triangle[0][0]
	dp_this[0] = triangle[0][0]

	var min func(int, int) int
	min = func(x, y int) int {
		if y < x {
			return y
		}
		return x
	}

	for i := 1; i < n; i++ {
		// each row fist node, only one path
		dp_this[0] = dp_last[0] + triangle[i][0]
		// each row last node, only one path
		dp_this[i] = dp_last[i-1] + triangle[i][i]
		// each row other node, i or i-1
		for j := 1; j < i; j++ {
			dp_this[j] = min(dp_last[j], dp_last[j-1]) + triangle[i][j]
		}
		// copy dp_this to dp_last
		for j := 0; j <= i; j++ {
			dp_last[j] = dp_this[j]
		}
	}

	// choose the most min path
	miniPast := dp_this[0]
	for i := 1; i < n; i++ {
		if dp_this[i] < miniPast {
			miniPast = dp_this[i]
		}
	}
	return miniPast
}
