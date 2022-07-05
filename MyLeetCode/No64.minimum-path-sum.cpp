#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        // dpTab[i][j] 表示从左上角到坐标 (i,j) 的所有路径的最小数字总和
        vector<vector<long long int>> dpTab(m, vector<long long int>(n, 0));
        // 初值：第一列与第一行（只有一个方向，路径和为累加和）
        dpTab[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i) {
            dpTab[i][0] = dpTab[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < n; ++j) {
            dpTab[0][j] = dpTab[0][j - 1] + grid[0][j];
        }

        // 从上至下，从左至右遍历其余坐标
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dpTab[i][j] = grid[i][j] + min(dpTab[i - 1][j], dpTab[i][j - 1]);
            }
        }

        return dpTab[m - 1][n - 1];
    }
};

int main(void) {
    Solution solution;
    int arr1[][3] = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    vector<vector<int>> grid1;
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    for (int i = 0; i < size1; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        grid1.push_back(tmp);
    }
    int res1 = solution.minPathSum(grid1);
    cout << res1 << endl;

    int arr2[][3] = {{1, 2, 3}, {4, 5, 6}};
    vector<vector<int>> grid2;
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < size2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        grid2.push_back(tmp);
    }
    int res2 = solution.minPathSum(grid2);
    cout << res2 << endl;

    return 0;
}
