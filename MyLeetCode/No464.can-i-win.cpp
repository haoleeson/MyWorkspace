#include <iostream>
using namespace std;

/**
 * No464. 我能赢吗（动态规划）
 * 两个玩家可以轮流从公共整数池中抽取从 1 到 15 的整数（不放回），直到累计整数和 >= 100。
 * 给定一个整数maxChoosableInteger（整数池中可选择的最大数）和另一个整数desiredTotal（累计和），
 * 判断  先出手的玩家  是否能稳赢（假设两位玩家游戏时都表现最佳）？
 *
 * 备注：你可以假设maxChoosableInteger不会大于 20，desiredTotal不会大于 300。

示例：
输入：
maxChoosableInteger = 10
desiredTotal = 11

输出：
false

解释：
无论第一个玩家选择哪个整数，他都会失败。
第一个玩家可以选择从 1 到 10 的整数。
如果第一个玩家选择 1，那么第二个玩家只能选择从 2 到 10 的整数。
第二个玩家可以通过选择整数 10（那么累积和为 11 >= desiredTotal），从而取得胜利.
同样地，第一个玩家选择任意其他整数，第二个玩家都会赢。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/can-i-win
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


class Solution {
    bool* dp;
public:
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if (maxChoosableInteger > desiredTotal) {
            return true;
        }
        if ((maxChoosableInteger + 1) * maxChoosableInteger / 2 < desiredTotal) {
            return false;
        }

        // 0xFFFFF，用一个2.5字节(int)就能表示20位，每一位的是否已被选择的状态情况，共有2^20种可能
        // 初始化dp，大小为 2^maxChoosableInteger，可以记录每个选择情况是否能赢
        dp = new bool[(1 << maxChoosableInteger) - 1]{false};
        bool ans = dfs(maxChoosableInteger, desiredTotal, 0);
        delete []dp;
        return ans;
    }

    /**
     * @param maxChoosableInteger 最大能选择的数
     * @param tmpTotal 实时剩余目标累计和
     * @param choosedBitMap [1...n]已被选择的数的位图
     * @return
     */
    bool dfs(int maxChoosableInteger, int tmpTotal, int choosedBitMap) {
        // 备忘录，加速已计算过的分支
        if (dp[choosedBitMap]) {
            return dp[choosedBitMap];
        }

        // 遍历选择[1...n]中剩余未被选择过的数
        for (int i = 1; i <= maxChoosableInteger; ++i) {
            int bit = (1 << (i - 1));// i 被选中的二进制位表示
            // 若 i 未被选择过
            if (!(bit & choosedBitMap)) {
                // 若 i 超过 实时剩余目标累计和（则胜出），或选择i后，下一次对手的结果为false（自己胜出）
                if (i >= tmpTotal || !dfs(maxChoosableInteger, tmpTotal - i, choosedBitMap | bit)) {
                    dp[choosedBitMap] = true;
                    return true;
                }
            }
        }

        // 经过上面遍历[1..n]中剩下未被选择的数都不可能赢，返回false
        dp[choosedBitMap] = false;
        return false;
    }
};

int main() {
    Solution solution;
    int maxChoosableInteger = 10;
    int desiredTotal = 11;

    cout << solution.canIWin(maxChoosableInteger, desiredTotal) << endl;

    return 0;
}
