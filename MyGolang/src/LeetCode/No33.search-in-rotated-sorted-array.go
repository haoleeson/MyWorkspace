/*
No33.search-in-rotated-sorted-array
*/
func search(nums []int, target int) int {
	n := len(nums)
	l, r := 0, n-1
	numK := nums[0]

	for l <= r {
		mid := (l + r) / 2

		// find
		if nums[mid] == target {
			return mid
		}

		if nums[mid] >= numK {
			// left
			// if nums[mid] > target {
			// 	if numK <= target {
			// 		r = mid - 1
			// 	} else {
			// 		l = mid + 1
			// 	}
			// } else if nums[mid] < target {
			// 	l = mid + 1
			// }
			// condition merge
			if nums[mid] > target && numK <= target {
				// left, down
				r = mid - 1
			} else {
				l = mid + 1
			}
		} else {
			// right
			// if nums[mid] > target {
			// 	r = mid - 1
			// } else if nums[mid] < target {
			// 	if numK > target {
			// 		l = mid + 1
			// 	} else {
			// 		r = mid - 1
			// 	}
			// }
			// condition merge
			if nums[mid] < target && numK > target {
				// right, up
				l = mid + 1
			} else {
				r = mid - 1
			}
		}
	}
	return -1

}