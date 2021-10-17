#include <iostream>
using namespace std;

/**
 * 201. 数字范围按位与
 * 给定范围 [m, n]，其中 0 <= m <= n <= 2147483647，返回此范围内所有数字的按位与（包含 m, n 两端点）。

示例 1:
输入: [5,7]
输出: 4

示例 2:
输入: [0,1]
输出: 0

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/bitwise-and-of-numbers-range
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


class Solution {
    int MAX_INT_BIT = 0x7FFFFFFF;
public:
    int rangeBitwiseAnd(int m, int n) {
        int ans = n & m, diff = n - m, bit = MAX_INT_BIT;
        int i = 0x01;
        while (i <= diff) {
            bit &= ~i;
            if (i != 0x40000000) {
                i <<= 1;
            } else {
                bit = 0x00;
                break;
            }
        }
        return MAX_INT_BIT & bit & ans;
    }
};


/**
 * 力扣大神做法
 * @return
 */
class Solution2 {
public:
    int rangeBitwiseAnd(int m, int n) {
        while (m < n) {  // Remove the last bit 1 until n <= m.
            n &= n - 1;
        }
        return n;
    }
};

int main() {
    Solution solution;
    int m = 5;
    int n = 7;

    cout << solution.rangeBitwiseAnd(m, n) << endl;

    return 0;
}
