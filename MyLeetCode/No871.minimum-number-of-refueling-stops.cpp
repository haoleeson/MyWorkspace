#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 官解：动态规划
// 链接：https://leetcode.cn/problems/minimum-number-of-refueling-stops/solution/zui-di-jia-you-ci-shu-by-leetcode-soluti-nmga/
class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();

        // dpTab[i] 表示加油 i 次的最大行驶英里数
        vector<long> dpTab(n + 1);
        dpTab[0] = startFuel;

        // 遍历每个加油站
        for (int i = 0; i < n; ++i) {
            // 找到能够抵达加油站 stations[i] 的最小加油次数 j，并更新最小加油次数的最大行驶距离 dp[j+1]
            for (int j = i; j >= 0; --j) {
                if (dpTab[j] >= stations[i][0]) {
                    dpTab[j + 1] = max(dpTab[j + 1], dpTab[j] + stations[i][1]);
                }
            }
        }

        // 遍历 dpTab 找到最小加油次数
        for (int i = 0; i <= n; ++i) {
            if (dpTab[i] >= target) {
                return i;
            }
        }

        return -1;
    }
};

// 思路：动态规划 70% 通过
class Solution0 {
public:
    const int CANNOT_ACCESS = -1;
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int size = stations.size();
        if (size == 0) {
            return startFuel >= target ? 0 : CANNOT_ACCESS;
        }

        // 判断能否直接到达终点
        if (startFuel >= target) {
            return 0;
        }

        // dpTab[i] 表示到达加油站 stations[i] 的最少加油次数
        vector<int> dpTab(size, INT_MAX);

        // 到达加油站 stations[i] 时的剩余油量
        vector<int> leafFuel(size, 0);

        // 初始状态值
        for (int j = 0; j < size && stations[j][0] <= startFuel; ++j) {
            dpTab[j] = 0;
            leafFuel[j] = startFuel - stations[j][0];
        }

        // 遍历各加油站
        for (int i = 0; i < size; ++i) {
            // 若中途加油站 stations[i] 不可达，退出
            if (dpTab[i] == INT_MAX) {
                break;
            }

            // 在本站加油后，能行驶到的位置
            int tmpMaxDistance = stations[i][0] + leafFuel[i] + stations[i][1];

            // 判断能否直接到达终点
            if (tmpMaxDistance >= target) {
                return dpTab[i] + 1;
            }

            /* 向后遍历能到达的加油站 */
            for (int j = i + 1; j < size && stations[j][0] <= tmpMaxDistance; ++j) {
                if (dpTab[j] >= dpTab[i] + 1) {
                    dpTab[j] = dpTab[i] + 1;
                    leafFuel[j] = leafFuel[i] + stations[i][1] - (stations[j][0] - stations[i][0]);
                }
            }
        }

        return CANNOT_ACCESS;
    }
};

int main(void) {
    Solution solution1;
    int target1 = 1;
    int startFuel1 = 1;
    vector<vector<int>> stations1;
    int res1 = solution1.minRefuelStops(target1, startFuel1, stations1);
    cout << res1 << endl;

    Solution solution2;
    int target2 = 100;
    int startFuel2 = 1;
    int arr2[][2] = {{10, 100}};
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    vector<vector<int>> stations2(size2, vector<int>(2));
    for (int i = 0; i < size2; ++i) {
        stations2[i][0] = arr2[i][0];
        stations2[i][1] = arr2[i][1];
    }
    int res2 = solution2.minRefuelStops(target2, startFuel2, stations2);
    cout << res2 << endl;

    Solution solution3;
    int target3 = 100;
    int startFuel3 = 10;
    int arr3[][3] = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
    int size3 = sizeof(arr3) / sizeof(arr3[0]);
    vector<vector<int>> stations3(size3, vector<int>(2));
    for (int i = 0; i < size3; ++i) {
        stations3[i][0] = arr3[i][0];
        stations3[i][1] = arr3[i][1];
    }
    int res3 = solution3.minRefuelStops(target3, startFuel3, stations3);
    cout << res3 << endl;

    return 0;
}
