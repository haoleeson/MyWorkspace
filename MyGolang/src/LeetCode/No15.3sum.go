/*
No15.3sum
*/

func threeSum(nums []int) [][]int {
	n := len(nums)
	ret := make([][]int, 0)
	var needNum, tmpSum, l, r int
	sort.Ints(nums)

	rightMoveL := func() {
		l++
		for l < n && nums[l] == nums[l-1] {
			l++
		}
	}

	leftMoveR := func() {
		r--
		for r >= 0 && nums[r] == nums[r+1] {
			r--
		}
	}

	for i := 0; i < n; i++ {
		needNum = -nums[i]
		l, r = i+1, n-1

		for l < r {
			tmpSum = nums[l] + nums[r]
			if tmpSum < needNum {
				rightMoveL()
			} else if tmpSum > needNum {
				leftMoveR()
			} else {
				tmpList := []int{nums[i], nums[l], nums[r]}
				ret = append(ret, tmpList)
				rightMoveL()
				leftMoveR()
			}
		}
		// skip same nums[i]
		for i+1 < n && nums[i+1] == nums[i] {
			i++
		}
	}

	return ret
}