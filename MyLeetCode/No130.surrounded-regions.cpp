#include <iostream>

#include "myTools.h"

using namespace std;

// 思路：边界上的'O'不会被包围，深度搜索与边界'O'相连的不会被包围的'O'（标记'A'），其余'O'置'X'
// 链接：https://leetcode.cn/problems/surrounded-regions/solution/bei-wei-rao-de-qu-yu-by-leetcode-solution/
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        n = board.size();
        m = board[0].size();

        // 以上、底边界的'O'为起点，深度搜索标记不被包围的'O'
        for (int i = 0; i < n; i++) {
            if (board[i][0] == 'O') {
                dfs(board, i, 0);
            }
            if (board[i][m - 1] == 'O') {
                dfs(board, i, m - 1);
            }
        }
        // 以左、右边界的'O'为起点，深度搜索标记不被包围的'O'
        for (int i = 1; i < m - 1; i++) {
            if (board[0][i] == 'O') {
                dfs(board, 0, i);
            }
            if (board[n - 1][i] == 'O') {
                dfs(board, n - 1, i);
            }
        }
        // 遍历所有区域，将未被围绕的区域（标记为'A'）恢复成'O'，将其他'O'填充成'X'
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'A') {
                    board[i][j] = 'O';
                } else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }

private:
    int n, m;

    // 深度搜索标记（与边界'O'相连的'O'为'A'）
    void dfs(vector<vector<char>>& board, int x, int y) {
        // 超出范围或不为'O'，退出
        if (x < 0 || x > n - 1 || y < 0 || y > m - 1 || board[x][y] != 'O') {
            return;
        }
        board[x][y] = 'A';
        // 向上下左右四个方向深度搜索标记
        dfs(board, x - 1, y);
        dfs(board, x + 1, y);
        dfs(board, x, y - 1);
        dfs(board, x, y + 1);
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    char arr1[][4] = {{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}};
    vector<vector<char>> board1;
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i) {
        vector<char> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(char));
        board1.push_back(tmp);
    }
    solution.solve(board1);
    MyTools::printVec2D(board1);

    char arr2[][1] = {{'X'}};
    vector<vector<char>> board2;
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i) {
        vector<char> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(char));
        board2.push_back(tmp);
    }
    solution.solve(board2);
    MyTools::printVec2D(board2);

    return 0;
}
