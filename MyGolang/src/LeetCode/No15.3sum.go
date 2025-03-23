/*
No15.3sum
*/

func threeSum(nums []int) [][]int {
	n := len(nums)
	ret := make([][]int, 0)
	var needNum int
	var tmpSum int

	sort.Ints(nums)

	for i := 0; i < n; i++ {
		needNum = -nums[i]

		l, r := i+1, n-1
		for l < r {
			tmpSum = nums[l] + nums[r]
			if tmpSum < needNum {
				l++
				for l < n && nums[l] == nums[l-1] {
					l++
				}
			} else if tmpSum > needNum {
				r--
				for r >= 0 && nums[r] == nums[r+1] {
					r--
				}
			} else {
				tmpList := []int{nums[i], nums[l], nums[r]}
				ret = append(ret, tmpList)
				l++
				for l < n && nums[l] == nums[l-1] {
					l++
				}
				r--
				for r >= 0 && nums[r] == nums[r+1] {
					r--
				}
			}
		}
		for i+1 < n && nums[i+1] == nums[i] {
			i++
		}
	}

	return ret
}