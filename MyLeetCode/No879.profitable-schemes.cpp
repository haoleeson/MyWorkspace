#include <iostream>
#include <vector>
using namespace std;

/**
 * No879. 盈利计划（背包问题，动态规划）
 * 帮派里有 G 名成员，他们可能犯下各种各样的罪行。
 * 第 i 种犯罪会产生 profit[i] 的利润，它要求 group[i] 名成员共同参与。
 * 让我们把这些犯罪的任何子集称为盈利计划，该计划至少产生 P 的利润。
 * 有多少种方案可以选择？因为答案很大，所以返回它模10^9 + 7的值。

示例1：
输入：G = 5, P = 3, group = [2,2], profit = [2,3]
输出：2
解释： 
至少产生 3 的利润，该帮派可以犯下罪 0 和罪 1 ，或仅犯下罪 1 。
总的来说，有两种方案。

示例2:
输入：G = 10, P = 5, group = [2,3,5], profit = [6,7,8]
输出：7
解释：
至少产生 5 的利润，只要他们犯其中一种罪就行，所以该帮派可以犯下任何罪行 。
有 7 种可能的计划：(0)，(1)，(2)，(0,1)，(0,2)，(1,2)，以及 (0,1,2) 。


提示：
1 <= G <= 100
0 <= P <= 100
1 <= group[i] <= 100
0 <= profit[i] <= 100
1 <= group.length = profit.length <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/profitable-schemes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


/**
 * 力扣路人题解：状态压缩动态规划，滚动利用dp
 */
class Solution {
public:
    const long M = 1e9 + 7;
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int N = profit.size();
        vector<vector<long> > dp(G + 1, vector<long>(P + 1, 0));
        for (int j = 0; j <= G; ++j) {
            dp[j][0] = 1;
        }
        for (int i = 1; i <= N; ++i) {
            int g = group[i - 1];// 第i个的人数占用
            int p = profit[i - 1];// 第i个的利润
            auto dp1 = dp;
            for (int j = G; j >= g; --j) {
                for (int k = 0; k <= P; ++k) {
                    dp[j][k] += dp[j - g][max(k - p, 0)];
                    dp[j][k] %= M;
                }
            }
        }
        return dp[G][P];
    }
};

/**
 * 解题思路：背包问题（问题考虑不全面）
 */
class Solution0 {
public:
    int profitableSchemes(int G, int P, vector<int>& group, vector<int>& profit) {
        int count = 0, lastChoseI, choseI, size = group.size(), size2 = profit.size();
        if (size != size2) {
            return 0;
        }

        // dp[i][j] : 当前容量为 j ，前 i 种的最大利润
        int dp[101][101] = {0};
        for (int i = 1; i <= size; ++i) {
            lastChoseI = 0;
            for (int j = 1; j <= G; ++j) {
                // 装不下
                if (j < group[i - 1]) {
                    dp[i][j] = dp[i - 1][j];
                } else {
                    choseI = dp[i - 1][j - group[i - 1]] + profit[i - 1];

                    dp[i][j] = max(dp[i - 1][j], choseI);

                    // 记录满足 >= P的选择i
                    if (choseI >= P && choseI != lastChoseI) {
                        ++count;
                        lastChoseI = choseI;
                    }
                }
            }
        }
        return count;
    }
};

int main() {
    Solution solution;
    int G = 10;
    int P = 1;
    int arr1[] = {7,1,9,1,9};
    int arr2[] = {1,2,2,1,0};
    vector<int> group(arr1, arr1 + sizeof(arr1) / sizeof(int));
    vector<int> profit(arr2, arr2 + sizeof(arr2) / sizeof(int));
    cout << solution.profitableSchemes(G, P, group, profit);
    return 0;
}
