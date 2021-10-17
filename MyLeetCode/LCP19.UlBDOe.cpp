#include <iostream>
#include "myTools.h"
using namespace std;

/**
 * LCP 19. 秋叶收藏集 （前缀和 + 动态规划）
 * 小扣出去秋游，途中收集了一些红叶和黄叶，他利用这些叶子初步整理了一份秋叶收藏集 leaves， 字符串 leaves 仅包含小写字符 r 和 y，
 * 其中字符 r 表示一片红叶，字符 y 表示一片黄叶。出于美观整齐的考虑，小扣想要将收藏集中树叶的排列调整成「红、黄、红」三部分。
 * 每部分树叶数量可以不相等，但均需大于等于 1。每次调整操作，小扣可以将一片红叶替换成黄叶或者将一片黄叶替换成红叶。
 * 请问小扣最少需要多少次调整操作才能将秋叶收藏集调整完毕。

示例 1：
输入：leaves = "rrryyyrryyyrr"
输出：2
解释：调整两次，将中间的两片红叶替换成黄叶，得到 "rrryyyyyyyyrr"

示例 2：
输入：leaves = "ryr"
输出：0
解释：已符合要求，不需要额外操作

提示：
3 <= leaves.length <= 10^5
leaves 中只包含字符 'r' 和字符 'y'

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/UlBDOe
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 力扣题解：前缀和 + 动态规划
 * Red: [0,...,x];  Yellow: [x+1,...,y];    Red: [y+1,...,n-1]
 * 累加和：
 *  =  PreY(x)    +     PreR(y) - PreR(x)    +  PreY(n-1) - PreY(y)
 *  =  PreY(n-1) + [PreY(x) - PreR(x)] - [PreY(y) - PreR(y)]
 *      由于：PreY(x) + PreR(x) = 叶子数量 = x + 1
 *      因此有：[PreY(x) - PreR(x)] = PreY(x) - [x + 1 - PreY(x)] = 2 * PreY(x) - (x + 1)
 *      令：[PreY(x) - PreR(x)] = G(x) = 2 * PreY(x) - (x + 1)，
 *      , 有：PreY(x) = [G(x) + (x + 1)] / 2 , G(0) = 2 * isYellow(0) - 1
 *      , 且有递推式：G(x) - G(x - 1) = 2 * isYellow(x) - 1
 *      则累加和可表示为：
 *
 *  =  PreY(n-1) + G(x) - G(y) ,         其中：PreY(n-1)为常数 = [G(n - 1) + n] / 2
 *     由于PreY(n-1)是定值，且有 x < y ，因此可以枚举 y ，并同时记录最小的 G(x)
 *
 * https://leetcode-cn.com/problems/UlBDOe/solution/qiu-xie-shou-cang-ji-by-leetcode-solution/
 */
class Solution {
public:
    int minimumOperations(string leaves) {
        int min_Gx_sub_Gy = INT_MAX, n = leaves.length(), Gy, minGx, tmp;
        minGx = Gy = leaves[0] == 'y' ? 1 : -1;// G(0) = 2 * isYellow(0) - 1
        
        // 枚举 y 下标 : [1, n-1)，先求 min( minG(x) - G(y) )
        for (int y = 1; y < n - 1; ++y) {
            // 递推式 G[i] - G[i - 1] = 2 * isYellow(i) - 1 = isYellow(i) ? 1 : -1
            Gy += leaves[y] == 'y' ? 1 : -1;
            tmp = minGx - Gy;// minG(x) - G(y)
            if (tmp < min_Gx_sub_Gy) {
                min_Gx_sub_Gy = tmp;
            }
            if (Gy < minGx) {
                minGx = Gy;
            }
        }
        // 计算 G(n - 1)
        Gy += (leaves[n - 1] == 'y') ? 1 : -1;
        return min_Gx_sub_Gy + (Gy + n) / 2;// 再加 PreY(n-1)定值 = [G(n - 1) + n] / 2
    }
};

int main() {
    Solution solution;
    string leaves = "rrryyyrryyyrr";
    cout << solution.minimumOperations(leaves) << endl;
    return 0;
}