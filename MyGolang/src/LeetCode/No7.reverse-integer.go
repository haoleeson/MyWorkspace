/*
No7.reverse-integer
*/

func reverse(x int) int {
	var ans, d int = 0, 0
	for x != 0 {
		d = x % 10
		// pos
		if ans > 214748364 || (ans == 214748364 && d > 7) {
			return 0
		}
		// neg
		if ans < -214748364 || (ans == -214748364 && d < -8) {
			return 0
		}

		ans = ans*10 + d
		x /= 10
	}

	return ans
}
