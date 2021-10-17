/**
 * No844. 比较含退格的字符串
 * 给定 S 和 T 两个字符串，当它们分别被输入到空白的文本编辑器后，判断二者是否相等，并返回结果。 # 代表退格字符。

注意：如果对空文本输入退格字符，文本继续为空。

示例 1：
输入：S = "ab#c", T = "ad#c"
输出：true
解释：S 和 T 都会变成 “ac”。

示例 2：
输入：S = "ab##", T = "c#d#"
输出：true
解释：S 和 T 都会变成 “”。

示例 3：
输入：S = "a##c", T = "#a#c"
输出：true
解释：S 和 T 都会变成 “c”。

示例 4：
输入：S = "a#c", T = "b"
输出：false
解释：S 会变成 “c”，但 T 仍然是 “b”。

提示：
1 <= S.length <= 200
1 <= T.length <= 200
S 和 T 只含有小写字母以及字符 '#'。

进阶：
你可以用 O(N) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/backspace-string-compare
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int sDelCnt = 0, tDelCnt = 0, sIndex = S.length() - 1, tIndex = T.length() - 1;
        // 比较
        while (sIndex >= 0 || tIndex >= 0) {
            // 跳到S末尾一个有效字符所在下标
            while (sIndex >= 0 && (S[sIndex] == '#' || sDelCnt != 0)) {
                sDelCnt += (S[sIndex] == '#') ? 1 : -1;
                --sIndex;
            }
            // 跳到T末尾一个有效字符所在下标
            while (tIndex >= 0 && (T[tIndex] == '#' || tDelCnt != 0)) {
                tDelCnt += (T[tIndex] == '#') ? 1 : -1;
                --tIndex;
            }
            // 若至少有一个无有效字符
            if (sIndex < 0 || tIndex < 0) {
                break;
            }
            // 存在两个有效字符，但字符不等
            if (S[sIndex--] != T[tIndex--]) {
                return false;
            }
        }
        return sIndex == tIndex;
    }
};

int main() {
    Solution solution;
    string strPair[9][2] = {
            {"e##e#o##oyof##q", "e##e#fq##o##oyof##q"}, // true
            {"nzp#o#g", "b#nzp#o#g"}, // true
            {"bbbextm", "bbb#extm"}, // false
            {"bxj##tw", "bxo#j##tw"}, // true
            {"xywrrmp", "xywrrmu#p"}, // true
            {"ab#c", "ad#c"}, // true
            {"ab##", "c#d#"}, // true
            {"a##c", "#a#c"}, // true
            {"a#c", "b"} // false
    };

    for (int i = 0; i < 9; ++i) {
        cout << solution.backspaceCompare(strPair[i][0], strPair[i][1]) << endl;
    }
    return 0;
}
