/**
 * No32. 最长有效括号 (正逆序遍历、动态规划、栈)
 * 给定一个只包含 '('和 ')'的字符串，找出最长的包含有效括号的子串的长度。

示例1:
输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"

示例 2:
输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-valid-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

/**
 * 方法3：利用栈存左括号下标
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
class Solution {
public:
    int longestValidParentheses(string s) {
        int len = s.length(), maxSubLen = 0, tmpLen;
        stack<int> stack;
        // 栈存放上一个未被匹配的下标
        stack.push(-1);
        for (int i = 0; i < len; ++i) {
            // 左括号：下标入栈
            if (s[i] == '(') {
                stack.push(i);
            }
            // 右括号：栈顶弹出上一个左括号下标
            else if (s[i] == ')') {
                stack.pop();// 先弹出栈顶表示已匹配右括号
                // 有左括号下标元素可弹出
                if (!stack.empty()) {
                    tmpLen = i - stack.top();
                    if (tmpLen > maxSubLen) {
                        maxSubLen = tmpLen;
                    }
                } else {
                    // 此下标的右括号未被匹配，表示弹出的是上一个未被匹配的下标（并更新未匹配下标）
                    stack.push(i);
                }
            }
        }
        return maxSubLen;
    }
};


/**
 * 方法2：动态规划
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
class Solution2 {
public:
    int longestValidParentheses(string s) {
        int len = s.length(), maxSubLen = 0;
        // dp[i]，表示已i结尾的子串中，最长有效括号子串的长度值。可知：所有以左括号结尾的dp[i] = 0
        // 状态转移方程：
        // 若s[i - dp[i-1] - 1] == '('，dp[i] = dp[i - 1] + 2 + dp[i - dp[i-1] - 2]
        // 若s[i - dp[i-1] - 1] != '('，dp[i] = 0
        vector<int> dp(len, 0);
        for (int i = 1; i < len; ++i) {
            // 只考虑右括号结尾
            if (s[i] == ')') {
                // 若与之匹配的位置下标合法且匹配成功
                if (i - dp[i-1] - 1 > -1 && s[i - dp[i-1] - 1] == '(') {
                    dp[i] = 2 + dp[i - 1];
                    // 继续向前看匹配后是否与再前一位（有效?）子串合并
                    if (i - dp[i-1] - 2 > -1) {
                        dp[i] += dp[i - dp[i-1] - 2];
                    }
                    if (dp[i] > maxSubLen) {
                        maxSubLen = dp[i];
                    }
                }
            }
        }
        return maxSubLen;
    }
};

/**
 * 方法1：正序逆序遍历相结合
 * 时间复杂度：O(2n)
 * 空间复杂度：O(1)
 */
class Solution1 {
public:
    int longestValidParentheses(string s) {
        int maxLen = 0, leftCnt = 0, rightCnt = 0;
        // 正序遍历
        for (char ch : s) {
            // 为左括号
            if (ch == '(') {
                ++leftCnt;
            }
            // 为右括号(需注意破坏条件)
            if (ch == ')') {
                ++rightCnt;
                if (rightCnt == leftCnt) {
                    if (rightCnt > maxLen) {
                        maxLen = rightCnt;
                    }
                } else if (rightCnt > leftCnt) {
                    rightCnt = 0;
                    leftCnt = 0;
                }
            }
        }
        // 逆序遍历
        leftCnt = 0, rightCnt = 0;
        for (int i = s.length() - 1; i >=0; --i) {
            // 为右括号
            if (s[i] == ')') {
                ++rightCnt;
            }
            // 为左括号(需注意破坏条件)
            if (s[i] == '(') {
                ++leftCnt;
                if (leftCnt == rightCnt) {
                    if (leftCnt > maxLen) {
                        maxLen = leftCnt;
                    }
                } else if (leftCnt > rightCnt) {
                    rightCnt = 0;
                    leftCnt = 0;
                }
            }
        }
        return maxLen * 2;
    }
};

int main() {
    Solution solution;
    string strs[] = {
            "()(()",// 2
            "(()", // 2
            ")()())"};// 4
    for (string s : strs) {
        cout << solution.longestValidParentheses(s) << endl;
    }
    return 0;
}
