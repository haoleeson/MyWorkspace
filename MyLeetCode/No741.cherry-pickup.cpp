#include <iostream>
#include <vector>

using namespace std;

// 思路：线性 Dp， 两个点从左上角开始同时走（每个位置的只能得分一次），最终都走到右下角的最大得分
// 链接：https://leetcode.cn/problems/cherry-pickup/solution/by-ac_oier-pz7i/
class Solution {
    const int INF = INT_MIN; // 最小值
    const int BAULK = -1;    // 荆棘
public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();

        // 定义 f[k][i1][i2] 为当前走了 k 步（横纵坐标之和），且第一个点当前在第 i1 行，第二点在第 i2
        // 行时的最大得分，最终答案为 f[2n][n][n]
        vector<vector<vector<int>>> f(2 * n + 1, vector<vector<int>>(n + 1, vector<int>(n + 1, INF)));
        // 初始值，实际坐标值放大 1
        f[2][1][1] = grid[0][0];

        // 模拟两个点 (i1, j1), (i2, j2) 同时从左上往右下走
        for (int k = 3; k <= 2 * n; ++k) {
            for (int i1 = 1; i1 <= n; ++i1) {
                for (int i2 = 1; i2 <= n; ++i2) {
                    // 根据假设两个点都走了 k 步，可分别根据行数坐标计算列坐标
                    int j1 = k - i1, j2 = k - i2;
                    // 合法性校验
                    if (j1 <= 0 || j1 > n || j2 <= 0 || j2 > n) continue;
                    // 取两个点的值
                    int A = grid[i1 - 1][j1 - 1], B = grid[i2 - 1][j2 - 1];

                    // 若两点均为荆棘，跳过
                    if (A == BAULK || B == BAULK) continue;
                    // A, B 两点各自向下、向右走一步 的最大值
                    int a = f[k - 1][i1 - 1][i2], b = f[k - 1][i1 - 1][i2 - 1], c = f[k - 1][i1][i2 - 1],
                        d = f[k - 1][i1][i2];
                    int t = max(max(a, b), max(c, d)) + A;
                    // 若 A，B 点不重合，加上 B 点的值，否则“只计算一次”
                    if (i1 != i2) t += B;
                    f[k][i1][i2] = t;
                }
            }
        }

        // 不可达 -- 返回0； 可达 -- 返回最大樱桃数
        return f[2 * n][n][n] <= 0 ? 0 : f[2 * n][n][n];
    }
};

// 正反遍历 + 动态规划（通过测试用例：49 / 59）
class Solution0 {
    const int BAULK = -1;     // 荆棘
    const int EMPTY = 0;      // 空地
    const int HAS_CHERRY = 1; // 有樱桃
    struct Position {
        int x;
        int y;
        Position() {}
        Position(int _x, int _y) : x(_x), y(_y) {}
        bool isHeadPos() { return x == 0 && y == 0; }
        Position& operator=(const Position& b) {
            this->x = b.x;
            this->y = b.y;
            return *this;
        }
    };

public:
    int cherryPickup(vector<vector<int>>& grid) {
        int n = grid.size();

        if (n == 1) {
            return grid[0][0] == HAS_CHERRY ? 1 : 0;
        }

        // dpTab[i][j] 表示从 (0,0) 到达 (i,j) 的采摘樱桃最大值
        vector<vector<int>> dpTab(n, vector<int>(n, -1));
        dpTab[0][0] = grid[0][0] == HAS_CHERRY ? 1 : 0;
        // path[i][j] 记录了到达 (i,j) 坐标的上一坐标
        vector<vector<Position>> path(n, vector<Position>(n));

        // 第一行
        for (int j = 1; j < n; ++j) {
            if (grid[0][j] == BAULK) {
                break;
            }
            dpTab[0][j] = dpTab[0][j - 1] + (grid[0][j] == HAS_CHERRY ? 1 : 0);
            path[0][j] = Position(0, j - 1);
        }
        // 第一列
        for (int i = 1; i < n; ++i) {
            if (grid[i][0] == BAULK) {
                break;
            }
            dpTab[i][0] = dpTab[i - 1][0] + (grid[i][0] == HAS_CHERRY ? 1 : 0);
            path[i][0] = Position(i - 1, 0);
        }

        // 从上至下，从左至右 遍历
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j < n; ++j) {
                if (grid[i][j] == BAULK) {
                    dpTab[i][j] = -1;
                    continue;
                }

                // 不可达
                if (dpTab[i - 1][j] == -1 && dpTab[i][j - 1] == -1) {
                    continue;
                }

                if (dpTab[i - 1][j] > dpTab[i][j - 1]) {
                    dpTab[i][j] = dpTab[i - 1][j] + (grid[i][j] == HAS_CHERRY ? 1 : 0);
                    path[i][j] = Position(i - 1, j);
                } else {
                    dpTab[i][j] = dpTab[i][j - 1] + (grid[i][j] == HAS_CHERRY ? 1 : 0);
                    path[i][j] = Position(i, j - 1);
                }
            }
        }

        // 若 (n-1,n-1) 不可达，返回 0
        if (dpTab[n - 1][n - 1] == -1) {
            return 0;
        }

        // 逆向遍历路径，更新格子樱桃数（将经过的非零网格置零）
        grid[n - 1][n - 1] = 0;
        grid[0][0] = 0;
        Position tmp = path[n - 1][n - 1];
        while (!tmp.isHeadPos()) {
            grid[tmp.x][tmp.y] = 0;
            tmp = path[tmp.x][tmp.y];
        }

        // 逆向遍历
        vector<vector<int>> dpTab2(n, vector<int>(n, -1));
        dpTab2[n - 1][n - 1] = 0;
        // 第 n-1 行
        for (int j = n - 2; j > -1; --j) {
            if (grid[n - 1][j] == BAULK) {
                break;
            }
            dpTab2[n - 1][j] = dpTab2[n - 1][j + 1] + (grid[n - 1][j] == HAS_CHERRY ? 1 : 0);
        }
        // 第 n-1 列
        for (int i = n - 2; i > -1; --i) {
            if (grid[i][n - 1] == BAULK) {
                break;
            }
            dpTab2[i][n - 1] = dpTab2[i + 1][n - 1] + (grid[i][n - 1] == HAS_CHERRY ? 1 : 0);
        }

        // 从下至上，从右至左 遍历
        for (int i = n - 2; i > -1; --i) {
            for (int j = n - 2; j > -1; --j) {
                if (grid[i][j] == BAULK) {
                    dpTab2[i][j] = -1;
                    continue;
                }

                // 不可达
                if (dpTab2[i + 1][j] == -1 && dpTab2[i][j + 1] == -1) {
                    continue;
                }

                dpTab2[i][j] = max(dpTab2[i + 1][j], dpTab2[i][j + 1]) + (grid[i][j] == HAS_CHERRY ? 1 : 0);
            }
        }

        return dpTab[n - 1][n - 1] + dpTab2[0][0];
    }
};

int main(void) {
    Solution solution;

    int arr1[][3]{{0, 1, -1}, {1, 0, -1}, {1, 1, 1}};
    vector<vector<int>> grid1;
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        grid1.push_back(tmp);
    }
    int res1 = solution.cherryPickup(grid1);
    cout << res1 << endl;

    int arr2[][1]{{1}};
    vector<vector<int>> grid2;
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        grid2.push_back(tmp);
    }
    int res2 = solution.cherryPickup(grid2);
    cout << res2 << endl;

    int arr3[][2]{{1, 1}, {-1, 1}};
    vector<vector<int>> grid3;
    for (int i = 0; i < sizeof(arr3) / sizeof(arr3[0]); ++i) {
        vector<int> tmp(arr3[i], arr3[i] + sizeof(arr3[i]) / sizeof(int));
        grid3.push_back(tmp);
    }
    int res3 = solution.cherryPickup(grid3);
    cout << res3 << endl;

    return 0;
}
