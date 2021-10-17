#include <iostream>
#include <string>
using namespace std;

/**
 * No60. 第k个排列
 * 给出集合[1,2,3,…,n]，其所有元素共有n! 种排列。

按大小顺序列出所有排列情况，并一一标记，当n = 3 时, 所有排列如下：

"123"
"132"
"213"
"231"
"312"
"321"
给定n 和k，返回第k个排列。

说明：

给定 n的范围是 [1, 9]。
给定 k的范围是[1, n!]。
示例1:

输入: n = 3, k = 3
输出: "213"
示例2:

输入: n = 4, k = 9
输出: "2314"

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutation-sequence
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

class Solution {
public:
    string getPermutation(int n, int k) {
        char charBuf[10]{0};
        string ans(charBuf, 10);
        int factorial[10]{0};
        bool choseFlag[10]{false};
        int order, num, count;
        --k;

//        if (n < 1 || n > 9) {
//            return "invalid Input n, [1,9]";
//        }

        // 计算前n个数的阶乘
        factorial[0] = 1;
        for (int i = 1; i <= n; ++i) {
            factorial[i] = factorial[i - 1] * i;
        }

//        if (k >= factorial[n]) {
//            return "invalid Input k, [1,n!]";
//        }

        // 从左至右，计算输出的排列字符串的每一位
        for (int i = 0; i < n; ++i) {
            order = k / factorial[n - 1 - i];
            // 在剩余未被选择的数字，找到第 order 个
            num = 1;
            count = 0;
            while (num <= n) {
                // 找到下一个未被选中的数字
                while (num <= n && choseFlag[num]) {
                    ++num;
                }
                if (count == order) {
                    break;
                }
                ++num;
                ++count;
            }
            ans[i] = '0' + num;
            choseFlag[num] = true;
            k -= factorial[n - 1 - i] * order;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    cout << solution.getPermutation(4, 9) << endl;
    return 0;
}
