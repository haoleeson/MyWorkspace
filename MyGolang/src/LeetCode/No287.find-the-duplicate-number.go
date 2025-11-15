/*
No287.find-the-duplicate-number
*/

func findDuplicate(nums []int) int {
	// Floyd判圈算法
	// startPoint -> a -> inPoint -> b -> meetPoint -> c -> inPoint ...
	//
	// 2 (a + b) = a + b + k * L
	// a = k * L - b = (k-1) * L + (L - b) = (k-1) * L + c

	slow, fast := 0, 0
	// access meetPoint
	for slow, fast = nums[slow], nums[nums[fast]]; slow != fast; slow, fast = nums[slow], nums[nums[fast]] {
	}

	// a = (k-1) * L + c
	// slow step a, slow2 step (k-1) * L + c, remeet on meetPoint
	slow2 := slow
	// reset slow to startPoint
	slow = 0
	for slow != slow2 {
		slow = nums[slow]
		slow2 = nums[slow2]
	}
	return slow
}
