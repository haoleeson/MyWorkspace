/*
No16.3sum-closest
*/
func threeSumClosest(nums []int, target int) int {
	sort.Ints(nums)
	var ret, minDist int = 0, math.MaxInt32
	n := len(nums)

	var abs func(int) int
	abs = func(x int) int {
		if x < 0 {
			return -x
		}
		return x
	}

	for i := 0; i < n-2; i++ {
		tmpTarget, tmpDist := target-nums[i], 0
		l, r := i+1, n-1

		for l < r {
			tmpDist = tmpTarget - nums[l] - nums[r]
			if tmpDist > 0 {
				// target > a + b + c
				l++
			} else if tmpDist < 0 {
				// target < a + b + c
				r--
			} else {
				// target == a + b + c
				return target
			}
			if abs(tmpDist) < minDist {
				minDist = abs(tmpDist)
				// record sum of a+b+c
				ret = target - tmpDist
			}
		}
	}
	return ret
}