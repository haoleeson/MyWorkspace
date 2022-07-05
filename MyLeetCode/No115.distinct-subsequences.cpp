#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int lenS = s.length(), lenT = t.length();

        // dpTab[i][j] 表示 t[0:i] 子串 用 s[0:j] 组成，有多少种子序列
        vector<vector<unsigned long long>> dpTab(lenT + 1, vector<unsigned long long>(lenS + 1, 0));
        // 初始值，表示当 t 子串长度为0时（为空），个子串 s[0:0~j] 包含1个空子序列
        for (int j = 0; j < lenS + 1; ++j) {
            dpTab[0][j] = 1;
        }

        // 遍历 t 的个长度 [1, lenT]
        for (int i = 1; i < lenT + 1; ++i) {
            for (int j = 1; j < lenS + 1; ++j) {
                // 状态方程
                // 当 t[i] == s[j] 时， dpTab[i][j] = dpTab[i-1][j-1] + dpTab[i][j-1] // 字符 t[i] 匹配 s[j] 或 字符
                // t[i] 匹配 s[0:j-1] 内的字符 当 t[i] != s[j] 时， dpTab[i][j] = dpTab[i][j-1]                // 字符
                // t[i] 只能匹配 s[0:j-1] 内的字符
                if (t[i - 1] == s[j - 1]) {
                    dpTab[i][j] = dpTab[i - 1][j - 1] + dpTab[i][j - 1];
                } else {
                    dpTab[i][j] = dpTab[i][j - 1];
                }
            }
        }

        return dpTab[lenT][lenS];
    }
};

int main(void) {
    Solution solution;
    string s1 = "rabbbit";
    string t1 = "rabbit";
    int res1 = solution.numDistinct(s1, t1);
    cout << res1 << endl;

    string s2 = "babgbag";
    string t2 = "bag";
    int res2 = solution.numDistinct(s2, t2);
    cout << res2 << endl;

    return 0;
}
