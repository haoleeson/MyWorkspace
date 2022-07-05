#include <string.h>

#include <functional>
#include <iostream>
#include <vector>

using namespace std;

// 官解：带备忘录的深度优先搜索  O(MN)
class Solution {
    const int MOD = 1e9 + 7;
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

public:
    int countPaths(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // 定义笔记本：f[i][j] 表示以 (i,j) 结尾的路径数
        //        int f[m][n];
        //        memset(f, -1, sizeof(f));
        vector<vector<int>> f(m, vector<int>(n, -1));

        function<int(int, int)> dfs = [&](int i, int j) -> int {
            // 如果已计算（记忆），直接返回值
            if (f[i][j] != -1) {
                return f[i][j];
            }

            int res = 1;
            // 遍历上下左右 4 个方向中数字大于本格子(i,j)的方向
            for (auto& d : dirs) {
                int x = i + d[0], y = j + d[1];
                if (0 <= x && x < m && 0 <= y && y < n && grid[x][y] > grid[i][j]) {
                    res = (res + (dfs(x, y))) % MOD;
                }
            }
            return f[i][j] = res;
        };

        // 遍历计算以每个格子为终点的所有路径
        int ans = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                ans = (ans + dfs(i, j)) % MOD;
            }
        }
        return ans;
    }
};

// 思路：动态规划，用例未全通过 16/36  O(MN)
class Solution1 {
    const int MOD = 1e9 + 7;

public:
    int countPaths(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        int res = 0;

        // dpTab[i][j] 表示以坐标 (i,j) 结尾的的严格递增的路径数
        vector<vector<long>> dpTab(m, vector<long>(n, 1));

        // 统计 上，左 方向严格递增路径数
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 上方相邻格子的数字小于 (i,j)
                if (i > 0 && grid[i - 1][j] < grid[i][j]) {
                    dpTab[i][j] = (dpTab[i][j] + dpTab[i - 1][j]) % MOD;
                }
                // 左方相邻格子的数字小于 (i,j)
                if (j > 0 && grid[i][j - 1] < grid[i][j]) {
                    dpTab[i][j] = (dpTab[i][j] + dpTab[i][j - 1]) % MOD;
                }
            }
        }

        // 统计 下，右 方向严格递增路径数
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                // 下方相邻格子的数字小于 (i,j)
                if (i + 1 < m && grid[i + 1][j] < grid[i][j]) {
                    dpTab[i][j] = (dpTab[i][j] + dpTab[i + 1][j]) % MOD;
                }
                // 右方相邻格子的数字小于 (i,j)
                if (j + 1 < n && grid[i][j + 1] < grid[i][j]) {
                    dpTab[i][j] = (dpTab[i][j] + dpTab[i][j + 1]) % MOD;
                }
            }
        }

        // 路径汇总
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res = (res + dpTab[i][j]) % MOD;
            }
        }
        return res;
    }
};

int main(void) {
    Solution solution;
    int arr1[][2]{{1, 1}, {3, 4}};
    vector<vector<int>> grid1(sizeof(arr1) / sizeof(arr1[0]), vector<int>(sizeof(arr1[0]) / sizeof(int)));
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i) {
        for (int j = 0; j < sizeof(arr1[0]) / sizeof(int); ++j) {
            grid1[i][j] = arr1[i][j];
        }
    }
    int res1 = solution.countPaths(grid1);
    cout << res1 << endl;

    int arr2[][1]{{1}, {2}};
    vector<vector<int>> grid2(sizeof(arr2) / sizeof(arr2[0]), vector<int>(sizeof(arr2[0]) / sizeof(int)));
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i) {
        for (int j = 0; j < sizeof(arr2[0]) / sizeof(int); ++j) {
            grid2[i][j] = arr2[i][j];
        }
    }
    int res2 = solution.countPaths(grid2);
    cout << res2 << endl;

    return 0;
}
