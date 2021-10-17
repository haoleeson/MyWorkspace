#include <iostream>
#include "myTools.h"
using namespace std;

/**
 * No65. 有效数字
 * 验证给定的字符串是否可以解释为十进制数字。

例如:

"0" => true
" 0.1 " => true
"abc" => false
"1 a" => false
"2e10" => true
" -90e3   " => true
" 1e" => false
"e3" => false
" 6e-1" => true
" 99e2.5 " => false
"53.5e93" => true
" --6 " => false
"-+3" => false
"95a54e53" => false

说明: 我们有意将问题陈述地比较模糊。在实现代码之前，你应当事先思考所有可能的情况。这里给出一份可能存在于有效十进制数字中的字符列表：

数字 0-9
指数 - "e"
正/负号 - "+"/"-"
小数点 - "."
当然，在输入中，这些字符的上下文也很重要。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/valid-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 约束条件：
 * 1. 符号：    有效字符表(数字，指数，正负号，小数点)： [0-9],'e','+','-','.'
 * 2. 指数：    指数前后必须有数字，不允许重复e，且指数后的数字不允许出现小数点
 * 3. 正负号：  正负号前方不允许出现数字和其他正负号（多个正负号），再 e 后可多出现依次正负号
 * 4. 小数点：  (小数点前后必须有数字)?(用例不需)，且小数点不允许出现多个
 */
class Solution {
public:
    bool isNumber(string s) {
        // 去除首尾空格
        if (!s.empty()) {
            s.erase(0, s.find_first_not_of(' '));
            s.erase(s.find_last_not_of(' ') + 1);
        }

        bool numFlag = false;// 前置数字
        bool eFlag = false;// 指数标识
        bool signFlag = false;// 正负号标识
        bool pointFlag = false;// 小数点标识

        for (char ch : s) {
            switch (ch) {
                // 数字
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (!numFlag) {
                        numFlag = true;
                    }
                    break;
                    
                // 指数
                case 'e':
                    // 不允许重复e，且前方必须出现有效数字
                    if (eFlag || !numFlag) {
                        return false;
                    }
                    eFlag = true;
                    // 将小数点符号置true，后方不允许出现小数点符号
                    pointFlag = true;
                    // 清理正负号标识
                    signFlag = false;
                    // 清理数字标识
                    numFlag = false;
                    break;

                // 正负号
                case '+':
                case '-':
                    // 不允许前方有正负号、数字、无e且有小数点
                    if (signFlag || numFlag || (!eFlag && pointFlag)) {
                        return false;
                    }
                    signFlag = true;
                    break;

                // 小数点
                case '.':
                    // (小数点前后必须有数字)?(用例不需)，不允许重复小数点
                    if (pointFlag) {
                        return false;
                    }
                    pointFlag = true;
                    break;

                // 其他无效字符
                default:
                    return false;
                    break;
            }
        }
        return numFlag;
    }
};

int main() {
    Solution solution;
    string strBuff[] = {
            "0", // true
            " 0.1 ", // true
            "abc", // false
            "1 a", // false
            "2e10", // true
            " -90e3 ", // true
            " 1e", // false
            "e3", // false
            " 6e-1", // true
            " 99e2.5", // false
            "53.5e93", // true
            " --6 ", // false
            "-+3", // false
            "95a54e53", // false
            ".1", // true
            "3." // true
    };
    for (string str : strBuff) {
        if (solution.isNumber(str)) {
            cout << "\"" << str << "\" => " <<   "true" << endl;
        } else {
            cout << "\"" << str << "\" => " <<   "false" << endl;
        }

    }
    return 0;
}