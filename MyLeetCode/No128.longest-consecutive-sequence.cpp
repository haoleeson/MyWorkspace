#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// 官解：set 暂存
// 链接：https://leetcode.cn/problems/longest-consecutive-sequence/solution/zui-chang-lian-xu-xu-lie-by-leetcode-solution/
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        // 存储所有数，便于O(1)查询
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }

        int longestStreak = 0;

        // 遍历每个数
        for (const int& num : num_set) {
            // 判断前驱数 num - 1 是否存在，若不存在尝试增量校验后驱数
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }

                longestStreak = max(longestStreak, currentStreak);
            }
        }

        return longestStreak;
    }
};

// 思路：排序后统计 O(N logN)
class Solution0 {
public:
    int longestConsecutive(vector<int>& nums) {
        int lenN = nums.size();
        if (lenN < 2) {
            return lenN;
        }

        sort(nums.begin(), nums.end());

        int maxSubLen = INT_MIN;
        int tmpLen = 1;

        for (int i = 1; i < lenN; ++i) {
            // 尝试找到连续递增
            //            if (nums[i] == nums[i - 1]) {
            //                continue;
            //            } else
            if (nums[i] == nums[i - 1] + 1) {
                ++tmpLen;
                continue;
            } else if (nums[i] > nums[i - 1] + 1) {
                // 不连续
                if (tmpLen > maxSubLen) {
                    maxSubLen = tmpLen;
                }
                tmpLen = 1;
            }
        }
        // 最后一段子序列
        if (tmpLen > maxSubLen) {
            maxSubLen = tmpLen;
        }

        return maxSubLen;
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {100, 4, 200, 1, 3, 2};
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    int res1 = solution.longestConsecutive(nums1);
    cout << res1 << endl;

    int arr2[] = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    int res2 = solution.longestConsecutive(nums2);
    cout << res2 << endl;

    return 0;
}
