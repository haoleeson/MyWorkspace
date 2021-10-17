#include <iostream>
#include <string>

using namespace std;

/**
 * No6. Z 字形变换（推算下标规律）
 * 将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如：输入字符串为 "LEETCODEISHIRING"行数为 3 时，排列如下：
L   C   I   R
E T O E S I I G
E   D   H   N
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
示例1:

输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"
示例2:

输入: s = "LEETCODEISHIRING", numRows =4
输出:"LDREOEIIECIHNTSG"
解释:

L     D     R
E   O E   I I
E C   I H   N
T     S     G

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/zigzag-conversion
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 分析：将形似小写 l 倒钩看作一个部分（partSize = 2 * numRows - 2），行数：numRows，列数：numRows - 1
 * 第一行：字符对应字符串中的下标为：0, 0 + partSize, 0 + partSize * 2, ...
 * 第二行：字符对应字符串中的下标为：{1, partSize - 1}, {1 + partSize, partSize - 1 + partSize},...
 *
 * 最后一行：字符对应字符串中的下标为：numRows-1, numsRows-1 + partSize,...
 *
 * 时间复杂度 O(n)
 */
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows < 2) {
            return numRows == 1 ? s : "";
        }
        int len = s.length(), partSize = 2 * numRows - 2, iterator = 0;
        string out(s);

        // 按行输出
        for (int row = 0; row < numRows; ++row) {
            for (int i1 = row, i2 = 0; i1 < len; i1 += partSize) {
                // 打印第一个字符
                out[iterator++] = s[i1];

                // 对第一行 和 最后一行每次只用打印一个字符
                if (row == 0 || row == numRows - 1) {
                    continue;
                }

                // 打印第二个字符
                i2 = (numRows - 1 - i1 % partSize) * 2 + i1;
                if (i2 < len) {
                    out[iterator++] = s[i2];
                }
            }
        }

        return out;
    }
};

int main() {
    Solution solution;
    string str1 = "LEETCODEISHIRING";
    cout << solution.convert(str1, 3) << endl;

    string str2 = "LEETCODEISHIRING";
    cout << solution.convert(str2, 4) << endl;

    return 0;
}
