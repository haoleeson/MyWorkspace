/*
No43.multiply-strings
*/

func multiply(num1 string, num2 string) string {
	if num1 == "0" || num2 == "0" {
		return "0"
	}

	var revertNumStrToNumArr func(string) []int
	revertNumStrToNumArr = func(num string) []int {
		lenN := len(num)
		arr := make([]int, lenN)
		for i, j := 0, lenN-1; i < lenN; {
			arr[j] = int(num[i] - '0')
			i++
			j--
		}
		return arr
	}

	var revertNumArrToNumStr func([]int) string
	revertNumArrToNumStr = func(arr []int) string {
		arrIdx := len(arr) - 1
		ansByteBuff := make([]byte, arrIdx+1)
		for i := 0; arrIdx >= 0; {
			ansByteBuff[i] = '0' + byte(arr[arrIdx])
			i++
			arrIdx--
		}
		return string(ansByteBuff)
	}

	// revert num1, num2
	lenNum1, lenNum2 := len(num1), len(num2)
	var n1, n2 []int
	if lenNum2 > lenNum1 {
		n1 = revertNumStrToNumArr(num2)
		n2 = revertNumStrToNumArr(num1)
		lenNum1, lenNum2 = lenNum2, lenNum1
	} else {
		n1 = revertNumStrToNumArr(num1)
		n2 = revertNumStrToNumArr(num2)
	}

	var jin, addJin, tmpVal int = 0, 0, 0
	ans := make([]int, lenNum1+lenNum2)
	tmpStr := make([]int, lenNum1+1)
	for i, ch2 := range n2 {
		// n1 * ch2
		for j, ch1 := range n1 {
			tmpVal = ch2*ch1 + jin
			tmpStr[j] = tmpVal % 10
			jin = tmpVal / 10
		}
		if jin != 0 {
			tmpStr[lenNum1] = jin
			jin = 0
		} else {
			tmpStr[lenNum1] = 0
		}

		// add tmpStr and ans
		for j := 0; j < lenNum1+1; j++ {
			tmpVal = tmpStr[j] + ans[i+j] + addJin
			ans[i+j] = tmpVal % 10
			if tmpVal > 9 {
				addJin = 1
			} else {
				addJin = 0
			}
		}
		if addJin > 0 {
			ans[i+lenNum1+1] = 1
			addJin = 0
		}
	}

	// remove more zero
	ansIdx := lenNum1 + lenNum2 - 1
	for ; ansIdx >= 0; ansIdx-- {
		if ans[ansIdx] != 0 {
			break
		}
	}
	ans = ans[:ansIdx+1]

	return revertNumArrToNumStr(ans)
}