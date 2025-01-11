/*
No3297.count-substrings-that-can-be-rearranged-to-contain-a-string-i
*/

// func isAContainsB(a, b []int) bool {
// 	for i := 0; i < 26; i++ {
// 		if a[i] < b[i] {
// 			return false
// 		}
// 	}
// 	return true
// }

// func validSubstringCount(word1 string, word2 string) int64 {
// 	n1 := len(word1)
// 	n2 := len(word2)
// 	var ret int64 = 0

// 	// count word2 ch num
// 	chCmp := make([]int, 26)
// 	for i := 0; i < n2; i++ {
// 		chCmp[word2[i]-'a']++
// 	}

// 	// double pointer
// 	chCnt0ToR := make([]int, 26)
//     tmpCnt := make([]int, 26)
	

// 	for r := 0; r < n1; r++ {
//         chCnt0ToR[word1[r]-'a']++

// 		// acc, move r until vaild
// 		for !isAContainsB(chCnt0ToR, chCmp) && r+1 < n1 {
// 			r++
// 			chCnt0ToR[word1[r]-'a']++
// 		}
// 		// break
// 		if r >= n1 {
// 			break
// 		}

// 		// continue move l with smallest vaild [l,r]
//         l := 0
//         copy(tmpCnt, chCnt0ToR)
//         for isAContainsB(tmpCnt, chCmp)  {
//             tmpCnt[word1[l]-'a']--
//             l++
//         }
//         l--

//         ret += int64(l + 1)
// 	}

// 	return ret
// }

func validSubstringCount(word1 string, word2 string) int64 {
    diff := make([]int, 26)
    for _, c := range word2 {
        diff[c - 'a']--
    }
    cnt := 0
    for _, c := range diff {
        if c < 0 {
            cnt++
        }
    }
    var res int64
    l, r := 0, 0
    for l < len(word1) {
        for r < len(word1) && cnt > 0 {
            update(diff, int(word1[r] - 'a'), 1, &cnt)
            r++
        }
        if cnt == 0 {
            res += int64(len(word1) - r + 1)
        }
        update(diff, int(word1[l]-'a'), -1, &cnt)
        l++
    }

    return res
}

func update(diff []int, c, add int, cnt *int) {
    diff[c] += add
    if add == 1 && diff[c] == 0 {
        // 表明 diff[c] 由 -1 变为 0
        *cnt--
    } else if add == -1 && diff[c] == -1 {
        // 表明 diff[c] 由 0 变为 -1
        *cnt++
    }
}
