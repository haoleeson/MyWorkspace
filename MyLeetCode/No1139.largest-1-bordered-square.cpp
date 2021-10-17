#include <iostream>
#include <vector>
using namespace std;
/**
 * No1139. 最大的以 1 为边界的正方形（动态规划）
 * 给你一个由若干 0 和 1 组成的二维网格grid，请你找出边界全部由 1 组成的最大 正方形 子网格，并返回该子网格中的元素数量。如果不存在，则返回 0。

示例 1：
输入：grid = [[1,1,1],
             [1,0,1],
             [1,1,1]]
输出：9

示例 2：
输入：grid = [[1,1,0,0]]
输出：1

提示：
1 <= grid.length <= 100
1 <= grid[0].length <= 100
grid[i][j] 为0或1
*/

class Solution {
public:
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        freshDp(grid);
        int maxLen = min(m, n);// 最大边长，逐渐减小可能边长
        int tryLen = maxLen;

        // 递减试探最大边长为 maxLen 的正方形是否满足边长全为 1
        while (tryLen) {
            for (int i = tryLen - 1; i < m; ++i) {
                for (int j = tryLen - 1; j < n; ++j) {
                    // 验证以(i,j)点为右下角，且边长为tryLen的正方形是否满足边界全为1
                    // 若 下边、右边、上边、左边 任一边连续为1点数小于边长(tryLen)，则重试
                    if (dp_h[i][j] < tryLen || dp_v[i][j] < tryLen ||
                        dp_h[i-tryLen+1][j] < tryLen || dp_v[i][j-tryLen+1] < tryLen) {
                        continue;
                    }
                    return tryLen * tryLen;
                }
            }
            --tryLen;
        }
        return 0;
    }

private:
    int m = 0;
    int n = 0;
    int **dp_h;// dp_h[i][j] 表示(i,j)点左侧连续的1的个数（统计该点）
    int **dp_v;// dp_v[i][j] 表示(i,j)点上侧连续的1的个数（统计该点）
    
    /**
     * 统计数组中每个点的横向和纵向到该点连续为1点数
     * @param grid
     */
    void freshDp(vector<vector<int>>& grid) {
        // 申请二维数组
        dp_h = new int*[m];
        dp_v = new int*[m];
        for (int i = 0; i < m; ++i) {
            dp_h[i] = new int[n]{0};
            dp_v[i] = new int[n]{0};
        }

        // 统计每个点的横向连续为1点数（逐行）
        for (int i = 0; i < m; ++i) {
            dp_h[i][0] = grid[i][0];
            for (int j = 1; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dp_h[i][j] = 1 + dp_h[i][j-1];
                }
            }
        }

        // 统计每个点的纵向连续为1点数（逐列）
        for (int j = 0; j < n; ++j) {
            dp_v[0][j] = grid[0][j];
            for (int i = 1; i < m; ++i) {
                if (grid[i][j] == 1) {
                    dp_v[i][j] = 1 + dp_v[i-1][j];
                }
            }
        }
    }
};

int main() {
    Solution solution;
    vector<vector<int>> grid;
    int array1[3][3] = {{1,1,1},{1,0,1},{1,1,1}};
    for (int i = 0; i < 3; ++i) {
        vector<int> tmpVec(array1[i], array1[i] + 3);
        grid.push_back(tmpVec);
    }
    cout << solution.largest1BorderedSquare(grid) << endl;
    return 0;
}
