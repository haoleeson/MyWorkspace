#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 思路：动态规划（by AC_OIer）
// 链接：https://leetcode.cn/problems/scramble-string/solution/gong-shui-san-xie-yi-ti-san-jie-di-gui-j-hybk/
class Solution {
public:
    bool isScramble(string s1, string s2) {
        int len1 = s1.length(), len2 = s2.length(), n;

        if (len1 != len2) {
            return false;
        } else if (s1 == s2) {
            return true;
        }
        n = len1;

        // dpTab[i][j][len] 表示 s1 从 i 开始和 s2 从 j 开始的长度为 len 的子串是否能够彼此“扰乱”得到
        vector<vector<vector<bool>>> dpTab(n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));

        // 先处理长度为 1 的情况 O(N^2)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (s1[i] == s2[j]) {
                    dpTab[i][j][1] = true;
                }
            }
        }

        // 枚举子串长度 2～n
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i <= n - len; ++i) {
                for (int j = 0; j <= n - len; ++j) {
                    // 枚举子串分割位置 [1,len-1]
                    for (int k = 1; k < len; ++k) {
                        // 分割后是否保持顺序
                        bool a = dpTab[i][j][k] && dpTab[i + k][j + k][len - k];       // s = x + y
                        bool b = dpTab[i][j + len - k][k] && dpTab[i + k][j][len - k]; // s = y + x
                        if (a || b) {
                            dpTab[i][j][len] = true;
                        }
                    }
                }
            }
        }

        return dpTab[0][0][n];
    }
};

int main(void) {
    Solution solution;

    string a1 = "great";
    string b1 = "rgeat";
    bool res1 = solution.isScramble(a1, b1);
    cout << res1 << endl;

    string a2 = "abcde";
    string b2 = "caebd";
    bool res2 = solution.isScramble(a2, b2);
    cout << res2 << endl;

    string a3 = "a";
    string b3 = "a";
    bool res3 = solution.isScramble(a3, b3);
    cout << res3 << endl;

    return 0;
}
