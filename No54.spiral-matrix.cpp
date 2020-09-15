#include <iostream>
#include <vector>
using namespace std;

/**
 * No54. 螺旋矩阵
 * 给定一个包含m x n个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

示例1:
输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]

示例2:
输入:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
输出: [1,2,3,4,8,12,11,10,9,5,6,7]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/spiral-matrix
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
    // 定义顺时针螺旋方向（右、下、左、上）
    enum arrow {RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3};
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ans;
        int x = 0, y = -1, iterator = 0, row, column, endVal, totalNum;
        if ( (row = matrix.size()) == 0 || (column = matrix[0].size()) == 0 ) {
            return ans;
        }
        totalNum = row * column;
        while (ans.size() < totalNum) {
            switch (iterator % 4) {
                case RIGHT:
                    endVal = column - 1 - (iterator + 1) / 4;
                    while (++y <= endVal) {
                        ans.push_back(matrix[x][y]);
                    }
                    --y;
                    break;
                case DOWN:
                    endVal = row - 1 - (iterator + 1) / 4;
                    while (++x <= endVal) {
                        ans.push_back(matrix[x][y]);
                    }
                    --x;
                    break;
                case LEFT:
                    endVal = 0 + (iterator + 1) / 4;
                    while (--y >= endVal) {
                        ans.push_back(matrix[x][y]);
                    }
                    ++y;
                    break;
                case UP:
                    endVal = 0 + (iterator + 1) / 4;
                    while (--x >= endVal) {
                        ans.push_back(matrix[x][y]);
                    }
                    ++x;
                    break;
                default:
                    break;
            }
            ++iterator;
        }
        return ans;
    }
};

template<typename T>
void printVec(vector<T> vec) {
    int size = vec.size();
    cout << "[";
    if (size > 0) {
        cout << vec[0];
        for (int i = 1; i < size; ++i) {
            cout << ", " << vec[i];
        }
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    int arr2D[3][4] = {{1, 2, 3, 4},
                       {5, 6, 7, 8},
                       {9,10,11,12}};
    vector<vector<int>> matrix;
    for (int i = 0; i < 3; ++i) {
        vector<int>tmp (arr2D[i], arr2D[i] + 4);
        matrix.push_back(tmp);
    }

    vector<int> result = solution.spiralOrder(matrix);
    printVec(result);
    return 0;
}