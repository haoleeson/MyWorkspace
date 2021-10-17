#include <iostream>
#include <string>
using namespace std;
/**
 * No5. 最长回文子串
 * 给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：
输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。

示例 2：
输入: "cbbd"
输出: "bb"
 */

/**
 * 解题思路：中心扩展法
 */
class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.length(), index = 0, leftIndex = 0, rightIndex = 0, maxLen = 0, beginIndex = 0, tmpLen = 0;
        if (len < 2) {
            return s;
        }

        while (index < len) {
            leftIndex = index;
            rightIndex = index;

            // 全是相同字符 | 偶回文子串right下标加1
            while (index < len - 1 && s[index] == s[index + 1]) {
                ++index;
                ++rightIndex;
            }
            while (rightIndex < len && leftIndex >= 0 && s[leftIndex] == s[rightIndex]) {
                --leftIndex;
                ++rightIndex;
            }

            tmpLen = rightIndex - leftIndex - 1;// 消除leftIndex和rightIndex共计多加的2个
            if (maxLen < tmpLen) {
                maxLen = tmpLen;
                beginIndex = leftIndex + 1;// 消除leftIndex多减的1个
            }
            ++index;
        }
        return s.substr(beginIndex, maxLen);
    }
};

int main() {
    Solution solution;
    string inputStr = "abbbbbcb";

    cout << "median of two sorted arrays is: " << solution.longestPalindrome(inputStr) << endl;

    return 0;
}
