/*
No3164.find-the-number-of-good-pairs-ii
*/

func numberOfPairs(nums1 []int, nums2 []int, k int) int64 {
	var ans int64 = 0
	maxNum := 0
	count1 := make(map[int]int, 0)
	count2 := make(map[int]int, 0)

	for _, num := range nums1 {
		count1[num]++
		maxNum = max(maxNum, num)
	}

	for _, num := range nums2 {
		count2[num]++
	}

	// find good pairs
	for num, cnt := range count2 {
		for b := num * k; b <= maxNum; b += num * k {
			if v, existed := count1[b]; existed {
				ans += int64(v) * int64(cnt)
			}
		}
	}

	return ans
}