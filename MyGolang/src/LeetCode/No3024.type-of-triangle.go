/*
No3024.type-of-triangle
*/
func triangleType(nums []int) string {
	// sort
	if nums[0] > nums[1] {
		nums[0], nums[1] = nums[1], nums[0]
	}
	if nums[0] > nums[2] {
		nums[0], nums[2] = nums[2], nums[0]
	}
	if nums[1] > nums[2] {
		nums[1], nums[2] = nums[2], nums[1]
	}

	// valide
	if nums[0]+nums[1] <= nums[2] {
		return "none"
	}

	// count same
	sameCnt := 0
	if nums[0] == nums[1] {
		sameCnt++
	}
	if nums[1] == nums[2] {
		sameCnt++
	}
	switch sameCnt {
	case 1:
		return "isosceles"
	case 2:
		return "equilateral"
	default:
		return "scalene"
	}
	return ""
}