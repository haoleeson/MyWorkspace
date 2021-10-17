#include <iostream>
#include <vector>

using namespace std;

/**
 * 面试题 08.11. 硬币（动态规划）
 * 硬币。给定数量不限的硬币，币值为25分、10分、5分和1分，编写代码计算n分有几种表示法。(结果可能会很大，你需要将结果模上1000000007)

示例1:
 输入: n = 5
 输出：2
 解释: 有两种方式可以凑成总金额:
5=5
5=1+1+1+1+1

示例2:
输入: n = 10
输出：4
解释: 有四种方式可以凑成总金额:
10=10
10=5+5
10=5+1+1+1+1+1
10=1+1+1+1+1+1+1+1+1+1

注意:
你可以假设：
0 <= n (总金额) <= 1000000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/coin-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 解题思路：暴力枚举（超出时间限制）
 */
class Solution0 {
public:
    int MAX_VALUE = 1000000007;
    int waysToChange(int n) {
        if (n < 1) {
            return 0;
        }
        int ans = 0;

        for (int i = n / 25; i >= 0; --i) {
            for (int j = (n - i * 25) / 10; j >= 0; --j) {
                ans += 1 + (n - i * 25 - j * 10) / 5;
                if (ans >= MAX_VALUE) {
                    ans %= MAX_VALUE;
                }
            }
        }
        return ans;
    }
};

/**
 * 力扣官解思路：动态规划
 * 首先考虑一个朴素的方法，我们用 f(i,v) 来表示前 i 种面值的硬币构成面值为 v 的方案数量，用 Ci 来表示第 i 种面值的硬币的面值。

举个例子。 假设这里 c={1,5,10,25}，在 i=4 的时候，c_i = 25（假设下标从 11 开始），如果我们要求前 4 种面值构成 90 的方案数量，可以这么写：
f(4,90) = f(3,90) + f(3,90−25) + f(3,90−2×25) + f(3,90−3×25)

这里最多取 3 个 25，所以等式右边一共有四项，分别代表取 0、1、2、3 个 25，即从前 3 种面值构成 90、90−25、90−2×25、90−3×25 四个状态中进行选择。
 */
class Solution {
public:
    int mod = 1000000007;
    int coins[4] = {25, 10, 5, 1};
    int waysToChange(int n) {
        int* dp = new int[n+1]{0};
        dp[0] = 1;
        // 从面值大的 25 开始取
        for (int c = 0; c < 4; ++c) {
            int coin = coins[c];
            for (int i = coin; i <= n; ++i) {
                dp[i] = (dp[i] + dp[i - coin]) % mod;
            }
        }
        int ans = dp[n];
        delete []dp;
        return ans;
    }
};


int main() {
    Solution solution;
    int n = 26;

    cout << solution.waysToChange(n) << endl;

    return 0;
}
