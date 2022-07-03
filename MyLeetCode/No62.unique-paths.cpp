#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        // dpTab[i][j] 表示从 (0,0) 到 (i,j) 的不同路径
        vector<vector<int>> dpTab(m, vector<int>(n, 1));

        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                // 状态方程：路径数 = 到上方相邻坐标路径数 和 到下方相邻坐标路径数 之和
                dpTab[i][j] = dpTab[i - 1][j] + dpTab[i][j - 1];
            }
        }

        return dpTab[m - 1][n - 1];
    }
};

int main(void) {
    Solution solution;
    int m1 = 3;
    int n1 = 7;
    int res1 = solution.uniquePaths(m1, n1);
    cout << res1 << endl;

    int m2 = 3;
    int n2 = 2;
    int res2 = solution.uniquePaths(m2, n2);
    cout << res2 << endl;

    int m3 = 7;
    int n3 = 3;
    int res3 = solution.uniquePaths(m3, n3);
    cout << res3 << endl;

    int m4 = 3;
    int n4 = 3;
    int res4 = solution.uniquePaths(m4, n4);
    cout << res4 << endl;

    return 0;
}
