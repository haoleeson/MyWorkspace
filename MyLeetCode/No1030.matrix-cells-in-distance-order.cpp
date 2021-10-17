/**
 * No1030. 距离顺序排列矩阵单元格
 * 给出 R 行 C 列的矩阵，其中的单元格的整数坐标为 (r, c)，满足 0 <= r < R 且 0 <= c < C。
 * 另外，我们在该矩阵中给出了一个坐标为 (r0, c0) 的单元格。
 * 返回矩阵中的所有单元格的坐标，并按到 (r0, c0) 的距离从最小到最大的顺序排，其中，两单元格(r1, c1) 和 (r2, c2) 之间的距离是
 * 曼哈顿距离，|r1 - r2| + |c1 - c2|。（你可以按任何满足此条件的顺序返回答案。）

示例 1：
输入：R = 1, C = 2, r0 = 0, c0 = 0
输出：[[0,0],[0,1]]
解释：从 (r0, c0) 到其他单元格的距离为：[0,1]

示例 2：
输入：R = 2, C = 2, r0 = 0, c0 = 1
输出：[[0,1],[0,0],[1,1],[1,0]]
解释：从 (r0, c0) 到其他单元格的距离为：[0,1,1,2]
[[0,1],[1,1],[0,0],[1,0]] 也会被视作正确答案。

示例 3：
输入：R = 2, C = 3, r0 = 1, c0 = 2
输出：[[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
解释：从 (r0, c0) 到其他单元格的距离为：[0,1,1,2,2,3]
其他满足题目要求的答案也会被视为正确，例如 [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]]。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/matrix-cells-in-distance-order
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "myTools.h"
using namespace std;

class Solution {
public:
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        vector<vector<int>> ans(R * C, vector<int>(2, 0));
        int iterator  = 0, dist, maxDist, dR, dC, tmpR, tmpC, maxDiffR, maxDiffC;
        maxDiffR = max(R - r0 - 1, r0);
        maxDiffC = max(C - c0 - 1, c0);
        maxDist = maxDiffR + maxDiffC;

        for (dist = 0; dist <= maxDist; ++dist) {
            for (dR = 0; dR <= min(maxDiffR, dist); ++dR) {
                dC = dist - dR;
                if (dC > maxDiffC) {
                    continue;
                }
                tmpR = r0 + dR;
                tmpC = c0 + dC;
                // try t0 add
                if (tmpR >= 0 && tmpR < R && tmpC >= 0 && tmpC < C) {
                    ans[iterator][0] = tmpR;
                    ans[iterator][1] = tmpC;
                    ++iterator;
                }
                if (dC) {
                    tmpC = c0 - dC;
                    // try to add
                    if (tmpR >= 0 && tmpR < R && tmpC >= 0 && tmpC < C) {
                        ans[iterator][0] = tmpR;
                        ans[iterator][1] = tmpC;
                        ++iterator;
                    }
                }
                if (dR) {
                    tmpR = r0 - dR;
                    tmpC = c0 + dC;
                    // try t0 add
                    if (tmpR >= 0 && tmpR < R && tmpC >= 0 && tmpC < C) {
                        ans[iterator][0] = tmpR;
                        ans[iterator][1] = tmpC;
                        ++iterator;
                    }
                    if (dC) {
                        tmpC = c0 - dC;
                        // try to add
                        if (tmpR >= 0 && tmpR < R && tmpC >= 0 && tmpC < C) {
                            ans[iterator][0] = tmpR;
                            ans[iterator][1] = tmpC;
                            ++iterator;
                        }
                    }
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int arr[3][4] = {
            {1, 2, 0, 0},
            {2, 2, 0, 1},
            {2, 3, 1, 2},
    };
    for (int i = 0; i < 3; ++i) {
        vector<vector<int>> result = solution.allCellsDistOrder(arr[i][0], arr[i][1], arr[i][2], arr[i][3]);
        MyTools::printVec2D(result);
    }
    return 0;
}
