#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// 思路：单调栈
// 链接：https://leetcode.cn/problems/maximal-rectangle/solution/zui-da-ju-xing-by-leetcode-solution-bjlu/
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        vector<vector<int>> left(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
                }
            }
        }

        int ret = 0;
        for (int j = 0; j < n; j++) { // 对于每一列，使用基于柱状图的方法
            vector<int> up(m, 0), down(m, 0);

            stack<int> stk;
            for (int i = 0; i < m; i++) {
                while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
                    stk.pop();
                }
                up[i] = stk.empty() ? -1 : stk.top();
                stk.push(i);
            }
            stk = stack<int>();
            for (int i = m - 1; i >= 0; i--) {
                while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
                    stk.pop();
                }
                down[i] = stk.empty() ? m : stk.top();
                stk.push(i);
            }

            for (int i = 0; i < m; i++) {
                int height = down[i] - up[i] - 1;
                int area = height * left[i][j];
                ret = max(ret, area);
            }
        }
        return ret;
    }
};

// 思路：使用柱状图的优化暴力方法
// 链接：https://leetcode.cn/problems/maximal-rectangle/solution/zui-da-ju-xing-by-leetcode-solution-bjlu/
class Solution1 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int m = matrix.size();
        if (m == 0) {
            return 0;
        }
        int n = matrix[0].size();
        vector<vector<int>> left(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '1') {
                    left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
                }
            }
        }

        int ret = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == '0') {
                    continue;
                }
                int width = left[i][j];
                int area = width;
                for (int k = i - 1; k >= 0; k--) {
                    width = min(width, left[k][j]);
                    area = max(area, (i - k + 1) * width);
                }
                ret = max(ret, area);
            }
        }
        return ret;
    }
};

// 思路：动态规划 O（N ^ 3)
class Solution0 {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int lenRow = matrix.size(), lenCol = matrix[0].size();
        int maxArea = 0, tmpArea;

        // 定义 dpTab[i][j][0], dpTab[i][j][1] 分别表示以 (i,j) 坐标结尾的点，其横向/纵向最大连续'1'数量
        vector<vector<vector<int>>> dpTab(lenRow, vector<vector<int>>(lenCol, vector<int>(2, 0)));
        if (matrix[0][0] == '1') {
            dpTab[0][0][0] = 1, dpTab[0][0][1] = 1;
        }

        for (int i = 0; i < lenRow; ++i) {
            for (int j = 0; j < lenCol; ++j) {
                // 统计点 (i, j) 的横向最大连续'1'数量
                if (j == 0) {
                    dpTab[i][j][0] = (matrix[i][j] == '1') ? 1 : 0;
                } else {
                    dpTab[i][j][0] = (matrix[i][j] == '1') ? dpTab[i][j - 1][0] + 1 : 0;
                }

                // 统计点 (i, j) 的纵向最大连续'1'数量
                if (i == 0) {
                    dpTab[i][j][1] = (matrix[i][j] == '1') ? 1 : 0;
                } else {
                    dpTab[i][j][1] = (matrix[i][j] == '1') ? dpTab[i - 1][j][0] + 1 : 0;
                }

                // 从 (i, j) 向左 横向遍历连续 n 个列，找到各自的最大面积
                int n = dpTab[i][j][0];
                for (int k = j, minZong = INT_MAX; k > j - n; --k) {
                    if (dpTab[i][k][1] < minZong) {
                        minZong = dpTab[i][k][1];
                    }
                    // 可组成的矩形面积： 列宽 * 最小高度
                    tmpArea = (j - k + 1) * minZong;
                    if (tmpArea > maxArea) {
                        maxArea = tmpArea;
                    }
                }
            }
        }

        return maxArea;
    }
};

int main(void) {
    Solution solution;

    char arr1[][5] = {
        {'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
    vector<vector<char>> matrix1;
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i) {
        vector<char> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(char));
        matrix1.push_back(tmp);
    }
    int res1 = solution.maximalRectangle(matrix1);
    cout << res1 << endl;

    char arr2[][1] = {{'0'}};
    vector<vector<char>> matrix2;
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i) {
        vector<char> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(char));
        matrix2.push_back(tmp);
    }
    int res2 = solution.maximalRectangle(matrix2);
    cout << res2 << endl;

    char arr3[][2] = {{'0', '1'}};
    vector<vector<char>> matrix3;
    for (int i = 0; i < sizeof(arr3) / sizeof(arr3[0]); ++i) {
        vector<char> tmp(arr3[i], arr3[i] + sizeof(arr3[i]) / sizeof(char));
        matrix3.push_back(tmp);
    }
    int res3 = solution.maximalRectangle(matrix3);
    cout << res3 << endl;

    return 0;
}
