/*
No75.sort-colors
*/
func sortColors(nums []int) {
	n := len(nums)
	l, r := 0, n-1

	for i := l; i <= r; {
		switch nums[i] {
		case 0:
			if l == i {
				l++
				i++
			} else {
				nums[i] = nums[l]
				nums[l] = 0

				l++
				i++
			}
		case 1:
			i++
		case 2:
			nums[i] = nums[r]
			nums[r] = 2
			r--
		}
	}
}