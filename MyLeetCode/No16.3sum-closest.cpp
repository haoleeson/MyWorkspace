#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * No16. 最接近的三数之和（双指针）
 * 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，
 * 使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。


示例：
输入：nums = [-1,2,1,-4], target = 1
输出：2
解释：与 target 最接近的和是 2 (-1 + 2 + 1 = 2) 。
 

提示：

3 <= nums.length <= 10^3
-10^3 <= nums[i] <= 10^3
-10^4 <= target <= 10^4

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum-closest
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
    int m_target = 0, m_minDiff = INT32_MAX, m_closestSum = 0;
public:
    // 尝试刷新最接近的值
    void freshMinDiff(int tmpSum) {
        int diff = abs(tmpSum - m_target);
        if (diff < m_minDiff) {
            m_minDiff = diff;
            m_closestSum = tmpSum;
        }
    }

    int threeSumClosest(vector<int>& nums, int target) {
        int size = nums.size();
        int leftIndex = 0, midIndex = 0, rightIndex = 0, tmp = 0;
        m_target = target;

        // 排序O(nlogn)
        sort(nums.begin(), nums.end());

        // 确定组合的最左端的数
        for (leftIndex = 0; leftIndex < size - 2 && m_minDiff > 0; ++leftIndex) {
            // 加速，最大组合仍小于 target
            tmp = nums[leftIndex] + nums[size - 1] + nums[size - 2];
            if (tmp <= target) {
                freshMinDiff(tmp);// 尝试刷新最接近的值
                continue;
            }

            // 加速，最小组合（左端的三个数）的和大于 target
            tmp = nums[leftIndex] + nums[leftIndex + 1] + nums[leftIndex + 2];
            if (tmp >= target) {
                freshMinDiff(tmp);// 尝试刷新最接近的值
                break;
            }

            // 正常遍历
            midIndex = leftIndex + 1;
            rightIndex = size - 1;
            while (midIndex < rightIndex) {
                tmp = nums[leftIndex] + nums[midIndex] + nums[rightIndex];
                if (tmp == target) {
                    return tmp;
                }
                // 若和小于target，增加midIndex
                if (tmp < target) {
                    ++midIndex;
                }
                // 若和大于target，减小rightIndex
                else {
                    --rightIndex;
                }
                freshMinDiff(tmp);// 尝试刷新最接近的值
            }
        }
        return m_closestSum;
    }
};

int main() {
    Solution solution;
    int target = 1;
    int arr[] = {-1,2,1,-4};
    vector<int> nums(arr, arr + 4);
    cout << solution.threeSumClosest(nums, target) << endl;
    return 0;
}
