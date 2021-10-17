#include <iostream>
#include <vector>
using namespace std;

/**
 * No474. 一和零（背包问题变种）
 * 在计算机界中，我们总是追求用有限的资源获取最大的收益。
 * 现在，假设你分别支配着 m 个 0 和 n 个 1。另外，还有一个仅包含 0 和 1 字符串的数组。
 * 你的任务是使用给定的 m 个 0 和 n 个 1，找到能拼出存在于数组中的字符串的最大数量。每个0和1至多被使用一次。

注意:
给定0和1的数量都不会超过100。
给定字符串数组的长度不会超过600。

示例 1:
输入: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
输出: 4
解释: 总共 4 个字符串可以通过 5 个 0 和 3 个 1 拼出，即 "10","0001","1","0" 。

示例 2:
输入: Array = {"10", "0", "1"}, m = 1, n = 1
输出: 2
解释: 你可以拼出 "10"，但之后就没有剩余数字了。更好的选择是拼出 "0" 和 "1" 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/ones-and-zeroes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 力扣路人思路：动态规划
 */
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        //先计算出每个字符串的0和1的个数
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        //然后定义状态转移方程：dp[i][j][k]代表前i个字符串转满j容量的0字符串和k容量的1字符串所需要的字符串个数
        //状态转移方程：dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - temp[0]][k - temp[1]] + 1);

        //初始化第一行
        vector<int> temp = zeorAndOneNum(strs[0]);
        for(int j = 0; j <= m; ++j){
            for(int k = 0; k <= n; ++k){
                if(j >= temp[0] && k >= temp[1]){
                    dp[j][k] = 1;
                }
            }
        }

        //一维背包：选与不选
        for(int i = 1; i < strs.size(); ++i){
            vector<int> temp = zeorAndOneNum(strs[i]);
            for(int j = m; j >= temp[0]; --j){
                for(int k = n; k >= temp[1]; --k){
                    dp[j][k] = max(dp[j][k], dp[j - temp[0]][k - temp[1]] + 1);
                }
            }
        }
        return dp[m][n];
    }
private:
    vector<int> zeorAndOneNum(string &s){
        int zero = 0;
        int one = 0;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == '0'){
                zero++;
            }
            else{
                one++;
            }
        }
        return {zero, one};
    }
};


/**
 * 动态规划
 */
class Solution0 {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int count0 = 0, count1 = 0, size = strs.size();
        // dp[i][m][n] : 在m个0, n个1前提下，前i个数组的最大选择
        int dp[601][101][101]{0};

        for (int i = 1; i <= size; ++i) {
            // 统计0，1
            count0 = 0;
            count1 = strs[i - 1].length();
            for (char ch : strs[i - 1]) {
                if (ch == '0') {
                    ++count0;
                }
            }
            count1 -= count0;
            cout << count0 << ", " << count1 << endl;
            // 如果不足以选i, dp[i][m][n] = dp[i-1][m][n]
            if (m < count0 || n < count1) {
            }
            // 如果可以选i,   dp[i][m][n] = max(1 + dp[i-1][m-count0][n-count1], dp[i-1][m][n])

        }
        return 0;
    }
};

int main() {
    Solution solution;
    int m = 5;
    int n = 3;
    vector<string> strs;
    strs.push_back("10");
    strs.push_back("0001");
    strs.push_back("111001");
    strs.push_back("1");
    strs.push_back("0");
    cout << solution.findMaxForm(strs, m, n) << endl;
    return 0;
}
