/*
No3162.find-the-number-of-good-pairs-i
*/

func numberOfPairs(nums1 []int, nums2 []int, k int) int {
    n := len(nums1)
    m := len(nums2)
    ans := 0
    
    // sample
    sort.Ints(nums2)
    for i :=0; i < n; i++ {
        if nums1[i] % k != 0 {
            continue
        }
        for j :=0; j < m; j++ {
            if nums2[j] > nums1[i] {
                break
            }
            if nums1[i] % (nums2[j] * k) == 0 {
                ans++
            }
        }
    }


    return ans
}