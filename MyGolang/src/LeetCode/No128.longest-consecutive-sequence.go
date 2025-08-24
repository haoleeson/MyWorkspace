/*
No128.longest-consecutive-sequence
*/

func longestConsecutive(nums []int) int {
	numSet := make(map[int]struct{})
	for _, num := range nums {
		numSet[num] = struct{}{}
	}

	var maxLong, tmplogest, tmpNum int = 0, 0, 0
	for num := range numSet {
		// num-1 existed skip
		if _, existed := numSet[num-1]; existed {
			continue
		}

		// start count longest
		tmplogest = 1
		tmpNum = num + 1
		for {
			if _, existed := numSet[tmpNum]; !existed {
				break
			}
			tmplogest++
			tmpNum++
		}

		if tmplogest > maxLong {
			maxLong = tmplogest
		}
	}

	return maxLong
}