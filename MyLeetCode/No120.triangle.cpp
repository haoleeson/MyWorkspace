#include <iostream>
#include <vector>

using namespace std;

// 思路：动态规划，状态数组压缩
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int lenT = triangle.size();

        // dpTab[j] 表示（压缩成一维的）到达第 i 行第 j 列的最小路径和
        vector<int> dpTab(lenT, INT_MAX);
        dpTab[0] = triangle[0][0];

        for (int i = 1; i < lenT; ++i) {
            // 若非第一列
            for (int j = i; j > 0; --j) {
                // 状态方程: dpTab[i][j] = min(dpTab[i-1][j], dpTab[i-1][j-1]) + triangle[i][j]
                dpTab[j] = min(dpTab[j], dpTab[j - 1]) + triangle[i][j];
            }
            // 若为第一列
            dpTab[0] += triangle[i][0];
        }

        // 找最后一行的最小路径和
        int res = INT_MAX;
        for (int num : dpTab) {
            if (num < res) {
                res = num;
            }
        }

        return res;
    }
};

int main(void) {
    Solution solution;

    int arr1_1[] = {2};
    int arr1_2[] = {3, 4};
    int arr1_3[] = {6, 5, 7};
    int arr1_4[] = {4, 1, 8, 3};
    vector<vector<int>> triangle1;
    triangle1.push_back(vector<int>(arr1_1, arr1_1 + sizeof(arr1_1) / sizeof(int)));
    triangle1.push_back(vector<int>(arr1_2, arr1_2 + sizeof(arr1_2) / sizeof(int)));
    triangle1.push_back(vector<int>(arr1_3, arr1_3 + sizeof(arr1_3) / sizeof(int)));
    triangle1.push_back(vector<int>(arr1_4, arr1_4 + sizeof(arr1_4) / sizeof(int)));
    int res1 = solution.minimumTotal(triangle1);
    cout << res1 << endl;

    int arr2_1[] = {-10};
    vector<vector<int>> triangle2;
    triangle2.push_back(vector<int>(arr2_1, arr2_1 + sizeof(arr2_1) / sizeof(int)));
    int res2 = solution.minimumTotal(triangle2);
    cout << res2 << endl;

    return 0;
}
