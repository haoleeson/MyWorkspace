/*
No50.powx-n
*/

func myPow(x float64, n int) float64 {
	if n >= 0 {
		return bioMul(x, n)
	}
	return 1.0 / bioMul(x, -n)
}

func bioMul(x float64, n int) float64 {
	if n == 0 {
		return 1
	}
	y := bioMul(x, n/2)
	if n%2 == 0 {
		return y * y
	}
	return y * y * x
}
