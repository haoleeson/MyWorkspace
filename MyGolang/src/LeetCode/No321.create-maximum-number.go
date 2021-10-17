/**
No321. 拼接最大数（单调栈）
给定长度分别为m和n的两个数组，其元素由0-9构成，表示两个自然数各位上的数字。现在从这两个数组中选出 k (k <= m + n)个数字拼接成一个新的数，要求从同一个数组中取出的数字保持其在原数组中的相对顺序。
求满足该条件的最大数。结果返回一个表示该最大数的长度为k的数组。
说明: 请尽可能地优化你算法的时间和空间复杂度。

示例1:
输入:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
输出:
[9, 8, 6, 5, 3]

示例 2:
输入:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
输出:
[6, 7, 6, 0, 4]

示例 3:
输入:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
输出:
[9, 8, 9]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/create-maximum-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
package LeetCode

/**
力扣官解：单调栈
单调栈使用数组实现，数组最左侧为栈底。使用数组实现，可以直接从左到右遍历数组得到最大子序列。
 */

/**
功能函数1：求指定长度的最大子数组（单调栈）
@param arr 输入数组
@param k 子数组长度 0 <= k <= len(arr), 外部维护 k 合法性
 */
func maxSubSequence(arr []int, k int) []int {
    lenArr := len(arr)
    lenSubArr := 0
    subArr := make([]int, k)
    for i, v := range arr {
        // 若当前栈非空，且栈已有元素 + 剩余元素 > k，即有比较淘汰空间，则比较栈顶 与 当前数，留大
        for lenSubArr > 0 && lenSubArr + lenArr - i - 1 >= k && v > subArr[lenSubArr - 1] {
            lenSubArr-- // 长度自减，其值将被后续数字覆盖
        }
        if lenSubArr < k {
            subArr[lenSubArr] = v
            lenSubArr++
        }
    }
    return subArr
}

/**
功能函数2：自定义比较两数组大小
true -- a > b; false -- a <= b
*/
func isAGreatThanB(a, b []int) bool {
    lenA := len(a)
    lenB := len(b)
    for i := 0; i < lenA && i < lenB; i++ {
        if a[i] != b[i] {
            return a[i] > b[i]
        }
    }
    return lenA > lenB
}

/**
功能函数3：合并两数组
 */
func merge(a, b []int) []int {
    lenA := len(a)
    lenB := len(b)
    combArr := make([]int, lenA + lenB)
    for i := range combArr {
        if isAGreatThanB(a, b) {
            combArr[i], a = a[0], a[1:]
        } else {
            combArr[i], b = b[0], b[1:]
        }
    }
    return combArr
}

func maxNumber(nums1 []int, nums2 []int, k int) (res []int) {
    len1 := len(nums1)
    len2 := len(nums2)
    start := 0
    if k > len2 {
        start = k - len2
    }
    for i := start; i <= k && i <= len1; i++ {
        subArr1 := maxSubSequence(nums1, i)
        subArr2 := maxSubSequence(nums2, k - i)
        combArr := merge(subArr1, subArr2)
        if isAGreatThanB(combArr, res) {
            res = combArr
        }
    }
    return
}
