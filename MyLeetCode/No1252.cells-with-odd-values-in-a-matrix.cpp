#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int oddCells(int m, int n, vector<vector<int>>& indices) {
        vector<int> rowCnt(m, 0);
        vector<int> colCnt(n, 0);

        // 统计各行、各列增加次数
        for (vector<int>& v : indices) {
            rowCnt[v[0]]++;
            colCnt[v[1]]++;
        }

        // 统计各行、各列增量的 奇偶状态
        vector<bool> rowJiStat(m, false);
        vector<bool> colJiStat(n, false);
        for (int i = 0; i < m; ++i) {
            if (rowCnt[i] & 0x01) {
                rowJiStat[i] = true;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (colCnt[j] & 0x01) {
                colJiStat[j] = true;
            }
        }

        // 统计各坐标值中奇数单元格数目 arr[i][j] = rowCnt[i] + colCnt[j]
        int cntJi = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 行为奇列为偶、行为偶列为奇，则次单元格为奇数
                if (rowJiStat[i] != colJiStat[j]) {
                    ++cntJi;
                }
            }
        }

        return cntJi;
    }
};

int main(void) {
    Solution solution;
    int m1 = 2;
    int n1 = 3;
    int arr1[][2] = {{0, 1}, {1, 1}};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    vector<vector<int>> indices1;
    for (int i = 0; i < len1; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        indices1.push_back(tmp);
    }
    int res1 = solution.oddCells(m1, n1, indices1);
    cout << res1 << endl;

    int m2 = 2;
    int n2 = 2;
    int arr2[][2] = {{1, 1}, {0, 0}};
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
    vector<vector<int>> indices2;
    for (int i = 0; i < len2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        indices2.push_back(tmp);
    }
    int res2 = solution.oddCells(m2, n2, indices2);
    cout << res2 << endl;

    return 0;
}
