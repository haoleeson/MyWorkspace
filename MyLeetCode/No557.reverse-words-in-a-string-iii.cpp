#include <iostream>
#include <string>

using namespace std;

/**
 * No557. 反转字符串中的单词 III
 * 给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。



示例：
输入："Let's take LeetCode contest"
输出："s'teL ekat edoCteeL tsetnoc"


提示：

在字符串中，每个单词由单个空格分隔，并且字符串中不会有任何额外的空格。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/reverse-words-in-a-string-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 分析：要构成回文串，则首字符必与后面的子串构成回文串，尾部则是需要逆向添加到首部左侧的补偿串
 * 时间复杂度：O(n^2)，4万长度字符串超时
 */

class Solution {
public:
    string reverseWords(string s) {
        int lastSpaceIndex = -1, spaceIndex = -1, leftIndex = 0, rightIndex = 0, len = s.length();
        char tmp;

        while (spaceIndex < len) {
            lastSpaceIndex = spaceIndex++;
            // 找到下一空格
            while (spaceIndex < len && s[spaceIndex] != ' ') {
                ++spaceIndex;
            }
            // 反转两个空格间的子串
            leftIndex = lastSpaceIndex + 1;
            rightIndex = spaceIndex - 1;
            while (leftIndex < rightIndex) {
                tmp = s[leftIndex];
                s[leftIndex] = s[rightIndex];
                s[rightIndex] = tmp;
                ++leftIndex;
                --rightIndex;
            }
        }

        return s;
    }
};



int main() {
    Solution solution;
    string string1 = "Let's take LeetCode contest";
    cout << solution.reverseWords(string1) << endl;
    return 0;
}
