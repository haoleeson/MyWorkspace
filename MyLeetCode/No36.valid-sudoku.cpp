#include <string.h>

#include <iostream>

#include "myTools.h"

using namespace std;

// 判断 行、列、小3x3格 中 1~9 出现的次数，次数超过 1 则无效
// 链接：https://leetcode.cn/problems/valid-sudoku/solution/you-xiao-de-shu-du-by-leetcode-solution-50m6/
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        // 记录 行、列、小3x3格 中 1~9 出现的次数
        int rows[9][9];
        int columns[9][9];
        int subboxes[3][3][9];
        memset(rows, 0, sizeof(rows));
        memset(columns, 0, sizeof(columns));
        memset(subboxes, 0, sizeof(subboxes));

        // 从上至下，从左至右，遍历各点
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char c = board[i][j];
                if (c == '.') {
                    continue;
                }
                int index = c - '1';
                // 统计 行、列、小3x3格 中 1~9 出现的次数
                rows[i][index]++;
                columns[j][index]++;
                subboxes[i / 3][j / 3][index]++;

                // 次数超过 1 ，则无效
                if (rows[i][index] > 1 || columns[j][index] > 1 || subboxes[i / 3][j / 3][index] > 1) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    char arr1[][9] = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                      {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                      {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                      {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    vector<vector<char>> board1;
    for (int i = 0; i < 9; ++i) {
        vector<char> tmp(arr1[i], arr1[i] + 9);
        board1.push_back(tmp);
    }
    bool res1 = solution.isValidSudoku(board1);
    cout << res1 << endl;

    char arr2[][9] = {{'8', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                      {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                      {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                      {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                      {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    vector<vector<char>> board2;
    for (int i = 0; i < 9; ++i) {
        vector<char> tmp(arr2[i], arr2[i] + 9);
        board2.push_back(tmp);
    }
    bool res2 = solution.isValidSudoku(board2);
    cout << res2 << endl;

    return 0;
}
