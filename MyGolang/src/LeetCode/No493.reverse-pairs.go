/**
No493. 翻转对 (归并)
给定一个数组nums，如果i < j且nums[i] > 2*nums[j]我们就将(i, j)称作一个重要翻转对。
你需要返回给定数组中的重要翻转对的数量。

示例 1:
输入: [1,3,2,3,1]
输出: 2

示例 2:
输入: [2,4,3,5,1]
输出: 3
注意:

给定数组的长度不会超过50000。
输入数组中的所有数字都在32位整数的表示范围内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-pairs
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
package LeetCode


func reversePairs(nums []int) int {
    n := len(nums)
    if n <= 1 {
        return 0
    }

    leftArr := append([]int(nil), nums[:n/2]...)
    rightArr := append([]int(nil), nums[n/2:]...)
    cnt := reversePairs(leftArr) + reversePairs(rightArr) // 递归完毕后，leftArr 和 rightArr 均为有序

    // 统计重要翻转对 (i, j) 的数量
    // 由于 leftArr 和 rightArr 均为有序，可以用两个指针同时遍历
    j := 0
    for _, v := range leftArr {
        for j < len(rightArr) && v > 2 * rightArr[j] {
            j++
        }
        cnt += j
    }

    // leftArr 和 rightArr 归并填入 nums
    p1, p2 := 0, 0
    for i := range nums {
        if p1 < len(leftArr) && (p2 == len(rightArr) || leftArr[p1] <= rightArr[p2]) {
            nums[i] = leftArr[p1]
            p1++
        } else {
            nums[i] = rightArr[p2]
            p2++
        }
    }
    return cnt
}

