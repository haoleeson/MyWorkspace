#include <iostream>
#include <vector>

using namespace std;

// 思路：动态规划
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        // dpTab[i][j] 表示从 (0,0) 到 (i,j) 的不同路径
        vector<vector<int>> dpTab(m, vector<int>(n, 0));
        dpTab[0][0] = 1;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 若 (i, j) 为障碍物，跳过
                if (obstacleGrid[i][j] == 1) {
                    dpTab[i][j] = 0;
                    continue;
                }

                // 状态方程：路径数 = 到上方相邻坐标路径数 和 到下方相邻坐标路径数 之和
                // dpTab[i][j] = dpTab[i - 1][j] + dpTab[i][j - 1];
                if (i > 0) {
                    dpTab[i][j] += dpTab[i - 1][j];
                }
                if (j > 0) {
                    dpTab[i][j] += dpTab[i][j - 1];
                }
            }
        }

        return dpTab[m - 1][n - 1];
    }
};

int main(void) {
    Solution solution;

    int arr1[][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    vector<vector<int>> obstacleGrid1;
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    for (int i = 0; i < size1; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        obstacleGrid1.push_back(tmp);
    }
    int res1 = solution.uniquePathsWithObstacles(obstacleGrid1);
    cout << res1 << endl;

    int arr2[][2] = {{0, 1}, {0, 0}};
    vector<vector<int>> obstacleGrid2;
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < size2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        obstacleGrid2.push_back(tmp);
    }
    int res2 = solution.uniquePathsWithObstacles(obstacleGrid2);
    cout << res2 << endl;

    int arr3[][4] = {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0}};
    vector<vector<int>> obstacleGrid3;
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    for (int i = 0; i < size3; ++i) {
        vector<int> tmp(arr3[i], arr3[i] + sizeof(arr3[i]) / sizeof(int));
        obstacleGrid3.push_back(tmp);
    }
    int res3 = solution.uniquePathsWithObstacles(obstacleGrid3);
    cout << res3 << endl;

    return 0;
}
