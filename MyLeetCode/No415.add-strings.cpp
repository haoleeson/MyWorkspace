#include <iostream>
#include <string>
using namespace std;
/**
415. 字符串相加
给定两个字符串形式的非负整数num1 和num2，计算它们的和。

提示：

num1 和num2的长度都小于 5100
num1 和num2 都只包含数字0-9
num1 和num2 都不包含任何前导零
你不能使用任何內建 BigInteger库，也不能直接将输入的字符串转换为整数形式
*/

class Solution {
public:
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

    string num1 = "999";
    string num2 = "1";

    cout << num1 << " + " << num2 << " = " << solution.addStrings(num1, num2) << endl;

    return 0;
}
