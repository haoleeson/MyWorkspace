#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No59. 螺旋矩阵 II
 * 给定一个正整数 n，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

示例:

输入: 3
输出:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/spiral-matrix-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
    // 定义顺时针螺旋方向（右、下、左、上）
    enum arrow {RIGHT = 0, DOWN = 1, LEFT = 2, UP = 3};
public:
    vector<vector<int>> generateMatrix(int n) {
        if (n < 1) {
            vector<vector<int>> emptyMatrix;
            return emptyMatrix;
        }

        int x = 0, y = -1, arrowIndex = 0, index = 0, row = n, column = n, endVal, totalNum = n * n;
        // initial matrix
        vector<int> tmpRow(n, 0);
        vector<vector<int>> matrix(n, tmpRow);

        while (index < totalNum) {
            switch (arrowIndex % 4) {
                case RIGHT:
                    endVal = column - 1 - (arrowIndex + 1) / 4;
                    while (++y <= endVal) {
                        matrix[x][y] = ++index;
                    }
                    --y;
                    break;
                case DOWN:
                    endVal = row - 1 - (arrowIndex + 1) / 4;
                    while (++x <= endVal) {
                        matrix[x][y] = ++index;
                    }
                    --x;
                    break;
                case LEFT:
                    endVal = 0 + (arrowIndex + 1) / 4;
                    while (--y >= endVal) {
                        matrix[x][y] = ++index;
                    }
                    ++y;
                    break;
                case UP:
                    endVal = 0 + (arrowIndex + 1) / 4;
                    while (--x >= endVal) {
                        matrix[x][y] = ++index;
                    }
                    ++x;
                    break;
                default:
                    break;
            }
            ++arrowIndex;
        }
        return matrix;
    }
};


int main() {
    Solution solution;
    vector<vector<int>> result = solution.generateMatrix(5);
    MyTools::printVec2D(result);
    return 0;
}