#include <iostream>
#include <vector>
using namespace std;

/**
 * No52. N皇后 II （回溯）
 * n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
["Q.......",
"....Q...",
".......Q",
".....Q..",
"..Q.....",
"......Q.",
".Q......",
 "...Q...."]
上图为 8 皇后问题的一种解法。

给定一个整数 n，返回 n 皇后不同的解决方案的数量。

示例:
输入: 4
输出: 2
解释: 4 皇后问题存在如下两个不同的解法。
[
[".Q..", // 解法 1
 "...Q",
 "Q...",
 "..Q."],

["..Q.", // 解法 2
 "Q...",
 "...Q",
 ".Q.."]
]

提示：
皇后，是国际象棋中的棋子，意味着国王的妻子。皇后只做一件事，那就是“吃子”。当她遇见可以吃的棋子时，就迅速冲上去吃掉棋子。当然，她横、竖、斜都可走一或 N-1 步，可进可退。（引用自 百度百科 - 皇后 ）
来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 解题思路：回溯
 */
class Solution {
    int* nQueensIndex;
    // 判断第 i 个皇后是否与前 i-1 个皇后冲突（不能处于同一纵行、斜线）
    bool valid(int i) {
        int val = nQueensIndex[i], l = nQueensIndex[i], r = nQueensIndex[i];
        for (int row = i - 1; row >= 0; --row) {
            // 同一纵行，或斜线冲突
            if (val == nQueensIndex[row] ||
                --l == nQueensIndex[row] || ++r == nQueensIndex[row]) {
                return false;
            }
        }
        return true;
    }
public:
    int totalNQueens(int n) {
        int ans = 0, i = 0;
        nQueensIndex = new int[n]{0};

        // 寻找第 i 个皇后的坐标
        while (true) {
            while (nQueensIndex[i] < n) {
                // 若前i个皇后合法，继续试探下一个皇后坐标
                if (valid(i)) {
                    if (i == n - 1) {
                        ++ans;
                    } else {
                        ++i;
                        break;
                    }
                }
                ++nQueensIndex[i];
            }

            // 无法找到第 i 个皇后的合适坐标，回溯
            if (nQueensIndex[i] == n) {
                if (i == 0) {
                    break;
                }
                // 回溯
                nQueensIndex[i] = 0;
                ++nQueensIndex[i - 1];
                --i;
            }
        }
        delete []nQueensIndex;
        return ans;
    }
};

int main() {
    Solution solution;
    int n = 4;
    cout << solution.totalNQueens(n) << endl;
    return 0;
}