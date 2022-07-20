#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();

        // 计算对应初始坐标
        k %= m * n;
        if (k == 0) {
            return grid;
        }
        int x = k / n, y = k % n;

        vector<vector<int>> res(m, vector<int>(n, 0));
        // 遍历腾挪每个元素
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                res[x][y] = grid[i][j];
                // 腾挪网格坐标 +1
                ++y;
                if (y == n) {
                    y = 0;
                    ++x;
                    if (x == m) {
                        x = 0;
                    }
                }
            }
        }

        return res;
    }
};

int main(void) {
    Solution solution;
    int arr1[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int k1 = 1;
    vector<vector<int>> grid1;
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    for (int i = 0; i < size1; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        grid1.push_back(tmp);
    }
    vector<vector<int>> res1 = solution.shiftGrid(grid1, k1);
    MyTools::printVec2D(res1);

    int arr2[][4] = {{3, 8, 1, 9}, {19, 7, 2, 5}, {4, 6, 11, 10}, {12, 0, 21, 13}};
    int k2 = 4;
    vector<vector<int>> grid2;
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < size2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        grid2.push_back(tmp);
    }
    vector<vector<int>> res2 = solution.shiftGrid(grid2, k2);
    MyTools::printVec2D(res2);

    int arr3[][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int k3 = 9;
    vector<vector<int>> grid3;
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    for (int i = 0; i < size3; ++i) {
        vector<int> tmp(arr3[i], arr3[i] + sizeof(arr3[i]) / sizeof(int));
        grid3.push_back(tmp);
    }
    vector<vector<int>> res3 = solution.shiftGrid(grid3, k3);
    MyTools::printVec2D(res3);

    return 0;
}
