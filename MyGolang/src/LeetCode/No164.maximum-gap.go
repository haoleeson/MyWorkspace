/**
No164. 最大间距 (基数排序)
给定一个无序的数组，找出数组在排序之后，相邻元素之间最大的差值。
如果数组元素个数小于2，则返回0。

示例1:
输入: [3,6,9,1]
输出: 3
解释: 排序后的数组是 [1,3,6,9], 其中相邻元素 (3,6) 和 (6,9) 之间都存在最大差值 3。

示例2:
输入: [10]
输出: 0
解释: 数组元素个数小于 2，因此返回 0。
说明:

你可以假设数组中所有元素都是非负整数，且数值在 32 位有符号整数范围内。
请尝试在线性时间复杂度和空间复杂度的条件下解决此问题。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/maximum-gap
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

package LeetCode

/** 思路：先排序，后统计
时间复杂度：快排O(n * log(n))、基数排序O(N)
空间复杂度：O(1)
*/
func maximumGap(nums []int) int {
    size := len(nums)
    if size <= 2 {
        if size == 2 {
            if nums[0] < nums[1] {
                return nums[1] - nums[0]
            } else {
                return nums[0] - nums[1]
            }
        }
        return 0
    }

    // 基数排序
    cardinalSort(&nums, len(nums))

    // 统计最大间距
    maxDiff := nums[1] - nums[0]
    for i := 2; i < size; i++ {
        if nums[i] - nums[i - 1] > maxDiff {
            maxDiff = nums[i] - nums[i - 1]
        }
    }
    return maxDiff
}

/**
基数排序（仅适用于正整数排序）
时间复杂度：O(N)
空间复杂度：O(N)
@param nums 待排序数组
@param size 数组内元素个数
*/
func cardinalSort(nums *[]int, size int) {
    // 创建与数组等容量的缓冲区，用于缓存每轮基数排序的中间结果
    buf := make([]int, size)
    // 找到最大值（确定基数排序多少轮，即最大数字有多少位数）
    maxVal := (*nums)[0]
    for _, num := range *nums {
        if num > maxVal {
            maxVal = num
        }
    }
    // 从个位依次到最高位基数排序（最低位优先）
    for exp := 1; exp <= maxVal; exp *= 10 {
        // 桶0~9，分别统计第 exp 位对应为 0 ~ 9 的数字的个数（后转换为起始下标）
        buckets := [10]int{} // 初始值为0
        // 1. 统计第 exp 位对应为 0 ~ 9 的数字的个数
        for _, num := range *nums {
            buckets[num / exp % 10]++
        }
        // 2. 根据每个桶的个数统计，折算成桶0~9所对应的起始偏移下标
        buckets[9] = size - buckets[9]
        for i := 8; i > 0; i-- {
            buckets[i] = buckets[i + 1] - buckets[i]
        }
        buckets[0] = 0

        // 3. 遍历数字，按第 exp 位的位置插入对应0~9末尾下标位置（该末尾后-1）
        var digit int // 第 exp 位的数字
        for _, num := range *nums {
            digit = num / exp % 10
            buf[buckets[digit]] = num
            buckets[digit]++
        }
        // 将第 exp 位基数排序的排序结果保存于nums数组
        copy(*nums, buf)
    }
}
