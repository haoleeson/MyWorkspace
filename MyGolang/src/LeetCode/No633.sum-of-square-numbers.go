/*
No633.sum-of-square-numbers
*/

func isSqrtNum(n int) bool {
    a := int(math.Sqrt(float64(n)))
    return a * a == n
}

func judgeSquareSum(c int) bool {
    maxT := int(math.Sqrt(float64(c)))
    for i:= maxT; i >= 0; i-- {
        if isSqrtNum(c - i * i) {
            return true
        }
    }
    return false
}