/*
No540.single-element-in-a-sorted-array
*/

// func singleNonDuplicate(nums []int) int {
//     n := len(nums)
//     if n == 1 {
//         return nums[0]
//     }

//     // dichotomy method
//     l,r, mid := 0, n-1, 0
//     for (r - l) > 1 {
//         mid = (l + r) / 2

//         if nums[mid] == nums[mid-1] {
//             if (mid-l)%2==0 {
//                 r = mid
//             } else {
//                 l = mid + 1
//             }
//         } else if nums[mid] == nums[mid+1] {
//             if (r - mid)%2==0 {
//                 l = mid + 1
//             } else {
//                 r = mid
//             }
//         } else {
//             return nums[mid]
//         }
//     }

//     mid = (l + r) / 2
//     if mid == 0 || mid == n-1 {
//         return nums[mid]
//     }
//     if nums[mid] == nums[mid - 1] {
//         return nums[mid + 1]
//     }

//     return nums[mid - 1]
// }

func singleNonDuplicate(nums []int) int {
    l, r := 0, len(nums)-1
    for l < r {
        mid := (r+l)/2
        if nums[mid] == nums[mid^1] {
            l = mid + 1
        } else {
            r = mid
        }
    }
    return nums[l]
}