/*
No2588.count-the-number-of-beautiful-subarrays
*/
func beautifulSubarrays(nums []int) int64 {
	var ret int64 = 0
	cnt := make(map[int]int)
	cnt[0] = 1
	mask := 0

	for _, num := range nums {
		mask ^= num
		ret += int64(cnt[mask])
		cnt[mask]++
	}
	return ret
}