/*
No3258.count-substrings-that-satisfy-k-constraint-i
*/

func countKConstraintSubstrings(s string, k int) int {
    n := len(s)
    ans := 0

    // subStr[i:]
    for i:=0; i<n; i++ {
        // cnt 0 == k
        cntZero := 0
        cntOne := 0
        for j:=i; j < n; j++ {
            switch s[j] {
                case '0':
                    cntZero++
                case '1':
                    cntOne++
            }
            if cntZero > k && cntOne > k {
                break
            }
            ans++
        }
    }
    return ans
}