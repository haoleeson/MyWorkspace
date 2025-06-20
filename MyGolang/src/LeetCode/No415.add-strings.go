/*
No415.add-strings
*/
func addStrings(num1 string, num2 string) string {
	n1 := len(num1)
	n2 := len(num2)
	b1 := []byte(num1)
	b2 := []byte(num2)

	ret := make([]byte, max(n1, n2)+1) // more 1

	idx1, idx2, idxSum := n1-1, n2-1, max(n1, n2)
	var tmpSum, jin byte = 0, 0
	for idx1 >= 0 && idx2 >= 0 {
		tmpSum = b1[idx1] - byte('0') + b2[idx2] + jin
		if tmpSum > byte('9') {
			tmpSum -= byte(10)
			jin = 1
		} else {
			jin = 0
		}
		ret[idxSum] = tmpSum
		idxSum--
		idx1--
		idx2--
	}

	for idx1 >= 0 {
		tmpSum = b1[idx1] + jin
		if tmpSum > byte('9') {
			tmpSum -= byte(10)
			jin = byte(1)
		} else {
			jin = byte(0)
		}
		ret[idxSum] = tmpSum
		idxSum--
		idx1--
	}

	for idx2 >= 0 {
		tmpSum = b2[idx2] + jin
		if tmpSum > byte('9') {
			tmpSum -= byte(10)
			jin = byte(1)
		} else {
			jin = byte(0)
		}
		ret[idxSum] = tmpSum
		idxSum--
		idx2--
	}

	if jin == byte(1) {
		ret[idxSum] = byte('1')
	} else {
		ret = ret[1:] // no jin, del more 1
	}

	return string(ret)
}