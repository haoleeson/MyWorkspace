//
// Created by eisenhao on 2022/6/24.
//

#include <iostream>
#include <queue>
#include <set>

#include "myTools.h"
using namespace std;

// 动态规划 O(n)
class Solution {
public:
    int minCost(vector<vector<int>>& costs) {
        int len = costs.size();
        if (len < 2) {
            return len == 1 ? min(min(costs[0][0], costs[0][1]), costs[0][2]) : 0;
        }

        // dpTab[3] 表示第 n-1 个房子分别刷成三种颜色的最小累计花销
        int dpTab[3] = {0};
        dpTab[0] = costs[0][0];
        dpTab[1] = costs[0][1];
        dpTab[2] = costs[0][2];

        // curCost 表示当前第 i 个房子分别刷成三种颜色的最小开销
        int curCost[3] = {0};
        for (int i = 1; i < len; ++i) {
            curCost[0] = costs[i][0] + min(dpTab[1], dpTab[2]);
            curCost[1] = costs[i][1] + min(dpTab[0], dpTab[2]);
            curCost[2] = costs[i][2] + min(dpTab[0], dpTab[1]);

            dpTab[0] = curCost[0];
            dpTab[1] = curCost[1];
            dpTab[2] = curCost[2];
        }

        return min(min(curCost[0], curCost[1]), curCost[2]);
    }
};

int main(void) {
    Solution solution;
    int arr1[][3] = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}};
    vector<vector<int>> costs1;
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        costs1.push_back(tmp);
    }
    int res1 = solution.minCost(costs1);
    cout << res1 << endl;

    int arr2[][3] = {{7, 6, 2}};
    vector<vector<int>> costs2;
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        costs2.push_back(tmp);
    }
    int res2 = solution.minCost(costs2);
    cout << res2 << endl;
    return 0;
}
