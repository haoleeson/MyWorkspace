#include <iostream>
#include <vector>
using namespace std;
/**
240. 搜索二维矩阵 II
编写一个高效的算法来搜索mxn矩阵 matrix 中的一个目标值 target。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。
示例:

现有矩阵 matrix 如下：

[
  [1,   4,  7, 11, 15],
  [2,   5,  8, 12, 19],
  [3,   6,  9, 16, 22],
  [10, 13, 14, 17, 24],
  [18, 21, 23, 26, 30]
]
给定 target=5，返回true。

给定target=20，返回false。
*/

/**
 * 解题思路：从矩阵的右上角看，可看作二叉搜索树
 */
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty()) {
            return false;
        }
        int m = matrix.size(), n = matrix[0].size(), rowIterator = 0, columnIterator = n - 1;
        while (true) {
            if (rowIterator == m || columnIterator == -1) {
                break;
            }
            if (matrix[rowIterator][columnIterator] < target) {
                ++rowIterator;
            } else if (matrix[rowIterator][columnIterator] > target) {
                --columnIterator;
            } else {
                return true;
            }
        }
        return false;
    }
};

int main() {
    Solution solution;

    vector<vector<int>> matrix;
    int target = 26;
    int a[5][5] = {{1,   4,  7, 11, 15},
                   {2,   5,  8, 12, 19},
                   {3,   6,  9, 16, 22},
                   {10, 13, 14, 17, 24},
                   {18, 21, 23, 26, 30}};



    for (int i = 0; i < 5; ++i) {
        vector<int> tmpVec(a[i], a[i] + 5);
        matrix.push_back(tmpVec);
    }

    cout << solution.searchMatrix(matrix, target) << endl;

    return 0;
}
