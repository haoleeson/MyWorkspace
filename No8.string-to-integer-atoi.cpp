#include <iostream>
#include <string>

using namespace std;

/**
 * No8. 字符串转换整数 (atoi)
 * 请你来实现一个atoi函数，使其能将字符串转换成整数。
 * 首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。接下来的转化规则如下：
 * s1.如果第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字字符组合起来，形成一个有符号整数。
 * s2.假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成一个整数。
 * 该字符串在有效的整数部分之后也可能会存在多余的字符，那么这些字符可以被忽略，它们对函数不应该造成影响。
 *
 * 注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换
 * ，即无法进行有效转换。在任何情况下，若函数不能进行有效的转换时，请返回 0 。

提示：
本题中的空白字符只包括空格字符 ' ' 。
假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为[−2^31, 2^31− 1]。如果数值超过这个范围，请返回 INT_MAX (2^31− 1) 或INT_MIN (−2^31) 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/string-to-integer-atoi
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
    string STR_ABS_INT_MAX = "2147483647";// 2^31-1
    string STR_ABS_INT_MIN = "2147483648";// -2^31
public:
    int myAtoi(string str) {
        int ans = 0, len = str.length(), iterator = 0, numEndIndex = 0;
        bool positiveFlag = true;

        // 跳过空白字符
        while (iterator < len && str[iterator] == ' ') {
            ++iterator;
        }
        if (iterator == len) {
            return 0;
        }

        // s1. 第一个非空字符为正或者负号
        if (str[iterator] == '+' || str[iterator] == '-') {
            positiveFlag = str[iterator++] == '-' ? false : true;
        }

        // 跳过'0'字符
        while (iterator < len && str[iterator] == '0') {
            ++iterator;
        }
        if (iterator == len) {
            return 0;
        }

        // s2. 假如第一个非空字符是数字
        if (str[iterator] >= '0' && str[iterator] <= '9') {
            numEndIndex = iterator;
            while (numEndIndex < len && str[numEndIndex] >= '0'&& str[numEndIndex] <= '9') {
                ++numEndIndex;
            }
            --numEndIndex; // 减去最后多余的字符

            // 32位INT范围限制判断
            // 超过 10 位，直接返回最大值（正/负）
            if (numEndIndex - iterator + 1 > 10) {
                return positiveFlag ? INT32_MAX : INT32_MIN;
            }
            // 刚好 10 位
            if (numEndIndex - iterator + 1 == 10) {
                string tmpStr(str, iterator, numEndIndex - iterator + 1);
                if (positiveFlag && STR_ABS_INT_MAX.compare(tmpStr) <= 0) {
                    return INT32_MAX;
                }
                if (!positiveFlag && STR_ABS_INT_MIN.compare(tmpStr) <= 0) {
                    return INT32_MIN;
                }
            }

            // 转换为 int
            for (int j = iterator; j <= numEndIndex; ++j) {
                ans *= 10;
                ans += str[j] - '0';
            }
            return positiveFlag ? ans : -ans;
        }

        return ans;
    }
};

int main() {
    Solution solution;
    string str1 = " - 2147483649";

    cout << solution.myAtoi(str1) << endl;
    return 0;
}
