#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 思路：动态规划 O(n)
// 链接：https://leetcode.cn/problems/decode-ways/solution/gong-shui-san-xie-gen-ju-shu-ju-fan-wei-ug3dd/
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        s = " " + s;

        // dpTab 表示 s[0:i]子串 的编码数量
        vector<int> dpTab(n + 1, 0);
        dpTab[0] = 1;

        for (int i = 1; i < n + 1; i++) {
            int a = s[i] - '0';                         // 数字 s[i] 单独构成一个字母
            int b = (s[i - 1] - '0') * 10 + s[i] - '0'; // 数字 s[i] 与前一个数字 s[i-1] 共同构成一个字母
            // 单个数字合法，则继承 dpTab[i - 1] 的编码数
            if (1 <= a && a <= 9) {
                dpTab[i] = dpTab[i - 1];
            }
            // 两个数字合法，则在 单个字符 dpTab[i] 可行解基础上，再加上两个数字的编码数量（dpTab[i - 2]）
            if (10 <= b && b <= 26) {
                dpTab[i] += dpTab[i - 2];
            }
        }

        return dpTab[n];
    }
};

// 思路：回溯（超出时间限制）
class Solution1 {
public:
    int numDecodings(string s) {
        lenS = s.length();
        //        buf = new char[lenS + 1]{0};
        backtrace(s, 0, 0);

        return res;
    }

private:
    //    char* buf = nullptr;
    int lenS;
    // 转码表，其中 num2charTab[0] 表示错误码 '0'
    char num2charTab[27] = {'0', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int res = 0;
    vector<string> strs;

    // 将字符串下标开始(是否两位数)的数字，转换为字符编码
    inline char validDecodeChar(string& s, int index, bool isLen2) {
        // 长度不支持为 2（超出长度），返回错误码
        if (isLen2 && index == lenS - 1) {
            return num2charTab[0];
        }

        // 零开头，返回错误码
        if (s[index] == '0') {
            return num2charTab[0];
        }

        // 数字超出范围（ > 26），返回错误码
        int num = isLen2 ? (s[index] - '0') * 10 + s[index + 1] - '0' : s[index] - '0';
        if (num > 26) {
            return num2charTab[0];
        }

        return num2charTab[num];
    }

    void backtrace(string& s, int index, int iterator) {
        // 结束条件
        if (index >= lenS) {
            ++res;
            //            buf[iterator] = '\0';
            //            string tmpStr(buf);
            //            strs.push_back(tmpStr);
            return;
        }

        // 遍历所有可能（1 个数字 or 2 个数字）
        for (int len = 1; len <= 2; ++len) {
            char ch = validDecodeChar(s, index, len == 2);
            if (ch == num2charTab[0]) {
                break;
            }

            //            buf[iterator] = ch;
            backtrace(s, index + len, iterator + 1);
        }
    }
};

int main(void) {
    Solution solution1;
    string s1 = "12";
    int res1 = solution1.numDecodings(s1);
    cout << res1 << endl;

    Solution solution2;
    string s2 = "226";
    int res2 = solution2.numDecodings(s2);
    cout << res2 << endl;

    return 0;
}
