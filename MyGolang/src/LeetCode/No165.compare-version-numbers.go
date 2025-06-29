/*
No165.compare-version-numbers
*/

func compareVersion(version1 string, version2 string) int {
	n1 := len(version1)
	n2 := len(version2)

	idx1, idx2 := 0, 0
	num1, num2 := 0, 0

	for idx1 < n1 && idx2 < n2 {
		num1 = 0
		for ; idx1 < n1 && version1[idx1] != '.'; idx1++ {
			num1 = num1*10 + int(version1[idx1]-'0')
		}
		idx1++

		num2 = 0
		for ; idx2 < n2 && version2[idx2] != '.'; idx2++ {
			num2 = num2*10 + int(version2[idx2]-'0')
		}
		idx2++

		// compare
		if num1 < num2 {
			return -1
		}
		if num1 > num2 {
			return 1
		}
	}

	// check left all 0
	for ; idx2 < n2; idx2++ {
		if version2[idx2] != '.' && version2[idx2] != '0' {
			return -1
		}
	}

	// check left all 0
	for ; idx1 < n1; idx1++ {
		if version1[idx1] != '.' && version1[idx1] != '0' {
			return 1
		}
	}

	return 0
}