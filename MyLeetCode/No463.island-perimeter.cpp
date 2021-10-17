/**
 * No463. 岛屿的周长
 * 给定一个包含 0 和 1 的二维网格地图，其中 1 表示陆地 0 表示水域。
 * 网格中的格子水平和垂直方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，
 * 一个或多个表示陆地的格子相连组成的岛屿）。岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。
 * 格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

示例 :
输入:
[[0,1,0,0],
 [1,1,1,0],
 [0,1,0,0],
 [1,1,0,0]]
输出:
16

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/island-perimeter
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

/**
 * 方法2：块数 - 2 * 覆盖边数
 */
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int i, j, row, column, blocks = 0, lines = 0;
        if ((row = grid.size()) == 0 || (column = grid[0].size()) == 0) {
            return 0;
        }
        // 横向
        for (i = 0; i < row; ++i) {
            for (j = 0; j < column; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }
                ++blocks;
                if (j > 0 && grid[i][j - 1] == 1) {
                    ++lines;
                }
            }
        }
        // 纵向
        for (j = 0; j < column; ++j) {
            for (i = 0; i < row; ++i) {
                if (grid[i][j] == 0) {
                    continue;
                }
                if (i > 0 && grid[i - 1][j] == 1) {
                    ++lines;
                }
            }
        }
        return blocks * 4 - lines * 2;
    }
};

/**
 * 方法1：根据领边统计有效边
 */
class Solution1 {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int row, column, ans = 0, i, j, line;
        if ((row = grid.size()) == 0 || (column = grid[0].size()) == 0) {
            return 0;
        }
        for (i = 0; i < row; ++i) {
            for (j = 0; j < column; ++j) {
                if (grid[i][j] == 0) {
                    continue;
                }
                line = 4;
                // 上边是否被覆盖
                if (i > 0 && grid[i - 1][j] == 1) {
                    --line;
                }
                // 下边是否被覆盖
                if (i + 1 < row && grid[i + 1][j] == 1) {
                    --line;
                }
                // 左边是否被覆盖
                if (j > 0 && grid[i][j - 1] == 1) {
                    --line;
                }
                // 右边是否被覆盖
                if (j + 1 < column && grid[i][j + 1] == 1) {
                    --line;
                }
                ans += line;
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int arr[4][4] = {
            {0,1,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {1,1,0,0},
    };
    vector<int> tmp(4, 0);
    vector<vector<int>> grid(4, tmp);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (arr[i][j]) {
                grid[i][j] = 1;
            }
        }
    }
    cout << solution.islandPerimeter(grid) << endl;
    return 0;
}
