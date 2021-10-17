#include <iostream>
#include <vector>
using namespace std;

/**
 * No529. 扫雷游戏
 * 让我们一起来玩扫雷游戏！
 * 给定一个代表游戏板的二维字符矩阵。'M'代表一个未挖出的地雷，'E'代表一个未挖出的空方块，'B'代表没有相邻（上，下，左，右，和所有4个对角线）地雷的已挖出的空白方块，数字（'1' 到 '8'）表示有多少地雷与这块已挖出的方块相邻，'X'则表示一个已挖出的地雷。
 * 现在给出在所有未挖出的方块中（'M'或者'E'）的下一个点击位置（行和列索引），根据以下规则，返回相应位置被点击后对应的面板：
 * 如果一个地雷（'M'）被挖出，游戏就结束了- 把它改为'X'。
 * 如果一个没有相邻地雷的空方块（'E'）被挖出，修改它为（'B'），并且所有和其相邻的未挖出方块都应该被递归地揭露。
 * 如果一个至少与一个地雷相邻的空方块（'E'）被挖出，修改它为数字（'1'到'8'），表示相邻地雷的数量。
 * 如果在此次点击中，若无更多方块可被揭露，则返回面板。

示例 1：
输入:
[['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'M', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E'],
 ['E', 'E', 'E', 'E', 'E']]

Click : [3,0]

输出:
[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

示例 2：
输入:
[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'M', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

Click : [1,2]

输出:
[['B', '1', 'E', '1', 'B'],
 ['B', '1', 'X', '1', 'B'],
 ['B', '1', '1', '1', 'B'],
 ['B', 'B', 'B', 'B', 'B']]

注意：

输入矩阵的宽和高的范围为 [1,50]。
点击的位置只能是未被挖出的方块 ('M' 或者 'E')，这也意味着面板至少包含一个可点击的方块。
输入面板不会是游戏结束的状态（即有地雷已被挖出）。
简单起见，未提及的规则在这个问题中可被忽略。例如，当游戏结束时你不需要挖出所有地雷，考虑所有你可能赢得游戏或标记方块的情况。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minesweeper
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


/**
 * 解题思路：dfs
 */
class Solution {
public:
    // Input
    const char UNDIGGED_MINES = 'M';
    const char UNDIGGED_EMPTY_SQUARE = 'E';
    // Output
    const char DIGGED_MINES = 'X';
    const char markTab[9] = {'B', '1', '2', '3', '4', '5', '6', '7', '8'};
    const int dir_x[8] = {0, 1, 0, -1, 1, 1, -1, -1};
    const int dir_y[8] = {1, 0, -1, 0, 1, -1, 1, -1};
    int m_maxRow = - 1, m_maxColumn =  - 1;

    void dfs(vector<vector<char>>& board, int x, int y) {
        int countMines = 0;
        // 统计方块(x,y)周围的相邻地雷数（只关注地雷'M'）
        for (int i = 0, tmpX, tmpY; i < 8; ++i) {
            tmpX = x + dir_x[i];
            tmpY = y + dir_y[i];
            if (0 > tmpX || tmpX > m_maxRow || 0 > tmpY || tmpY > m_maxColumn ||
                board[tmpX][tmpY] != UNDIGGED_MINES) {
                continue;
            }
            ++countMines;
        }

        // 按相邻地雷数标记方块
        board[x][y] = markTab[countMines];

        // 若相邻地雷数为0，则扩展（只关注未被挖出的空白方块'E'）
        if (countMines == 0) {
            for (int i = 0, tmpX, tmpY; i < 8; ++i) {
                tmpX = x + dir_x[i];
                tmpY = y + dir_y[i];
                if (0 > tmpX || tmpX > m_maxRow || 0 > tmpY || tmpY > m_maxColumn ||
                    board[tmpX][tmpY] != UNDIGGED_EMPTY_SQUARE) {
                    continue;
                }
                dfs(board, tmpX, tmpY);
            }
        }
    }

    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        m_maxRow = board.size() - 1;
        m_maxColumn = board[0].size() - 1;

        // 点击的位置只能是未被挖出的方块 ('M' 或者 'E')，否则，不更新直接返回
        if (click.size() == 2 && 0 <= click[0] && click[0] <= m_maxRow && 0 <= click[1] && click[1] <= m_maxColumn &&
            (board[click[0]][click[1]] == UNDIGGED_MINES || board[click[0]][click[1]] == UNDIGGED_EMPTY_SQUARE)) {
            // 若点击到地雷，改为'X'
            if (board[click[0]][click[1]] == UNDIGGED_MINES) {
                board[click[0]][click[1]] = DIGGED_MINES;
            } else {
                // 点到一个未挖出的空方块
                dfs(board, click[0], click[1]);
            }
        }
        return board;
    }
};

void PrintBoard(vector<vector<char>>& board) {
    int maxRow = board.size();
    int maxColumn = board[0].size();
    for (int i = 0; i < board.size(); ++i) {
        for (int j = 0; j < board[0].size() - 1; ++j) {
            cout << board[i][j] << " ";
        }
        cout << board[i][board[0].size() - 1] << endl;
    }
}

int main() {
    char array2D[4][5] = {  {'E', 'E', 'E', 'E', 'E'},
                            {'E', 'E', 'M', 'E', 'E'},
                            {'E', 'E', 'E', 'E', 'E'},
                            {'E', 'E', 'E', 'E', 'E'}};

    vector<vector<char>> board;
    for (int i = 0; i < 4; ++i) {
        vector<char> tmpVec(array2D[i], array2D[i] + 5);
        board.push_back(tmpVec);
    }

    vector<int> click;
    click.push_back(3);
    click.push_back(0);

    Solution solution;
    vector<vector<char>> result = solution.updateBoard(board, click);
    PrintBoard(result);

    return 0;
}
