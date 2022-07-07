#include <string.h>

#include <iostream>

#include "myTools.h"

using namespace std;

// 官解思路： 标记
// 对于一个长度为 N 的数组，其中没有出现的最小正整数只能在 [1,N+1] 中。
//  - 如果 [1, N] 都出现了，那么答案是 N+1
//  - 否则，答案是 [1,N] 中没有出现的最小正整数
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        int N_1 = n + 1;

        // 第一遍遍历，先将负数变为 N + 1
        for (int& num : nums) {
            if (num <= 0) num = N_1;
        }

        // 第二遍遍历，将出现在 [1, N] 之间的值(-1)视作下标，并标记该值（将该下标中的数改为负数）
        for (int i = 0, absVal; i < n; ++i) {
            // 取绝对值，不受是否被标记影响（仍可根据值 去标记下标）
            absVal = abs(nums[i]);
            if (absVal <= n) nums[absVal - 1] = -abs(nums[absVal - 1]);
        }

        // 第三遍遍历，找到第一个值为正数的下标
        int index = 0;
        while (index < n && nums[index] <= 0) {
            index++;
        }

        // index == n 表示 1~N 都出现了，则 返回 N+1 ，否则，返回第一个未被标记（为正数的）的下标（+1）
        // 正好都是 index + 1
        return index + 1;
    }

private:
    inline int abs(int a) { return a < 0 ? -a : a; }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    int arr1[] = {1, 2, 0};
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    int res1 = solution.firstMissingPositive(nums1);
    cout << res1 << endl;

    int arr2[] = {3, 4, -1, 1};
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    int res2 = solution.firstMissingPositive(nums2);
    cout << res2 << endl;

    int arr3[] = {7, 8, 9, 11, 12};
    vector<int> nums3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    int res3 = solution.firstMissingPositive(nums3);
    cout << res3 << endl;

    return 0;
}
