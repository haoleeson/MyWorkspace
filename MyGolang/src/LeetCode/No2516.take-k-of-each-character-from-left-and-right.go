/*
No2516.take-k-of-each-character-from-left-and-right
*/

func takeCharacters(s string, k int) int {
    n := len(s)
    ans := n
    
    // count chars
    cntCh := make([]int, 3)
    for i := 0; i < n; i++ {
        cntCh[s[i] - 'a']++
    }
    if cntCh[0] >= k && cntCh[1] >= k && cntCh[2] >= k {
        ans = min(ans, n)
    } else {
        return -1
    }

    // double pointer
    l := 0
    for r :=0; r < n; r++ {
        cntCh[s[r] - 'a']--
        for l < r && (cntCh[0] < k || cntCh[1] < k || cntCh[2] < k) {
            cntCh[s[l] - 'a']++
            l++
        }

        if cntCh[0] >= k && cntCh[1] >= k && cntCh[2] >= k {
            ans = min(ans, n - (r - l + 1))
        }
    }
    return ans
}