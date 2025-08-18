/*
No470.implement-rand10-using-rand7
*/

func rand10() int {
	for {
		row := rand7()
		col := rand7()
		idx := (row-1)*7 + col
		if idx <= 40 {
			return (idx-1)%10 + 1
		}
	}
}