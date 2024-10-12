/*
No3158.find-the-xor-of-numbers-which-appear-twice
*/
func duplicateNumbersXOR(nums []int) int {
    n := len(nums)
    countM := make(map[int]int, n)
    ans := 0

    for _, num := range nums {
        if _, existed := countM[num]; existed {
            ans ^= num
        } else {
            countM[num] = 1
        }
    }

    return ans
}