#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 思路：用第一行(和第一列)元素存储各列(和各行)是否有 0 元素；再用两个变量记录 第一行（和第一列）是否有 0 元素
// 链接：https://leetcode.cn/problems/set-matrix-zeroes/solution/o1kong-jian-by-powcai/
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int row = matrix.size(), col = matrix[0].size();

        // 判断第一行(和第一列)是否有 0
        bool first_row_has_zero = false, first_col_has_zero = false;
        for (int j = 0; j < col; ++j) {
            if (matrix[0][j] == 0) {
                first_row_has_zero = true;
                break;
            }
        }
        for (int i = 0; i < row; ++i) {
            if (matrix[i][0] == 0) {
                first_col_has_zero = true;
                break;
            }
        }

        // 第一次遍历全矩阵，记录含有 0 的 行和列（记录到第一列和第一行）
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = matrix[0][j] = 0;
                }
            }
        }

        // 第二次遍历全矩阵，置0
        for (int i = 1; i < row; ++i) {
            for (int j = 1; j < col; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 再单独根据第一行第一列有无 0，选择是否置零第一行或第一列
        if (first_row_has_zero) {
            for (int j = 0; j < col; ++j) {
                matrix[0][j] = 0;
            }
        }
        if (first_col_has_zero) {
            for (int i = 0; i < row; ++i) {
                matrix[i][0] = 0;
            }
        }
    }
};

int main(void) {
    Solution solution;

    int arr1[][3] = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
    vector<vector<int>> matrix1;
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    for (int i = 0; i < size1; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        matrix1.push_back(tmp);
    }
    solution.setZeroes(matrix1);
    MyTools::printVec2D(matrix1);

    int arr2[][4] = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
    vector<vector<int>> matrix2;
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    for (int i = 0; i < size2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        matrix2.push_back(tmp);
    }
    solution.setZeroes(matrix2);
    MyTools::printVec2D(matrix2);

    return 0;
}
