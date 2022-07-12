#include <iostream>
#include <vector>

using namespace std;

// 官解：动态规划 O(N^2)
// 链接：https://leetcode.cn/problems/palindrome-partitioning-ii/solution/fen-ge-hui-wen-chuan-ii-by-leetcode-solu-norx/
class Solution {
public:
    int minCut(string s) {
        int n = s.size();

        // 动态规划：预计算每个子字符串 s[i:j] 是否为回文串 （g[i][j] 表示子字符串 s[i:j] 是否为回文串）
        vector<vector<int>> g(n, vector<int>(n, true));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                g[i][j] = (s[i] == s[j]) && g[i + 1][j - 1];
            }
        }

        // 动态规划：f[i] 表示子字符串 s[0:i] 的最小分割次数
        vector<int> f(n, INT_MAX);
        for (int i = 0; i < n; ++i) {
            // 若 s[0:i] 本身是回文串，无需分割
            if (g[0][i]) {
                f[i] = 0;
            } else {
                // 枚举 s[0:i] 的最后一个回文串起始坐标 j，即 s[j+1:i] 是回文串
                for (int j = 0; j < i; ++j) {
                    if (g[j + 1][i]) {
                        f[i] = min(f[i], f[j] + 1);
                    }
                }
            }
        }

        return f[n - 1];
    }
};

// 思路：回溯 + 动态规划（超时，通过用例 26 / 36） O(N!)
class Solution0 {
private:
    // f[i][j] 表示子字符串 s[i:j] 是否为回文串
    vector<vector<int>> f;
    // 临时分割次数
    int tmpSplitTimes = 0;
    // 源字符串长度
    int n;
    int minSplit = INT_MAX;

    // 回溯：遍历每个可能的分割点
    // @Param1 s: 源字符串
    // @param2 i: 分割点
    void dfs(const string& s, int i) {
        // 回溯结束：分割完源字符串
        if (i == n) {
            return;
        }

        // 若分割次数已超过“当前最小”分割次数，后续不必再尝试找分割点，终止
        if (tmpSplitTimes >= minSplit) {
            return;
        }

        // 尝试余下部分每个点作为分割点
        for (int j = n - 1; j >= i; --j) {
            if (f[i][j]) {
                // 若成功分割完成
                if (j == n - 1) {
                    if (tmpSplitTimes < minSplit) {
                        minSplit = tmpSplitTimes;
                    }
                    return;
                }
                ++tmpSplitTimes;
                dfs(s, j + 1);
                --tmpSplitTimes;
            }
        }
    }

public:
    int minCut(string s) {
        n = s.length();
        f.assign(n, vector<int>(n, true));

        // 动态规划：计算每个子字符串 s[i:j] 是否为回文串
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                // 状态方程：头尾单词相同，且去头尾子串 s[i+1:j-1] 为回文串，则 s[i:j] 也为回文串
                f[i][j] = (s[i] == s[j]) && f[i + 1][j - 1];
            }
        }

        dfs(s, 0);
        return minSplit;
    }
};

int main(void) {
    Solution solution1;
    string s1 = "aab";
    int res1 = solution1.minCut(s1);
    cout << res1 << endl;

    Solution solution2;
    string s2 = "a";
    int res2 = solution2.minCut(s2);
    cout << res2 << endl;

    Solution solution3;
    string s3 = "ab";
    int res3 = solution3.minCut(s3);
    cout << res3 << endl;

    return 0;
}
