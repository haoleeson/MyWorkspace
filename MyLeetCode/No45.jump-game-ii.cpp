#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int lenN = nums.size();

        // dpTab[i] 表示跳到 nums[i] 的最小次数（初始值为0）
        int* dpTab = new int[lenN]{0};

        for (int i = 0; i < lenN - 1; ++i) {
            for (int j = i + 1; j <= min(i + nums[i], lenN - 1); ++j) {
                if (dpTab[j] == 0) {
                    dpTab[j] = dpTab[i] + 1;
                } else {
                    dpTab[j] = min(dpTab[j], dpTab[i] + 1);
                }
            }
        }

        int res = dpTab[lenN - 1];
        delete[] dpTab;
        return res;
    }
};

int main(void) {
    Solution solution;
    int arr1[] = {2, 3, 1, 1, 4};
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    int res1 = solution.jump(nums1);
    cout << res1 << endl;

    int arr2[] = {2, 3, 0, 1, 4};
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    int res2 = solution.jump(nums2);
    cout << res2 << endl;

    return 0;
}
