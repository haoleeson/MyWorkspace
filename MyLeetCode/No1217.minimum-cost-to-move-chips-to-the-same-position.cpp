#include <string.h>

#include <iostream>

#include "myTools.h"

using namespace std;

// 思路：由于移动 2 位无开销，则可将所有奇偶下标位置的筹码先“零开销”移动至 position[0] 和
// position[1]，两者中最小值即为移动最小代价
class Solution {
public:
    int minCostToMoveChips(vector<int>& position) {
        // 统计奇偶下标的筹码和
        int jiSum = 0, ouSum = 0;
        for (int& pos : position) {
            if (pos & 0x01) {
                ++jiSum;
            } else {
                ++ouSum;
            }
        }

        return min(jiSum, ouSum);
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    int arr1[] = {1, 2, 3};
    vector<int> position1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    int res1 = solution.minCostToMoveChips(position1);
    cout << res1 << endl;

    int arr2[] = {2, 2, 2, 3, 3};
    vector<int> position2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    int res2 = solution.minCostToMoveChips(position2);
    cout << res2 << endl;

    int arr3[] = {1, 1000000000};
    vector<int> position3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    int res3 = solution.minCostToMoveChips(position3);
    cout << res3 << endl;

    return 0;
}
