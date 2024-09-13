/*
No2576.find-the-maximum-number-of-marked-indices
*/

func maxNumOfMarkedIndices(nums []int) int {
    n := len(nums)
    sort.Ints(nums)
    ans := 0
    m := n/2

    // double pointer
    for i,j:=0,m; i<m && j < n; i++ {
        for j < n && 2 * nums[i] > nums[j] {
            j++
        }
        if j < n {
            ans += 2
            j++
        } 
    }
    return ans
}