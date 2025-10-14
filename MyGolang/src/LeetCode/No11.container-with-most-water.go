/*
No11.container-with-most-water
*/

// double point
// O(n)
func maxArea(height []int) int {
	var l, r, tmpW, ret int = 0, len(height) - 1, 0, 0

	for l < r {
		tmpW = min(height[l], height[r]) * (r - l)
		if tmpW > ret {
			ret = tmpW
		}

		if height[l] < height[r] {
			l++
		} else {
			r--
		}
	}
	return ret
}

// single stack
// O(n^2)
func maxArea0(height []int) int {
	var ret, tmpW int = 0, 0

	sinIdxQue := make([]int, 1)
	sinIdxQue[0] = 0

	for i := 1; i < len(height); i++ {
		// calc the most water when cur i idx as right edge
		for j := len(sinIdxQue) - 1; j >= 0; j-- {
			tmpW = min(height[i], height[sinIdxQue[j]]) * (i - sinIdxQue[j])
			if tmpW > ret {
				ret = tmpW
			}
		}
		// push heighter cur idx i
		if height[i] > sinIdxQue[len(sinIdxQue)-1] {
			sinIdxQue = append(sinIdxQue, i)
		}
	}

	return ret
}

func min(x, y int) int {
	if y < x {
		return y
	}
	return x
}