/*
LCR187.yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof
*/

func iceBreakingGame(num int, target int) int {
    idx := 0
    for i:=2; i<=num; i++ {
        idx = (idx+target)%i
    }
    return idx
}

// simulate, over time
func iceBreakingGame0(num int, target int) int {
	numFlag := make([]bool, num)

	var findNextKIdx func(int, int) int
	findNextKIdx = func(idx, k int) int {
		// find from [idx, num-1]
		for i := idx; i < num; i++ {
			if !numFlag[i] {
				k--
				if k == 0 {
					return i
				}
			}
		}
		// find from [0, idx-1]
		for i := 0; i < idx; i++ {
			if !numFlag[i] {
				k--
				if k == 0 {
					return i
				}
			}
		}
		return 0
	}

	lastIdx, choseIdx := 0, 0
	for cnt := num; cnt > 1; cnt-- {
		// choose the target next index
		if cnt < target {
            choseIdx = findNextKIdx(lastIdx, 1 + (target-1)%cnt)
        } else {
            choseIdx = findNextKIdx(lastIdx, target)
        }
        
		// mark leave
		numFlag[choseIdx] = true
		// update last idx
		lastIdx = choseIdx
	}

    // only one num leaft, find the 1 next index as ans
	return findNextKIdx(lastIdx, 1)
}
