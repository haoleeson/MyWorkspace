#include <iostream>
using namespace std;

/**
 * No29. 两数相除
 * 给定两个整数，被除数dividend和除数divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。
 * 返回被除数dividend除以除数divisor得到的商。
 * 整数除法的结果应当截去（truncate）其小数部分，例如：truncate(8.345) = 8 以及 truncate(-2.7335) = -2

示例1:
输入: dividend = 10, divisor = 3
输出: 3
解释: 10/3 = truncate(3.33333..) = truncate(3) = 3

示例2:
输入: dividend = 7, divisor = -3
输出: -2
解释: 7/-3 = truncate(-2.33333..) = -2

提示：
被除数和除数均为 32 位有符号整数。
除数不为0。
假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231, 231− 1]。本题中，如果除法结果溢出，则返回 231− 1。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/divide-two-integers
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
class Solution {
public:
//dividend = divisor*2^2 + divisor*2^1 + divisor*2^0
//ans = 2^2 + 2^1 + 2^0
    int divide(int dividend, int divisor) {
        long ans = 0, up = dividend, down = divisor, count, base;
        if (up < 0) {
            up = -up;
        }
        if (down < 0) {
            down = -down;
        }
        while (up >= down) {
            count = 1, base = down;
            while (up > (base << 1)) {
                count <<= 1;
                base <<= 1;
            }
            ans += count;
            up -= base;
        }
        ans = ((dividend < 0) ^ (divisor < 0)) ? -ans : ans;
        return (ans > INT_MAX || ans < INT_MIN) ? INT_MAX : ans;
    }
};

class Solution0 {
public:
    int divide(int dividend, int divisor) {
        bool negFlag1 = false, negFlag2 = false;// 正数 -- false, 负数 -- true
        int ans = 0;

        if (dividend < 0) {
            negFlag1 = true;
            dividend = -dividend;
        }
        if (divisor < 0) {
            negFlag2 = true;
            divisor = -divisor;
        }
        if (dividend < divisor) {
            return 0;
        }

        while (dividend >= divisor) {
            dividend -= divisor;
            ++ans;
        }

        return (negFlag1 ^ negFlag2) ? -ans : ans;
    }
};

int main() {
    Solution solution;
    int dividend = 10;
    int divisor = 3;
    cout << solution.divide(dividend, divisor) << endl;
    return 0;
}