#include <iostream>
#include <vector>

using namespace std;

// 动态规划
class Solution {
public:
    bool isMatch(string s, string p) {
        int lenS = s.size(), lenP = p.size();

        // dpTab[i][j] 表示字符串 s[0 ~ j] 与模式串 p[0 ~ i] 是否匹配
        vector<vector<bool>> dpTab(lenP + 1, vector<bool>(lenS + 1, false));
        dpTab[0][0] = true;

        for (int i = 0; i < lenP; ++i) {
            // 若模式串中字符 p[i] 为 '*'，则尝试 p[0 ~ i] 匹配 s[0 ~ (j .. lenS-1)]
            if (p[i] == '*') {
                // 整行余下列是否全可达
                bool rowSetFlg = false;
                for (int j = 0; j < lenS + 1; ++j) {
                    if (rowSetFlg) {
                        dpTab[i + 1][j] = true;
                    } else if (dpTab[i][j]) {
                        rowSetFlg = true;
                        dpTab[i + 1][j] = true;
                    }
                }
                continue;
            }

            // 若模式串中字符 p[i] 为其他字符 [a-z\?]
            for (int j = 0; j < lenS; ++j) {
                if (p[i] == '?' || s[j] == p[i]) {
                    dpTab[i + 1][j + 1] = dpTab[i][j];
                }
            }
        }
        return dpTab[lenP][lenS];
    }
};

int main(void) {
    Solution solution;
    cout << solution.isMatch("aa", "a") << endl;
    cout << solution.isMatch("aa", "*") << endl;
    cout << solution.isMatch("cb", "?a") << endl;
    cout << solution.isMatch("adceb", "*a*b") << endl;
    cout << solution.isMatch("acdcb", "a*c?b") << endl;

    return 0;
}
