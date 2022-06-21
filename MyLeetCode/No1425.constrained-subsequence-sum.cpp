#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
using namespace std;

// O(n)动态规划 + 简易滑动窗口2
class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int len = nums.size();
        int maxVal = nums[0];
        
        // 简易滑动窗口，存储 k 个历史 dp 值 及 维护其中最大值
        int qMax = nums[0];

        // 定义 dpTab：为包含 nums[i] 的最大子序列和
        int* dpTab = new int[len]{0};
        for (int i = 0; i < len; ++i) {
            dpTab[i] = nums[i];
        }

        for (int i = 1; i < len; ++i) {
            // 判断是否接上之前子序列
            if (qMax + nums[i] > dpTab[i]) {
                dpTab[i] = qMax + nums[i];
            }
            
            // 判断是否更新 qMax
            if (dpTab[i] >= qMax) {
                qMax = dpTab[i];
            } else if (i - k >= 0 && dpTab[i - k] == qMax) {
                // 判断离开窗口的元素是否是qMax，若是则更新 qMax
                qMax = dpTab[i - k + 1];
                for (int j = i - k + 2; j <= i; ++j) {
                    if (dpTab[j] > qMax) {
                        qMax = dpTab[j];
                    }
                }
            }

            // 更新最大子序列和
            if (dpTab[i] > maxVal) {
                maxVal = dpTab[i];
            }
        }
        return maxVal;
    }
};

// O(n)动态规划 + 简易滑动窗口，超时
class Solution0 {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int len = nums.size();
        int maxVal = nums[0];

        // 简易滑动窗口，存储 k 个历史 dp 值 及 维护其中最大值
        list<int> l;
        l.push_back(nums[0]);
        int qMax = nums[0];

        // 定义 dpTab：为包含 nums[i] 的最大子序列和
        int* dpTab = new int[len]{0};
        for (int i = 0; i < len; ++i) {
            dpTab[i] = nums[i];
        }

        for (int i = 1; i < len; ++i) {
            // 判断是否接上之前子序列
            if (qMax + nums[i] > dpTab[i]) {
                dpTab[i] = qMax + nums[i];
            }

            // 滑动窗口添加当前 dpTab[i] 的值
            l.push_back(dpTab[i]);
            if (dpTab[i] > qMax) {
                qMax = dpTab[i];
            }

            // 若窗口已满，弹出之前第 K 个元素
            if (l.size() > k) {
                int tmp = l.front();
                l.pop_front();
                // 若弹出值为曾经最大值，则更新最大值
                if (tmp == qMax) {
                    qMax = *max_element(l.begin(), l.end());
                }
            }

            if (dpTab[i] > maxVal) {
                maxVal = dpTab[i];
            }
        }
        return maxVal;
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {10, 2, -10, 5, 20};
    vector<int> nums1(arr1, arr1 + sizeof(arr1)/sizeof(int));
    cout << solution.constrainedSubsetSum(nums1, 2) << endl;

    int arr2[] = {-1,-2,-3};
    vector<int> nums2(arr2, arr2 + sizeof(arr2)/sizeof(int));
    cout << solution.constrainedSubsetSum(nums2, 1) << endl;

    int arr3[] = {10,-2,-10,-5,20};
    vector<int> nums3(arr3, arr3 + sizeof(arr3)/sizeof(int));
    cout << solution.constrainedSubsetSum(nums3, 2) << endl;

    return 0;
}
