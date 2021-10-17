#include <iostream>
#include <vector>

using namespace std;

/**
 * No486. 预测赢家（动态规划）
 * 给定一个表示分数的非负整数数组。 玩家 1 从数组任意一端拿取一个分数，随后玩家 2 继续从剩余数组任意一端拿取分数，然后玩家 1 拿，…… 。
 * 每次一个玩家只能拿取一个分数，分数被拿取之后不再可取。直到没有剩余分数可取时游戏结束。最终获得分数总和最多的玩家获胜。
 * 给定一个表示分数的数组，预测玩家1是否会成为赢家。你可以假设每个玩家的玩法都会使他的分数最大化。



示例 1：
输入：[1, 5, 2]
输出：False
解释：一开始，玩家1可以从1和2中进行选择。
如果他选择 2（或者 1 ），那么玩家 2 可以从 1（或者 2 ）和 5 中进行选择。如果玩家 2 选择了 5 ，那么玩家 1 则只剩下 1（或者 2 ）可选。
所以，玩家 1 的最终分数为 1 + 2 = 3，而玩家 2 为 5 。
因此，玩家 1 永远不会成为赢家，返回 False 。

示例 2：
输入：[1, 5, 233, 7]
输出：True
解释：玩家 1 一开始选择 1 。然后玩家 2 必须从 5 和 7 中进行选择。无论玩家 2 选择了哪个，玩家 1 都可以选择 233 。
     最终，玩家 1（234 分）比玩家 2（12 分）获得更多的分数，所以返回 True，表示玩家 1 可以成为赢家。

提示：
1 <= 给定的数组长度<= 20.
数组里所有分数都为非负数且不会大于 10000000 。
如果最终两个玩家的分数相等，那么玩家 1 仍为赢家。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/predict-the-winner
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


/**
 * 官方思路：动态规划
 * 若使用递归，存在大量重复计算，因此时间复杂度很高。由于存在重复子问题，因此可以使用动态规划降低时间复杂度。
 *
 * 定义二维数组 dp[i][j] : 数组剩下部分[i,j]当前玩家与另一玩家的分数之差的最大值 (i <= j)
 * 当 i == j,    dp[i][j] = nums[i]
 * 当 i < j,     dp[i][j] = max(nums[i] - dp[i+1][j], nums[j] - dp[i][j-1])
 */
class Solution {
public:
    bool PredictTheWinner(vector<int>& nums) {
        int ans, size = nums.size();
        int dp[20][20] = {0};

        for (int i = size - 1; i >= 0; --i) {
            dp[i][i] = nums[i];
            for (int j = i + 1; j < size; ++j) {
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }

        ans = dp[0][size - 1];
        return ans >= 0;
    }
};

/**
 * 思路：递归
 * 时间复杂度：O(2^n)
 * 空间复杂度：O(n)，空间复杂度取决于递归使用的栈空间。
 */
class Solution0 {
public:
    /**
     * 先手得分与后手得分之差
     * @param leftIndex 左侧下标
     * @param rightIndex 右侧下标
     * @param diff 与另一角色分数之前累积的差值
     * @param nums 整数数组
     * @return
     */
    int totalDiff(vector<int>&nums, int leftIndex, int rightIndex, bool isFirst) {
        if (leftIndex == rightIndex) {
            return isFirst ? nums[leftIndex] : -nums[leftIndex];
        }

        int scoreLeft, scoreRight;
        // 若为先手
        if (isFirst) {
            scoreLeft = totalDiff(nums, leftIndex + 1, rightIndex, !isFirst) + nums[leftIndex];
            scoreRight = totalDiff(nums, leftIndex, rightIndex - 1, !isFirst) + nums[rightIndex];
            return max(scoreLeft, scoreRight);
        }
        // 若为后手
        scoreLeft = totalDiff(nums, leftIndex + 1, rightIndex, !isFirst) - nums[leftIndex];
        scoreRight = totalDiff(nums, leftIndex, rightIndex - 1, !isFirst) - nums[rightIndex];
        return -max(-scoreLeft, -scoreRight);
    }

    bool PredictTheWinner(vector<int>& nums) {
        int size = nums.size();
        return totalDiff(nums, 0, size - 1, true) >= 0;
    }
};

int main() {
    Solution solution;
    int arr[] = {1, 5, 2};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    cout << solution.PredictTheWinner(nums) << endl;
    return 0;
}
