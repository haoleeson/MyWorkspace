#include <iostream>
#include "myTools.h"
using namespace std;

/**
 * No55. 跳跃游戏
 * 给定一个非负整数数组，你最初位于数组的第一个位置。数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 判断你是否能够到达最后一个位置。

示例1:
输入: [2,3,1,1,4]
输出: true
解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。

示例2:
输入: [3,2,1,0,4]
输出: false
解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jump-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int targetIndex = nums.size() - 1;
        // dp[i] : [0,i]是否均可到达
        // 状态转移公式 dp[i] = (dp[i-k] == true && nums[i-k] >= k) ? true : false;
        // 进一步转换为最大可访问到的下标 maxAccessIndex
        int iterator = 1, maxAccessIndex = nums[0];

        while (iterator <= maxAccessIndex && maxAccessIndex < targetIndex) {
            if (nums[iterator] + iterator > maxAccessIndex) {
                maxAccessIndex = nums[iterator] + iterator;
            }
            ++iterator;
        }
        return maxAccessIndex >= targetIndex;
    }
};

/**
 * 思路1：dfs + 贪心（最大跳跃距离），超时
 */
class Solution1 {
public:
    bool ans = false;
    int size;
    void dfs(vector<int>& nums, int index) {
        if (index == size - 1) {
            ans = true;
        }

        int maxIndex = min(size - 1, index + nums[index]);
        // 加速
        if (maxIndex == size - 1) {
            ans = true;
        }
        // 贪心
        for (int nextI = maxIndex; !ans && nextI >= index + 1; --nextI) {
            dfs(nums, nextI);
        }
    }
    bool canJump(vector<int>& nums) {
        size = nums.size();
        dfs(nums, 0);
        return ans;
    }
};

int main() {
    Solution solution;
    int arr[] = {1,2,3};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    cout << solution.canJump(nums) << endl;
    return 0;
}