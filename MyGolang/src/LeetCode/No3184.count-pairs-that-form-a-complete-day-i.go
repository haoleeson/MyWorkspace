/*
No3184.count-pairs-that-form-a-complete-day-i
*/

func Cn2(a int) int {
    if a < 2 {
        return 0
    }
    return a * (a - 1) / 2
}

func countCompleteDayPairs(hours []int) int {
    cnt := make([]int, 24)

    // cnt mod hour
    for _, hour := range hours {
        cnt[hour%24]++
    }

    ans := Cn2(cnt[0]) + Cn2(cnt[12])
    for i:=1; i<12; i++ {
        ans += cnt[i] * cnt[24-i]
    }
    return ans
}