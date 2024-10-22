/*
No910.smallest-range-ii
*/

// func absSub(a, b int) int {
//     if b > a {
//         return b - a
//     }
//     return a - b
// }

// func smallestRangeII(nums []int, k int) int {
//     var sum, maxVal, minVal, avg, tmp int = 0, -1, 10001, 0, 0

//     // avg
//     for _, num := range nums {
//         sum += num
//     }
//     avg = sum / len(nums)

//     // iterator
//     for _, num := range nums {
//         if num < avg {
//             if absSub(num + k, avg) < absSub(num, avg) {
//                 tmp = num + k
//             }
//         } else if num > avg {
//             if absSub(num - k, avg) < absSub(num, avg) {
//                 tmp = num - k
//             }
//         } else {
//             if absSub(maxVal, num - k) < absSub(num + k, minVal) {
//                 tmp = num - k
//             } else {
//                 tmp = num + k
//             }
//         }
//         maxVal = max(maxVal, tmp)
//         minVal = min(minVal, tmp)
//     }

//     return maxVal - minVal
// }

func smallestRangeII(nums []int, k int) int {
	n := len(nums)
	sort.Ints(nums)

	mi, ma := nums[0], nums[n-1]
	ans := ma - mi

	// iterator i, nums[0, i] + k, nums[i+1, n-1] -k
	for i := 0; i < n-1; i++ {
		ans = min(ans, max(ma-k, nums[i]+k)-min(mi+k, nums[i+1]-k))
	}
	return ans
}