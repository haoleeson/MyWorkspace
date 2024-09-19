/*
No2414.length-of-the-longest-alphabetical-continuous-substring
*/
func longestContinuousSubstring(s string) int {
    n := len(s)
    b := []byte(s)

    i := 0
    var ans, tmpL int = 0, 0
    for ; i < n; i++ {
        tmpL = 1
        for i + 1 < n && (b[i+1] - b[i]) == 1 {
            tmpL++
            i++
        }
        ans = max(ans, tmpL)
    }
    return ans
}
