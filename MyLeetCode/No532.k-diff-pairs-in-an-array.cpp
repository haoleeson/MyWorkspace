#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#include "myTools.h"
using namespace std;

class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        int res = 0;
        int len = nums.size();

        vector<int> numsCpy(nums);
        sort(numsCpy.begin(), numsCpy.end());

        set<int> targetNum;

        for (int i = 0; i < len; ++i) {
            // 若 num[i] 是能组成 diff 数对的期望值
            if (targetNum.count(numsCpy[i])) {
                ++res;
                // 跳过后续相同数字
                while (i + 1 < len && numsCpy[i + 1] == numsCpy[i]) {
                    ++i;
                }
            }

            // 添加期望数字
            targetNum.insert(numsCpy[i] + k);
        }

        return res;
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {3, 1, 4, 1, 5};
    int k1 = 2;
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    cout << solution.findPairs(nums1, k1) << endl;

    int arr2[] = {1, 2, 3, 4, 5};
    int k2 = 1;
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    cout << solution.findPairs(nums2, k2) << endl;

    int arr3[] = {1, 3, 1, 5, 4};
    int k3 = 0;
    vector<int> nums3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    cout << solution.findPairs(nums3, k3) << endl;

    return 0;
}
