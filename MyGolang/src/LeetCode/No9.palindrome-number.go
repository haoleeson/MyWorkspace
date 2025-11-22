/*
No9.palindrome-number
*/

func isPalindrome(x int) bool {
	if x < 0 {
		return false
	}

	nums := make([]int, 10)
	numsLen := 0
	var tmp int
	for x > 0 {
		tmp = x % 10
		nums[numsLen] = tmp
		numsLen++
		x /= 10
	}

	for i, j := 0, numsLen-1; i < j; {
		if nums[i] != nums[j] {
			return false
		}
		i++
		j--
	}

	return true
}
