/*
No6.zigzag-conversion
*/

func strIdxToRowIdx(strIdx, numRows int) int {
	if numRows == 2 {
		return strIdx % 2
	}
	looplRow := numRows*2 - 2
	strIdx %= looplRow
	if strIdx < numRows {
		return strIdx
	}
	// else: rowIndex = (numRows - 1) - (strIdx - (numRows - 1)) = numRows * 2 - strIdx - 2
	return numRows*2 - strIdx - 2
}

func convert(s string, numRows int) string {
	if numRows == 1 {
		return s
	}

	n := len(s)
	b := []byte(s)

	rows := make([][]byte, numRows)

	for i := 0; i < n; i++ {
		// string index convert to row index
		rowIndex := strIdxToRowIdx(i, numRows)
		rows[rowIndex] = append(rows[rowIndex], b[i])
	}

	// append string
	ret := make([]byte, 0)
	for _, r := range rows {
		ret = append(ret, r...)
	}
	return string(ret)
}