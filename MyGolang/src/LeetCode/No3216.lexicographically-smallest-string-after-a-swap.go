/*
No3216.lexicographically-smallest-string-after-a-swap
*/

func isSmaller(a, b []byte, n int) bool {
	var i int = 0
	for i = 0; i < n; i++ {
		if a[i] > b[i] {
			return false
		} else if a[i] < b[i] {
			return true
		}
	}
	return false
}

func swapI(a []byte, i int) {
    tmp := a[i-1]
    a[i-1] = a[i]
    a[i] = tmp
}

func deepCopy(a, b []byte, n int) {
    for i := 0; i< n; i++ {
        a[i] = b[i]
    }
}

func getSmallestString(s string) string {
    n := len(s)
	b := []byte(s)
	ans := []byte(s)

    // iterator index
	for i := 1; i < n; i++ {
        // if b[i] is not smaller or not equal feature, skip
		if b[i] >= b[i-1] || int(b[i-1]-b[i])%2 == 1 {
			continue
		}
		
        swapI(b, i)
		if isSmaller(b, ans, n) {
			deepCopy(ans, b, n)
		}
        swapI(b, i)
	}

	return string(ans)
}