#include <iostream>
#include <string>
using namespace std;
/**
43. 字符串相乘
给定两个以字符串形式表示的非负整数num1和num2，返回num1和num2的乘积，它们的乘积也表示为字符串形式。

示例 1:
输入: num1 = "2", num2 = "3"
输出: "6"

示例2:
输入: num1 = "123", num2 = "456"
输出: "56088"

说明：
num1和num2的长度小于110。
num1 和num2 只包含数字0-9。
num1 和num2均不以零开头，除非是数字 0 本身。
不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。

*/

class Solution {
public:
    /**
     * 字符串相乘
     * @param num1
     * @param num2
     * @return
     */
    string multiply(string num1, string num2) {
        if (num2.length() > num1.length()) {
            return multiply(num2, num1);
        }

        string ans = "0", endZeroStr = "", tmp;
        int iterator2 = num2.length() - 1;
        while (iterator2 >= 0) {
            tmp = singleMultiply(num1, num2[iterator2--]) + endZeroStr;
            ans = addStrings(ans, tmp);
            endZeroStr += "0";
        }

        return ans;
    }

private:
    /**
     * 字符串数字与一位数相乘
     * @param num1
     * @param num2
     * @return
     */
    string singleMultiply(string num1, char num2) {
        if (num2 < '2') {
            return num2 == '0' ? "0" : num1;
        }

        string ans = num1;
        int jinWei = 0, tmp = 0, mulNum = (int)(num2 - '0'), iterator = ans.length() - 1;
        while (iterator >= 0) {
            tmp = mulNum * (int)(ans[iterator] - '0') + jinWei;
            jinWei = 0;
            if (tmp > 9) {
                jinWei = tmp / 10;
                tmp %= 10;
            }
            ans[iterator--] = '0' + (char)tmp;
        }

        if (jinWei != 0) {
            ans = "0" + ans;
            ans[0] = '0' + (char)jinWei;
        }

        return ans;
    }

    /**
     * 两字符串数相加
     * @param num1
     * @param num2
     * @return
     */
    string addStrings(string num1, string num2) {
        if (num2.length() > num1.length()) {
            return addStrings(num2, num1);
        }

        string ans = num1;
        int iterator1 = ans.length() - 1;
        int iterator2 = num2.length() - 1;
        char jinWei = 0, tmp = 0;

        while (iterator2 >= 0) {
            tmp = ans[iterator1] + num2[iterator2--] + jinWei - '0';
            jinWei = 0;
            if (tmp > '9') {
                tmp -= 10;
                jinWei = 1;
            }
            ans[iterator1--] = tmp;
        }

        while (iterator1 >= 0) {
            tmp = ans[iterator1] + jinWei;
            jinWei = 0;
            if (tmp > '9') {
                tmp -= 10;
                jinWei = 1;
            }
            ans[iterator1--] = tmp;
        }

        return jinWei == 1 ? "1" + ans : ans;
    }
};

int main() {
    Solution solution;

    string num1 = "123";
    string num2 = "321";

    cout << num1 << " * " << num2 << " = " << solution.multiply(num1, num2) << endl;

    return 0;
}
