#include <iostream>
#include <string>

using namespace std;

/**
 * No459. 重复的子字符串
 * 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。给定的字符串只含有小写英文字母，并且长度不超过10000。

示例 1:
输入: "abab"
输出: True
解释: 可由子字符串 "ab" 重复两次构成。

示例 2:
输入: "aba"
输出: False

示例 3:
输入: "abcabcabcabc"
输出: True
解释: 可由子字符串 "abc" 重复四次构成。 (或者子字符串 "abcabc" 重复两次构成。)

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/repeated-substring-pattern
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        int len = s.length();
        if (len < 2) {
            return false;
        }

        char firstCh = s[0];
        int endSubStrIndex = 0;
        for (int i = 1, j = 1; i < len; ++i) {
            // 找到下一个 firstCh
            if (s[i] != firstCh) {
                continue;
            }
            endSubStrIndex = i - 1;
            // 判断重复子串
            while(true) {
                ++i;
                for (j = 1; i < len && j <= endSubStrIndex && s[j] == s[i]; ++j) {
                    ++i;
                }
                // 若遍历完字符串，返回结果
                if (i == len) {
                    return j > endSubStrIndex;
                }
                // 子串仅部分重复，或下一子串与头字符不相等（打破重复）
                if (j <= endSubStrIndex || s[i] != firstCh) {
                    i -= j;
                    break;
                }
            }
        }
        return false;
    }
};

int main() {
    Solution solution;
    string str = "abaababaab";
    cout << solution.repeatedSubstringPattern(str) << endl;
    return 0;
}
