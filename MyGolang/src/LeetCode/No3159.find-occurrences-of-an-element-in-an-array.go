/*
No3159.find-occurrences-of-an-element-in-an-array
*/

func occurrencesOfElement(nums []int, queries []int, x int) []int {
	lenN := len(nums)
	lenQ := len(queries)
	res := make([]int, lenQ)

	indexX := make([]int, 0)
	// record x index
	for i := 0; i < lenN; i++ {
		if nums[i] == x {
			indexX = append(indexX, i)
		}
	}

	sizeI := len(indexX)
	for i := 0; i < lenQ; i++ {
		if queries[i] > sizeI {
			res[i] = -1
		} else {
			res[i] = indexX[queries[i]-1]
		}
	}
	return res
}