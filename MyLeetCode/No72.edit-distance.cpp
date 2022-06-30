#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 思路：动态规划（by powcai）
class Solution {
public:
    int minDistance(string word1, string word2) {
        int len1 = word1.length(), len2 = word2.length();

        // dpTab[i][j] 代表 word1 的子串 [0:i] 转换成 word2 的子串[0:j] 需要的最少步数
        vector<vector<int>> dpTab(len1 + 1, vector<int>(len2 + 1, 0));
        // 初始化 dpTab[][] 第一行
        for (int i = 0; i <= len2; ++i) {
            dpTab[0][i] = i;
        }
        // 初始化 dpTab[][] 第一列
        for (int i = 0; i <= len1; ++i) {
            dpTab[i][0] = i;
        }

        // 从上至下，从左至右，根据 状态转移方程 更新 dpTab
        for (int i = 1; i <= len1; ++i) {
            for (int j = 1; j <= len2; ++j) {
                // 若字符相同，保留，不增加步数
                if (word1[i - 1] == word2[j - 1]) {
                    dpTab[i][j] = dpTab[i - 1][j - 1];
                } else {
                    // 若字符不同，从前置状态中，增加 1 步（替换、删除、插入）操作转换过来
                    // dpTab[i-1][j-1]+1 表示替换操作
                    // dpTab[i-1][j]+1 表示删除操作，word1进行删除
                    // dpTab[i][j-1]+1 表示插入操作，word2进行插入
                    dpTab[i][j] = 1 + minOfThree(dpTab[i - 1][j - 1], dpTab[i - 1][j], dpTab[i][j - 1]);
                }
            }
        }

        return dpTab[len1][len2];
    }

private:
    inline int minOfThree(int a, int b, int c) { return min(min(a, b), c); }
};

int main(void) {
    Solution solution;

    string start1 = "horse";
    string end1 = "ros";
    int res1 = solution.minDistance(start1, end1);
    cout << res1 << endl;

    string start2 = "intention";
    string end2 = "execution";
    int res2 = solution.minDistance(start2, end2);
    cout << res2 << endl;

    return 0;
}
