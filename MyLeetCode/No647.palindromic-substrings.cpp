#include <iostream>
#include <string>
using namespace std;

/**
 * No647. 回文子串
 * 给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。
 * 具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

示例 1：
输入："abc"
输出：3
解释：三个回文子串: "a", "b", "c"

示例 2：
输入："aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

提示：
输入的字符串长度不会超过 1000 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/palindromic-substrings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 解题思路：暴力枚举 O(n^3)
 * coder: eisenhao
 * date: 20200819
 */
class Solution1 {
public:
    int countSubstrings(string s) {
        int len = s.size(), res = len;

        for (int i = 0; i < len - 1; ++i) {
            for (int j = i + 1; j < len; ++j) {
                if (isPalindromeSubstring(s, i, j)) {
                    ++res;
                }
            }
        }
        return res;
    }

    bool isPalindromeSubstring(string& s, int LeftIndex, int RightIndex) {
        while (LeftIndex < RightIndex) {
            if (s[LeftIndex++] != s[RightIndex--]) {
                return false;
            }
        }
        return true;
    }
};

/**
 * 解题思路：枚举 O(n^2) + 中心拓展
 * coder: 官方题解：
 * 枚举每一个可能的回文中心，然后用两个指针分别向左右两边拓展，当两个指针指向的元素相同的时候就拓展，否则停止拓展。
 * 关键点：考虑回文长度是奇数和回文长度是偶数的两种情况。如果回文长度是奇数，那么回文中心是一个字符；如果回文长度是偶数，那么中心是两个字符。
 * 当然你可以做两次循环来分别枚举奇数长度和偶数长度的回文，但是我们也可以用一个循环搞定：
 * 长度为 n 的字符串会生成 2n−1 组回文中心 [l_i, r_i]，其中 l_i = ⌊i/2⌋，r_i = l_i + (i mod 2)。这样我们只要从 0 到 2n - 2 遍历 i，就可以得到所有可能的回文中心，这样就把奇数长度和偶数长度两种情况统一起来了。
 */
class Solution2 {
public:
    int countSubstrings(string s) {
        int n = s.size(), ans = 0;
        for (int i = 0; i < 2 * n - 1; ++i) {
            int l = i / 2, r = i / 2 + i % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {
                --l;
                ++r;
                ++ans;
            }
        }
        return ans;
    }
};


/**
 * 解题思路：dp  O(n^2)
 * coder: eisenhao
 * date: 20200819
 */
class Solution {
public:
    int countSubstrings(string s) {
        int len = s.size(), res = len;

        // 初始化二维 Dp 数组
        bool **dp;
        dp = new bool*[len];
        for (int i = 0; i < len; ++i) {
            dp[i] = new bool[len]{false};
            dp[i][i] = true;
        }

        // 判断(i,j)子串是否是回文子串
        for (int j = 1; j < len; ++j) {
            dp[j-1][j] = s[j-1] == s[j];
            for (int i = j - 2; i >= 0; --i) {
                dp[i][j] = dp[i+1][j-1] && (s[i] == s[j]);
            }
        }

        // 统计
        for (int i = 0; i < len - 1; ++i) {
            for (int j = i + 1; j < len; ++j) {
                if (dp[i][j]) {
                    ++res;
                }
            }
        }
        return res;
    }
};

int main() {
    Solution solution;
    string string1 = "abc";
    string string2 = "aaa";
    cout << solution.countSubstrings(string1) << endl;
    cout << solution.countSubstrings(string2) << endl;
    return 0;
}
