/**
 * No402. 移掉 K 位数字（贪心 + 单调栈）
 * 给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。

注意:
num 的长度小于 10002 且 ≥ k。
num 不会包含任何前导零。

示例 1 :
输入: num = "1432219", k = 3
输出: "1219"
解释: 移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219。

示例 2 ：
输入: num = "10200", k = 1
输出: "200"
解释: 移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。

示例 3 :
输入: num = "10", k = 2
输出: "0"
解释: 从原数字移除所有的数字，剩余为空就是0。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-k-digits
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <string>
using namespace std;

/**
 * 分析：移除最大的数字（贪心 + 单调栈）
 */
class Solution {
public:
    string removeKdigits(string num, int k) {
        int len = num.length(), iterator = -1, i = -1;
        if (k >= len) {
            return "0";
        }
        if (k <= 0) {
            return k == 0 ? num : "0";
        }
        char* stack = new char[len]{0};
        // 维护单调栈（递增）
        for (char digit: num) {
            // 若前面数字（栈顶）大于当前数，则弹出（栈顶）
            while (iterator > -1 && stack[iterator] > digit && k) {
                --iterator;
                --k;
            }
            // 入栈当前数
            stack[++iterator] = digit;
        }
        // 若还有 k (k > 0)，则依次弹出k个（栈顶）较大的数
        while (k--) {
            --iterator;
        }
        // 删除前导0
        while (++i <= iterator && stack[i] == '0');
        if (i > iterator) {
            return "0";
        }
        string ans(stack + i, iterator - i + 1);
        delete []stack;
        return ans;
    }
};

int main() {
    Solution solution;
    string nums[] = {
            "12345264",
            "1432219",
            "10200",
            "10"
    };
    int K[] = {4, 3, 1, 2};
    for (int i = 0; i < 4; ++i) {
        cout << solution.removeKdigits(nums[i], K[i]) << endl;
    }
    return 0;
}
