#include <iostream>
#include <vector>
using namespace std;

/**
 * No37. 解数独 (dfs)
 * 编写一个程序，通过已填充的空格来解决数独问题。

一个数独的解法需遵循如下规则：

数字1-9在每一行只能出现一次。
数字1-9在每一列只能出现一次。
数字1-9在每一个以粗实线分隔的3x3宫内只能出现一次。
空白格用'.'表示。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sudoku-solver
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
private:
    bool row[9][9]{false};// line[i][num - 1]记录第i行是否出现数字：num
    bool column[9][9]{false};// column[i][num - 1]记录第i列是否出现数字：num
    bool block[3][3][9]{false};// block[i][j][num - 1]记录第(i,j)个小方块内是否出现数字：num。0 <= i,j <= 2
    vector<pair<int, int>> spaces;// 记录空格位置
    int spacesSize;
    bool finish;
public:
    /**
     * 枚举 + 回溯 试填充每个空格(1~9)
     * @param board
     * @param iterator 记录空格坐标的数组中，第 i 个空格的坐标
     */
    void dfs(vector<vector<char>>& board, int iterator) {
        if (iterator == spacesSize) {
            finish = true;
            return;
        }

        // 取第 i 个空格的坐标: (i, j)
        auto [i, j] = spaces[iterator];
        // 依次遍历1~9，（当全部遍历成功后，后续不需继续遍历了）
        for (int num = 0; num < 9 && !finish; ++num) {
            // 冲突判断
            if (!row[i][num] && !column[j][num] && !block[i/3][j/3][num]) {
                board[i][j] = '1' + num;
                // 刷新标记num
                row[i][num] = true;
                column[j][num] = true;
                block[i / 3][j / 3][num] = true;
                // 继续尝试下一个空格
                dfs(board, iterator + 1);
                // 失败后，回溯到此，取消标记
                row[i][num] = false;
                column[j][num] = false;
                block[i / 3][j / 3][num] = false;
            }
        }
    }

    void solveSudoku(vector<vector<char>>& board) {
        int num;
        finish = false;

        // step1. 遍历棋盘，统计已有数字，记录空白位置
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                // 为空白字符
                if (board[i][j] == '.') {
                    spaces.emplace_back(i, j);
                }
                // 为数字，统计出现情况（标记已出现）
                else {
                    num = board[i][j] - '1';
                    row[i][num] = true;
                    column[j][num] = true;
                    block[i / 3][j / 3][num] = true;
                }
            }
        }
        spacesSize = spaces.size();

        // step2. 枚举 + 回溯 试填充每个空格(1~9)
        dfs(board, 0);
    }
};

template<typename T>
void printVec2D(vector<vector<T>> vec) {
    int size = vec.size();
    cout << "[" << endl;
    if (size > 0) {
        cout << "  [ " << vec[0][0];
        for (int j = 1; j < vec[0].size(); ++j) {
            if (j % 3 == 0) {
                cout << " | " << vec[0][j];
            } else {
                cout << " " << vec[0][j];
            }
        }
        cout << " ]";
        for (int i = 1; i < size; ++i) {
            cout << "," << endl;
            if (i % 3 == 0) {
                cout << "  ";
                for (int j = 0; j < 25; ++j) {
                    cout << "-";
                }
                cout << endl;
            }
            cout << "  [ " << vec[i][0];
            for (int j = 1; j < vec[i].size(); ++j) {
                if (j % 3 == 0) {
                    cout << " | " << vec[i][j];
                } else {
                    cout << " " << vec[i][j];
                }
            }
            cout << " ]";
        }
    }
    cout << endl << "]" << endl;
}

int main() {
    Solution solution;
    char arr2D[9][9] = {{'5','3','.','.','7','.','.','.','.'},
                        {'6','.','.','1','9','5','.','.','.'},
                        {'.','9','8','.','.','.','.','6','.'},
                        {'8','.','.','.','6','.','.','.','3'},
                        {'4','.','.','8','.','3','.','.','1'},
                        {'7','.','.','.','2','.','.','.','6'},
                        {'.','6','.','.','.','.','2','8','.'},
                        {'.','.','.','4','1','9','.','.','5'},
                        {'.','.','.','.','8','.','.','7','9'}};
    vector<vector<char>> board;
    for (int i = 0; i < 9; ++i) {
        vector<char>tmp (arr2D[i], arr2D[i] + 9);
        board.push_back(tmp);
    }
    solution.solveSudoku(board);
    printVec2D(board);
    return 0;
}