#include <iostream>
#include <vector>
using namespace std;

/**
 * No740. 删除与获得点数（动态规划）
 * 给定一个整数数组nums，你可以对它进行一些操作。
 * 每次操作中，选择任意一个nums[i]，删除它并获得nums[i]的点数。之后，你必须删除每个等于nums[i] - 1或nums[i] + 1的元素。
 * 开始你拥有 0 个点数。返回你能通过这些操作获得的最大点数。

示例 1:
输入: nums = [3, 4, 2]
输出: 6
解释: 
删除 4 来获得 4 个点数，因此 3 也被删除。
之后，删除 2 来获得 2 个点数。总共获得 6 个点数。

示例2:
输入: nums = [2, 2, 3, 3, 3, 4]
输出: 9
解释: 
删除 3 来获得 3 个点数，接着要删除两个 2 和 4 。
之后，再次删除 3 获得 3 个点数，再次删除 3 获得 3 个点数。
总共获得 9 个点数。

注意:
nums的长度最大为20000。
每个整数nums[i]的大小都在[1, 10000]范围内。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/delete-and-earn
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


/**
 * 参考力扣高赞路人解题思路：
 * 统计每个数字个数O(n)，每个数字有两种选择：选择or被删除
 * 1. 如果你不删除当前数字，那么你得到就是前一个数字的位置的最优结果。
 * 2. 如果删除当前数字，那么你就会得到i - 2位置的那个最优结果加上当前位置的数字乘以个数。
 *
 * eg.
 * nums     = [2, 2, 3, 3, 3, 4]
 * count[]  = [0, 0, 2, 3, 1]
 *                 删除当前数字       选择当前数字(前一个数字会被保留)
 * dp[i] = Math.max(dp[i - 1], dp[i - 2] + i * count[i]);
 */
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        int size = nums.size(), maxNum = 0;
        if (size < 2) {
            return size == 1 ? nums[0] : 0;
        }

        int count[10001] = {0};
        int dp[10001] = {0};
        // 统计每个数字个数（并记录最大值）
        for (int i = 0; i < size; ++i) {
            ++count[nums[i]];
            if (nums[i] > maxNum) {
                maxNum = nums[i];
            }
        }

        // dp[i] ： 从[0, i]能获取的最大积分
        dp[0] = 0;
        dp[1] = count[1];

        for (int i = 2; i <= maxNum; ++i) {
            dp[i] = max(dp[i - 1], dp[i - 2] + i * count[i]);
        }
        return dp[maxNum];
    }
};

int main() {
    Solution solution;
    int arr[] = {2, 2, 3, 3, 3, 4};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));

    cout << solution.deleteAndEarn(nums) << endl;

    return 0;
}
