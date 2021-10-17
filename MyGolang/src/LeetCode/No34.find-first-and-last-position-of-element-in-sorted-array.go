/**
No34. 在排序数组中查找元素的第一个和最后一个位置
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。

进阶：
你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？

示例 1：
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]

示例 2：
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]

示例 3：
输入：nums = [], target = 0
输出：[-1,-1]

提示：
0 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
nums 是一个非递减数组
-10^9 <= target <= 10^9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
package LeetCode

func searchRange(nums []int, target int) []int {
    ans := []int{-1, -1}
    size := len(nums)
    if size < 2 {
        if size == 1 && nums[0] == target {
            return []int{0, 0}
        }
    }

    // 二分法（找到最大下标的target）
    left, right, mid := 0, size - 1, 0
    for left < right {
        mid = (left + right) / 2
        if nums[mid] > target {
            right = mid -1
        } else if nums[mid] <= target {
            // 忽略左侧target 值
            left = mid + 1
        }
    }
    if left < size && nums[left] == target {
        ans[1] = left
    } else if left > 0 && left < size + 1 && nums[left - 1] == target {
        ans[1] = left - 1
    }

    // 二分法（找到最小下标的target）
    left = 0
    right = size - 1
    for left < right {
        mid = (left + right) / 2
        if nums[mid] >= target {
            // 忽略右侧target 值
            right = mid - 1
        } else if nums[mid] < target {
            left = mid + 1
        }
    }
    if right > -1 && nums[right] == target {
        ans[0] = right
    } else if right > -2 && right < size - 1 && nums[right + 1] == target {
        ans[0] = right + 1
    }
    return ans
}
