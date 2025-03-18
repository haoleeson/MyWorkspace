// No2614.prime-in-diagonal
func diagonalPrime(nums [][]int) int {
	n := len(nums)
	res := 0

	for i := 0; i < n; i++ {
		if nums[i][i] > res && isPrime(nums[i][i]) {
			res = max(res, nums[i][i])
		}
		if nums[i][n-1-i] > res && isPrime(nums[i][n-1-i]) {
			res = max(res, nums[i][n-1-i])
		}
	}
	return res
}

func isPrime(num int) bool {
	if num == 1 {
		return false
	}

	fa := 2
	for ; fa*fa <= num; fa++ {
		if num%fa == 0 {
			return false
		}
	}
	return true
}