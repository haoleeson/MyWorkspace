/*
No75.sort-colors
*/
func sortColors(nums []int) {
	l, r := 0, len(nums)-1
	var tmp int

	for i := 0; i <= r; {
		switch nums[i] {
		case 0:
			// skip swap
			if i == l {
				i++
				l++
				continue
			}
			// swap with nums[i], nums[l]
			tmp = nums[l]
			nums[l] = nums[i]
			nums[i] = tmp
			l++
		case 2:
			// swap with nums[i], nums[r]
			tmp = nums[r]
			nums[r] = nums[i]
			nums[i] = tmp
			r--
		case 1:
			// skip swap
			i++
		}
	}
}