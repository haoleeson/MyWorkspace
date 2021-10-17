#include <iostream>
#include <vector>
using namespace std;

/**
 * No300. 最长上升子序列（动态规划）
 * 给定一个无序的整数数组，找到其中最长上升子序列的长度。

示例:

输入: [10,9,2,5,3,7,101,18]
输出: 4 
解释: 最长的上升子序列是[2,3,7,101]，它的长度是 4。
说明:

可能会有多种最长上升子序列的组合，你只需要输出对应的长度即可。
你算法的时间复杂度应该为O(n2) 。
进阶: 你能将算法的时间复杂度降低到O(n log n) 吗?

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-increasing-subsequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 解题思路：动态规划O(n^2)
 */
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int i, k, size = nums.size();
        if (size < 2) {
            return size;
        }

        int maxSubLen = 1;

        // dp[i] : [0, i]中，若选i为上升子序列的尾部，最大序列长度值
        vector<int> dp(size, 1);

        for (i = 1; i < size; ++i) {
            for (k = 0; k < i; ++k) {
                if (nums[k] < nums[i] && dp[k] + 1 > dp[i]) {
                    dp[i] = 1 + dp[k];
                    if (dp[i] > maxSubLen) {
                        maxSubLen = dp[i];
                    }
                }
            }
        }

        return maxSubLen;
    }
};

int main() {
    Solution solution;
    int arr[] = {10,9,2,5,3,7,101,18};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    cout << solution.lengthOfLIS(nums) << endl;
    return 0;
}
