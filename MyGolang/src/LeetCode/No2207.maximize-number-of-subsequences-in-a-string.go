/*
No2207.maximize-number-of-subsequences-in-a-string
*/

func maximumSubsequenceCount(text string, pattern string) int64 {
    n := len(text)
    t := []byte(text)

    // if the same char
    if pattern[0] == pattern[1] {
        var cntA, ansA int64 = 1, 0
        for i := 0; i < n; i++ {
            if t[i] == pattern[0] {
                ansA += cntA
                cntA++
            }
        }
        return ansA
    }

    // try add a in front
    var cntA, ansA int64 = 1, 0
    for i := 0; i < n; i++ {
        if t[i] == pattern[0] {
            cntA++
        } else if t[i] == pattern[1] {
            ansA += cntA
        }
    }

    // try add b in end
    var cntB, ansB int64 = 1, 0
    for i := n-1; i >= 0; i-- {
        if t[i] == pattern[1] {
            cntB++
        } else if t[i] == pattern[0] {
            ansB += cntB
        }
    }

    return max(ansA, ansB)
}