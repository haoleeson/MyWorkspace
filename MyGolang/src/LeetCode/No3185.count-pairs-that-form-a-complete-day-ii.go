/*
No3185.count-pairs-that-form-a-complete-day-ii
*/
func Cn2(a int) int64 {
	if a < 2 {
		return 0
	}
	return int64(a) * int64(a-1) / 2
}

func countCompleteDayPairs(hours []int) int64 {
	cnt := make([]int, 24)

	// cnt mod hour
	for _, hour := range hours {
		cnt[hour%24]++
	}

	ans := Cn2(cnt[0]) + Cn2(cnt[12])
	for i := 1; i < 12; i++ {
		ans += int64(cnt[i]) * int64(cnt[24-i])
	}
	return ans
}