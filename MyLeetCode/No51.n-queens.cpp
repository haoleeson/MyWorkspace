#include <iostream>
#include <vector>
using namespace std;

/**
 * No51. N 皇后
 * n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 * 给定一个整数 n，返回所有不同的n皇后问题的解决方案。
 * 每一种解法包含一个明确的n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例：
输入：4
输出：
 [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。

提示：
皇后彼此不能相互攻击，也就是说：任何两个皇后都不能处于同一条横行、纵行或斜线上。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/n-queens
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


/**
 * 解题思路：回溯
 */
class Solution {
    int* nQueensIndex;
    // 判断第 i 个皇后是否与前 i-1 个皇后冲突（不能处于同一纵行、斜线）
    bool valid(int i) {
        int val = nQueensIndex[i], l = nQueensIndex[i], r = nQueensIndex[i];
        for (int row = i - 1; row >= 0; --row) {
            // 同一纵行，或斜线冲突
            if (val == nQueensIndex[row] ||
                --l == nQueensIndex[row] || ++r == nQueensIndex[row]) {
                return false;
            }
        }
        return true;
    }
    // 生成皇后棋盘
    vector<string> genStrVec(int* nQueensIndex, int n) {
        vector<string> strVec;
        char* charBuf = new char[n]{0};
        for (int i = 0; i < n; ++i) {
            charBuf[i] = '.';
        }
        string str(charBuf, n);

        for (int i = 0; i < n; ++i) {
            strVec.push_back(str);
            strVec[i][nQueensIndex[i]] = 'Q';
        }
        return strVec;
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        nQueensIndex = new int[n]{0};
        int i = 0;

        // 寻找第 i 个皇后的坐标
        while (true) {

            while (nQueensIndex[i] < n) {
                // 若前i个皇后合法，继续试探下一个皇后坐标
                if (valid(i)) {
                    if (i == n - 1) {
                        ans.push_back(genStrVec(nQueensIndex, n));
                    } else {
                        ++i;
                        break;
                    }
                }
                ++nQueensIndex[i];
            }

            // 无法找到第 i 个皇后的合适坐标，回溯
            if (nQueensIndex[i] == n) {
                if (i == 0) {
                    return ans;
                }
                // 回溯
                nQueensIndex[i] = 0;
                ++nQueensIndex[i - 1];
                --i;
            }
        }
        return ans;
    }
};

void printVec2D(vector<vector<string>>& vec2D) {
    int size = vec2D.size();
    cout << "[" << endl;
    for (int i = 0; i < size; ++i) {
        cout << "[";
        for (int j = 0; j < vec2D[i].size() - 1; ++j) {
            cout << "\"" << vec2D[i][j] << "\"," << endl;
        }
        cout << " \"" << vec2D[i][vec2D[i].size() - 1] << "\"]" << endl << endl;
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    int n = 4;
    vector<vector<string>> result = solution.solveNQueens(n);
    printVec2D(result);
    return 0;
}
