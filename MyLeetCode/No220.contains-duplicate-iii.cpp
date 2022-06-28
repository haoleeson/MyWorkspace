#include <iostream>
#include <set>
#include <vector>

using namespace std;

// 官解
//作者：LeetCode-Solution
//链接：https://leetcode.cn/problems/contains-duplicate-iii/solution/cun-zai-zhong-fu-yuan-su-iii-by-leetcode-bbkt/

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        set<int> rec;
        for (int i = 0; i < n; i++) {
            // 判断是否存在目标对
            auto iter = rec.lower_bound(max(nums[i], INT_MIN + t) - t);
            if (iter != rec.end() && *iter <= min(nums[i], INT_MAX - t) + t) {
                return true;
            }

            // 加入新数字
            rec.insert(nums[i]);

            //删除老数字
            if (i >= k) {
                rec.erase(nums[i - k]);
            }
        }
        return false;
    }
};

// 暴力解法，超时
class Solution1 {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int lenN = nums.size();
        if (lenN < 2) {
            return false;
        }

        for (int i = 1; i < lenN; ++i) {
            for (int j = max(0, i - k); j < i; ++j) {
                if (validAbs(nums[j], nums[i], t)) {
                    return true;
                }
            }
        }

        return false;
    }

private:
    inline bool validAbs(long a, long b, long t) { return a > b ? (a - b <= t) : (b - a <= t); }
};

int main(void) {
    Solution solution;
    int arr1[] = {1, 2, 3, 1};
    int k1 = 3;
    int t1 = 0;
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    bool res1 = solution.containsNearbyAlmostDuplicate(nums1, k1, t1);
    cout << res1 << endl;

    int arr2[] = {1, 0, 1, 1};
    int k2 = 1;
    int t2 = 2;
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    bool res2 = solution.containsNearbyAlmostDuplicate(nums2, k2, t2);
    cout << res2 << endl;

    int arr3[] = {1, 5, 9, 1, 5, 9};
    int k3 = 2;
    int t3 = 3;
    vector<int> nums3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    bool res3 = solution.containsNearbyAlmostDuplicate(nums3, k3, t3);
    cout << res3 << endl;

    return 0;
}
