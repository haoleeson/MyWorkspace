/** 题目描述：
 * 67. 二进制求和
 * 给定两个二进制字符串，返回他们的和（用二进制表示）。

输入为非空字符串且只包含数字 1 和 0。

示例 1:

输入: a = "11", b = "1"
输出: "100"
示例 2:

输入: a = "1010", b = "1011"
输出: "10101"
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190302
 * */
#include <iostream>
#include <string.h>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        char JFlag = 0;
        //特殊值判断，有一字符串为空
        if (a.length() == 0) {
            return b;
        }
        if (b.length() == 0) {
            return a;
        }
        int a_iterator = a.length()-1, b_iterator = b.length()-1;
        string result_str = (a_iterator < b_iterator) ? b : a;
        int result_iterator = (a_iterator < b_iterator) ? b_iterator : a_iterator;
        while ((a_iterator > -1) && (b_iterator > -1)) {
            result_str[result_iterator] = a[a_iterator] + b[b_iterator] - '0' + JFlag;  // (char)48为'0'
            //判断是否产生进位
            if (result_str[result_iterator] > '1') {
                result_str[result_iterator] -= (char)2;
                JFlag = 1;
            } else {
                JFlag = 0;
            }
            a_iterator--;
            b_iterator--;
            result_iterator--;
        }
        //a余下部分计算
        while (a_iterator > -1) {
            //判断有无进位
            if (JFlag == 1) {
                result_str[result_iterator] = a[a_iterator] + JFlag;
                //判断是否产生进位
                if (result_str[result_iterator] > '1') {
                    result_str[result_iterator] -= (char)2;
                    JFlag = 1;
                } else {
                    JFlag = 0;
                }
            } else {
                return result_str;
            }
            a_iterator--;
            result_iterator--;
        }
        //b余下部分计算
        while (b_iterator > -1) {
            //判断有无进位
            if (JFlag == 1) {
                result_str[result_iterator] = b[b_iterator] + JFlag;
                //判断是否产生进位
                if (result_str[result_iterator] > '1') {
                    result_str[result_iterator] -= (char)2;
                    JFlag = 1;
                } else {
                    JFlag = 0;
                }
            } else {
                return result_str;
            }
            b_iterator--;
            result_iterator--;
        }
        //若，a, b等长,即a_iterator,b_iterator都为-1，但有进位
        if (JFlag == 1) {
            result_str.insert(result_str.begin(), '1');
        }
        return result_str;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    string a = "100";
    string b = "101";
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "Output = " << solution.addBinary(a, b) << endl;
}
