#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 官解：回溯 + 动态规划 O(N!)
// 链接：https://leetcode.cn/problems/palindrome-partitioning/solution/fen-ge-hui-wen-chuan-by-leetcode-solutio-6jkv/
class Solution {
private:
    // f[i][j] 表示子字符串 s[i:j] 是否为回文串
    vector<vector<int>> f;
    // 存储所有可能分割组合
    vector<vector<string>> ret;
    // 临时存储单个可能组合
    vector<string> ans;
    // 源字符串长度
    int n;

    // 回溯：遍历每个可能的分割点
    // @Param1 s: 源字符串
    // @param2 i: 分割点
    void dfs(const string& s, int i) {
        // 回溯结束：分割完源字符串
        if (i == n) {
            ret.push_back(ans);
            return;
        }

        // 尝试余下部分每个点作为分割点
        for (int j = i; j < n; ++j) {
            if (f[i][j]) {
                ans.push_back(s.substr(i, j - i + 1));
                dfs(s, j + 1);
                ans.pop_back();
            }
        }
    }

public:
    vector<vector<string>> partition(string s) {
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
        return ret;
    }
};

int main(void) {
    Solution solution1;
    string s1 = "aab";
    vector<vector<string>> res1 = solution1.partition(s1);
    MyTools::printVec2D(res1);

    Solution solution2;
    string s2 = "a";
    vector<vector<string>> res2 = solution2.partition(s2);
    MyTools::printVec2D(res2);

    Solution solution3;
    string s3 = "abba";
    vector<vector<string>> res3 = solution3.partition(s3);
    MyTools::printVec2D(res3);

    return 0;
}
