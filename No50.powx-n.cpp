#include <iostream>
using namespace std;

/**
 * No50. Pow(x, n) (快速幂)
 * 实现 pow(x, n)，即计算 x 的 n 次幂函数。

示例 1:
输入: 2.00000, 10
输出: 1024.00000

示例2:
输入: 2.10000, 3
输出: 9.26100

示例3:
输入: 2.00000, -2
输出: 0.25000
解释: 2^-2 = 1/2^2 = 1/4 = 0.25

说明:
-100.0 < x < 100.0
n 是 32 位有符号整数，其数值范围是[−2^31,2^31− 1] 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/powx-n
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 解法2：快速幂 + 迭代
 * O(logN)
 */
class Solution {
public:
    double quickMul(double x, long long N) {
        double ans = 1.0;
        // 贡献的初始值为 x
        double x_contribute = x;
        // 在对 N 进行二进制拆分的同时计算答案
        while (N > 0) {
            if (N % 2 == 1) {
                // 如果 N 二进制表示的最低位为 1，那么需要计入贡献
                ans *= x_contribute;
            }
            // 将贡献不断地平方
            x_contribute *= x_contribute;
            // 舍弃 N 二进制表示的最低位，这样我们每次只要判断最低位即可
            N /= 2;
        }
        return ans;
    }

    double myPow(double x, int n) {
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1.0 / quickMul(x, -N);
    }
};

/**
 * 解法1：快速幂 + 递归
 * O(logN)
 */
class Solution1 {
public:
    double xx;
    /**
     * 快速幂，递归求pow(x, n)
     * @param x
     * @param n 自然数（n : [0, N]）
     * @return
     */
    double rePow(double x, long long n) {
        if (n < 2) {
            return n == 0 ? 1.0 : x;
        }
        xx = rePow(x, n / 2);
        return n % 2 == 0 ? xx * xx : xx * xx * x;
    }
    double myPow(double x, int n) {
        long long N = n;
        return (N < 0) ? 1.0 / rePow(x, -N) : rePow(x, N);
    }
};


int main() {
    Solution solution;
    double x = 2.0;
    int n = 3;
    cout << solution.myPow(x, n) << endl;
    return 0;
}