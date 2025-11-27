/*
No15.3sum
*/
// 2025-11-27
func threeSum2(nums []int) [][]int {
	ans := make([][]int, 0)
	n := len(nums)
	sort.Ints(nums)

	var i, j, tmpTarget, tmpTwoSum int
	for k := n - 1; k > 1; k-- {
		tmpTarget = -nums[k]
		i, j = 0, k-1
		for i < j {
			tmpTwoSum = nums[i] + nums[j]
			if tmpTwoSum > tmpTarget {
				// left move j and skip same val
				for i < j && nums[j-1] == nums[j] {
					j--
				}
				j--
			} else if tmpTwoSum < tmpTarget {
				// right move i and skip same val
				for i < j && nums[i+1] == nums[i] {
					i++
				}
				i++
			} else {
				ans = append(ans, []int{nums[i], nums[j], nums[k]})
				// left move j and skip same val
				for i < j && nums[j-1] == nums[j] {
					j--
				}
				j--
				// right move i and skip same val
				for i < j && nums[i+1] == nums[i] {
					i++
				}
				i++
			}
		}

		// skip dumplicate k
		for k > 1 && nums[k-1] == nums[k] {
			k--
		}
	}

	return ans
}

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