/*
No1061.lexicographically-smallest-equivalent-string
*/
func smallestEquivalentString(s1 string, s2 string, baseStr string) string {
	chIdxs := make([]map[byte]struct{}, 256)
	for i := 'a'; i <= 'z'; i++ {
		chIdxs[i] = make(map[byte]struct{})
	}
	sLen := len(s1)

	// add each ch index
	for i := 0; i < sLen; i++ {
		if s1[i] == s2[i] {
			continue
		}
		chIdxs[s1[i]][s2[i]] = struct{}{}
		chIdxs[s2[i]][s1[i]] = struct{}{}
	}

	// fmt.Println("debug print chIdxs:")
	// for i := 'a'; i <= 'z'; i++ {
	// 	if len(chIdxs[i]) > 0 {
	// 		fmt.Printf(string([]byte{byte(i)}) + ": {")
	// 	}
	// 	for ch := range chIdxs[i] {
	// 		fmt.Printf(" " + string([]byte{ch}))
	// 	}
	// 	if len(chIdxs[i]) > 0 {
	// 		fmt.Println("}")
	// 	}
	// }

	smallSetList := make([]map[byte]struct{}, 0)
	findFlag := make([]bool, 256)

	var combineGroupSet func(b byte) map[byte]struct{}
	combineGroupSet = func(b byte) map[byte]struct{} {
		if findFlag[b] {
			return make(map[byte]struct{})
		}
		findFlag[b] = true
		if len(chIdxs[b]) == 0 {
			return make(map[byte]struct{})
		}

		smallSet := make(map[byte]struct{})
		for ch := range chIdxs[b] {
			smallSet[ch] = struct{}{}
			subSmallSet := combineGroupSet(ch)
			for ch2 := range subSmallSet {
				smallSet[ch2] = struct{}{}
			}
		}
		return smallSet
	}

	for i := 'a'; i <= 'z'; i++ {
		if findFlag[i] {
			continue
		}
		if len(chIdxs[i]) == 0 {
			continue
		}

		smallGroupSet := combineGroupSet(byte(i))
		smallSetList = append(smallSetList, smallGroupSet)
	}

	// find the smallest char of each group
	smallestMap := make([]byte, 256)
	for _, smallGroupSet := range smallSetList {
		var eachGroupSmallestCh byte = 'z'
		for ch := range smallGroupSet {
			if ch < eachGroupSmallestCh {
				eachGroupSmallestCh = ch
			}
		}
		// smallest char map
		for ch := range smallGroupSet {
			smallestMap[ch] = eachGroupSmallestCh
		}
	}

	// fmt.Println("debug print smallSetList:")
	// for _, smallGroupSet := range smallSetList {
	// 	var eachGroupSmallestCh byte = 0
	// 	fmt.Print("{")
	// 	for ch := range smallGroupSet {
	// 		fmt.Print(" " + string([]byte{ch}))
	// 		if eachGroupSmallestCh == 0 {
	// 			eachGroupSmallestCh = smallestMap[ch]
	// 		}
	// 	}
	// 	fmt.Println("} : " + string([]byte{eachGroupSmallestCh}))
	// }

	baseStrLen := len(baseStr)
	result := make([]byte, baseStrLen)
	for i := 0; i < baseStrLen; i++ {
		smallestMapCh := smallestMap[baseStr[i]]
		if smallestMapCh != 0 {
			result[i] = smallestMapCh
		} else {
			result[i] = baseStr[i]
		}
	}
	return string(result)

}
