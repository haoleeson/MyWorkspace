#include <string.h>

#include <iostream>

#include "myTools.h"

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();

        // 极小值/极大值判断
        if (target <= matrix[0][0] || target >= matrix[m - 1][n - 1]) {
            return (target == matrix[0][0] || target == matrix[m - 1][n - 1]);
        }

        // 先按行二分确定所在行
        int upRow = 0, downRow = m - 1, midRow;
        while (upRow < downRow) {
            midRow = (upRow + downRow) / 2;

            if (target == matrix[midRow][n - 1]) {
                return true;
            } else if (target > matrix[midRow][n - 1]) {
                upRow = midRow + 1;
            } else {
                downRow = midRow;
            }
        }
        int i = downRow;

        // 再对 matri[i] 行，进行按列的二分查找
        int left = 0, right = n - 1, midCol;
        while (left <= right) {
            midCol = (left + right) / 2;

            if (target == matrix[i][midCol]) {
                return true;
            } else if (target > matrix[i][midCol]) {
                left = midCol + 1;
            } else {
                right = midCol - 1;
            }
        }

        return false;
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    int arr1[][4] = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target1 = 3;
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    vector<vector<int>> matrix1;
    for (int i = 0; i < size1; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        matrix1.push_back(tmp);
    }
    bool res1 = solution.searchMatrix(matrix1, target1);
    cout << res1 << endl;

    int arr2[][4] = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
    int target2 = 13;
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    vector<vector<int>> matrix2;
    for (int i = 0; i < size2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        matrix2.push_back(tmp);
    }
    bool res2 = solution.searchMatrix(matrix2, target2);
    cout << res2 << endl;

    int arr3[][4] = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
    int target3 = 10;
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    vector<vector<int>> matrix3;
    for (int i = 0; i < size3; ++i) {
        vector<int> tmp(arr3[i], arr3[i] + sizeof(arr3[i]) / sizeof(int));
        matrix3.push_back(tmp);
    }
    bool res3 = solution.searchMatrix(matrix3, target3);
    cout << res3 << endl;

    return 0;
}
