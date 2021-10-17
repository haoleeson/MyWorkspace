/**
 * No416. 分割等和子集 （动态规划、01背包问题）
 * 给定一个只包含正整数的非空数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

注意:
每个数组中的元素不会超过 100
数组的大小不会超过 200

示例 1:
输入: [1, 5, 11, 5]
输出: true
解释: 数组可以分割成 [1, 5, 5] 和 [11].


示例2:
输入: [1, 2, 3, 5]
输出: false
解释: 数组不能分割成两个元素和相等的子集.

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/partition-equal-subset-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;
/**
 * 力扣官解：
 * 简化问题为：是否能从数组中找到子集，其和为数组和的一半(target)，从而转化为0/1背包问题
 */
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) {
            return false;
        }
        int sum = 0, maxNum = 0, target;
        for (int num : nums) {
            sum += num;
            if (num > maxNum) {
                maxNum = num;
            }
        }
        // 若数组和为奇数，不可能被划分为两部分
        if (sum & 1) {
            return false;
        }
        target = sum / 2;
        // 若最大元素大于数组和的一半，说明其他所有元素之和小于target，不能被等分
        if (maxNum > target) {
            return false;
        }
        // dp[j] : 是否存在一种选取方案使得被选取的正整数的和等于 j，0/1背包问题
        // 状态转移方程：若 j > num ，且选取当前num作为元素，则 dp[j] = dp[j - num];
        //              若 j > num ，且不选取当前num，则 dp[j]不变
        //              若 j < num , 不能选取当前num，则 dp[j]不变
        //      归纳有: dp[j] = dp[j - num] | dp[j]
        vector<bool> dp(target + 1, 0);
        dp[0] = true;
        for (int i = 0; i < n; i++) {
            int num = nums[i];
            for (int j = target; j >= num; --j) {
                dp[j] = dp[j - num] | dp[j];// 选取 or 不选取，有一个成功即可
            }
        }
        return dp[target];
    }
};

int main() {
    Solution solution;
    int arr[] = {1, 5, 11, 5};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    cout << solution.canPartition(nums) << endl;
    return 0;
}
