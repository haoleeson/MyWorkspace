#include <iostream>
#include <vector>
using namespace std;

/**
 * No79. 单词搜索 （dfs）
 * 给定一个二维网格和一个单词，找出该单词是否存在于网格中。
 * 单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
 * 同一个单元格内的字母不允许被重复使用。

示例:
board =
[
  ['A','B','C','E'],
  ['S','F','C','S'],
  ['A','D','E','E']
]

给定 word = "ABCCED", 返回 true
给定 word = "SEE", 返回 true
给定 word = "ABCB", 返回 false

提示：
board 和 word 中只包含大写和小写英文字母。
1 <= board.length <= 200
1 <= board[i].length <= 200
1 <= word.length <= 10^3

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-search
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
class Solution {
public:
    int m_direction[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};// 上下左右
    int m_row, m_column, m_len;
    bool m_flag[201][201] = {false};

    bool dfs(vector<vector<char>>& board, string& word, int x, int y, int iterator) {
        if (iterator == m_len) {
            return true;
        }
        int tmpX, tmpY;
        // 四个方向试探
        for (int i = 0; i < 4; ++i) {
            tmpX = m_direction[i][0] + x;
            tmpY = m_direction[i][1] + y;
            // 坐标合法性判断、字符判等，则继续下探
            if (0 <= tmpX && tmpX < m_row && 0 <= tmpY && tmpY < m_column && !m_flag[tmpX][tmpY] && board[tmpX][tmpY] == word[iterator]) {
                m_flag[tmpX][tmpY] = true;
                if(dfs(board, word, tmpX, tmpY, iterator + 1)) {
                    return true;
                }
                m_flag[tmpX][tmpY] = false;
            }
        }
        return false;
    }

    bool exist(vector<vector<char>>& board, string word) {
        bool result = false;
        m_row = board.size();
        m_column = board[0].size();
        m_len = word.length();

        for (int i = 0; i < m_row; ++i) {
            for (int j = 0; j < m_column; ++j) {
                // 找到起始坐标
                if (board[i][j] == word[0]) {
                    m_flag[i][j] = true;
                    if (dfs(board, word, i, j, 1)) {
                        return true;
                    }
                    m_flag[i][j] = false;
                }
            }
        }
        return false;
    }
};

int main() {
    Solution solution;
    char arr1[] = {'A','B','C','E'};
    char arr2[] = {'S','F','C','S'};
    char arr3[] = {'A','D','E','E'};
    vector<vector<char>> board;
    vector<char> tmp1(arr1, arr1 + sizeof(arr1)/sizeof(char));
    board.push_back(tmp1);
    vector<char> tmp2(arr2, arr2 + sizeof(arr2)/sizeof(char));
    board.push_back(tmp2);
    vector<char> tmp3(arr3, arr3 + sizeof(arr3)/sizeof(char));
    board.push_back(tmp3);
    string word = "ABCCED";
    cout << solution.exist(board, word) << endl;
    return 0;
}