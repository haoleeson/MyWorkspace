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

class Solution1 {
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

/**
 * Leetcode评论启发：
 * num1的第i位(高位从0开始)和num2的第j位相乘的结果在乘积中的位置是[i+j, i+j+1]
例: 123 * 45,  123的第1位 2 和45的第0位 4 乘积 08 存放在结果的第[1, 2]位中
  index:    0 1 2 3 4

                1 2 3
            *     4 5
            ---------
                  1 5
                1 0
              0 5
            ---------
              0 6 1 5
                1 2
              0 8
            0 4
            ---------
            0 5 5 3 5
   这样我们就可以单独都对每一位进行相乘计算把结果存入相应的index中
 */
class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = num1.length() - 1, n2 = num2.length() - 1, bitMul;
        if (n1 < 0 || n2 < 0) {
            return "";
        }
        int* mulAnsArr = new int[n1 + n2 + 2]{0};

        string ans = "";

        for (int i = n1; i >= 0; --i) {
            for (int j = n2; j >= 0; --j) {
                bitMul = (int)(num1[i] - '0') * (int)(num2[j] - '0') + mulAnsArr[i + j + 1]; // 先加低位判断是否有新的进位

                mulAnsArr[i + j] += bitMul / 10;
                mulAnsArr[i + j + 1] = bitMul % 10;
            }
        }

        int iterator = 0;
        // 去掉前导0
        while (iterator < n1 + n2 + 1 && mulAnsArr[iterator] == 0) {
            ++iterator;
        }
        for(; iterator < n1 + n2 + 2; ++iterator) {
            ans += '0' + (char)mulAnsArr[iterator];
        }
        delete []mulAnsArr;
        return ans;
    }
};

int main() {
    Solution solution;

    string num1 = "123";
    string num2 = "321";

    cout << num1 << " * " << num2 << " = " << solution.multiply(num1, num2) << endl;

    return 0;
}
