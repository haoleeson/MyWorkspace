/*
No179.largest-number
*/

func largestNumber(nums []int) string {
	// compare "x"+"y"  with "y"+"x"
	var cmp func(int, int) bool
	cmp = func(i, j int) bool {
		x, y := nums[i], nums[j]
		sx, sy := 10, 10
		for sx <= x {
			sx *= 10
		}
		for sy <= y {
			sy *= 10
		}
		// "x" + "y"  >  "y"+"x"
		return (x*sy + y) > (y*sx + x)
	}

	sort.Slice(nums, cmp)

	// special, all nums equal 0, squash them to "0"
	if nums[0] == 0 {
		return "0"
	}

	// to string
	ret := make([]byte, 0)
	for _, num := range nums {
		ret = append(ret, strconv.Itoa(num)...)
	}
	return string(ret)
}