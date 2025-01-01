/*
No3280.convert-date-to-binary
*/

func convertDateToBinary(date string) string {
	y, _ := strconv.Atoi(date[0:4])
	m, _ := strconv.Atoi(date[5:7])
	d, _ := strconv.Atoi(date[8:])

	return fmt.Sprintf("%b-%b-%b", y, m, d)
}