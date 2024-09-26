/*
No2306.naming-a-company
*/

// 法1：暴力解法、超时
func distinctNames1(ideas []string) int64 {
	n := len(ideas)
	m := make(map[string]bool, 0)

	// mark ideas
	for _, idea := range ideas {
		m[idea] = true
	}

	var ans int64 = 0
	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			idea1 := ideas[j][:1] + ideas[i][1:]
			idea2 := ideas[i][:1] + ideas[j][1:]
			if _, ok := m[idea1]; ok {
				continue
			}
			if _, ok := m[idea2]; ok {
				continue
			}
			ans += 2
		}
	}

	return ans
}

// function: count the number of same string between two shuffle group
func cntSameFunc(a, b map[string]struct{}) int {
	cnt := 0
	for shuffle, _ := range a {
		if _, existed := b[shuffle]; existed {
			cnt++
		}
	}
	return cnt
}

// 法2：map映射 + 全排列
func distinctNames(ideas []string) int64 {
	// mark ideas pre char and shuffle group
	m := make(map[byte]map[string]struct{}, 0)
	for _, idea := range ideas {
		if _, existed := m[idea[0]]; !existed {
			m[idea[0]] = make(map[string]struct{}, 0)
		}
		m[idea[0]][idea[1:]] = struct{}{}
	}

	// full mesh of two idea
	var ans int64 = 0
	for k1, v1 := range m {
		for k2, v2 := range m {
			if k1 == k2 {
				continue
			}
			sameCnt := cntSameFunc(v1, v2)
			ans += int64(len(v1)-sameCnt) * int64(len(v2)-sameCnt)
		}
	}

	return ans
}