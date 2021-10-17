#include <iostream>
#include <string>
using namespace std;
/**
 * 3. 无重复字符的最长子串
 * 给定一个字符串，请你找出其中不含有重复字符的最长子串的长度。

示例1:
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

示例 2:
输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

示例 3:
输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是"wke"，所以其长度为 3。
    请注意，你的答案必须是 子串 的长度，"pwke"是一个子序列，不是子串。

*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }

        bool charBit[256] = {false};
        int startIterator = 0, endIterator = 0, Len = s.length(), maxSubLen = 1;
        charBit[(int)s[startIterator]] = true;

        while (endIterator < Len) {
            if (maxSubLen < (endIterator - startIterator + 1)) {
                maxSubLen = endIterator - startIterator + 1;
            }
            ++endIterator;

            // 若尾指针遇到重复字符，缩头指针直至消除冲突
            while (charBit[(int)s[endIterator]]) {
                charBit[(int)s[startIterator++]] = false;
            }
            charBit[(int)s[endIterator]] = true;
        }
        return maxSubLen;
    }
};

int main() {
    Solution solution;

    string string1 = "abcabcbb";
    string string2 = "bbbbb";
    string string3 = "pwwkew";
    cout << "max substrlen of string[" << string1 << "] is " << solution.lengthOfLongestSubstring(string1) << endl;
    cout << "max substrlen of string[" << string2 << "] is " << solution.lengthOfLongestSubstring(string2) << endl;
    cout << "max substrlen of string[" << string3 << "] is " << solution.lengthOfLongestSubstring(string3) << endl;

    return 0;
}
