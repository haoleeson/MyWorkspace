#include <algorithm>
#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

//思路2：快速选择 O(N) + 3-way-partition O(N)
//作者：hexcat
//链接：https://leetcode.cn/problems/wiggle-sort-ii/solution/yi-bu-yi-bu-jiang-shi-jian-fu-za-du-cong-onlognjia/

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int lenN = nums.size();
        if (lenN < 2) {
            return;
        }

        int midI = (lenN + 1) / 2;
        vector<int> arr = nums;

        // 快速选择，找到中位数 O(N)
        quickSelect(arr, 0, lenN - 1, midI);
        int midNum = arr[midI];

        // 中位数划分数组（将小于中位数放左侧，大于中位数放右侧） O(N)
        threeWayPartition(arr, midNum);

        // 将左右两半数组进行穿插 O(N)
        for (int i = 0, j = midI - 1, k = lenN - 1; i < lenN; i += 2, --j, --k) {
            // 奇数位为 nums[midI - 1] 下标递减
            nums[i] = arr[j];
            // 偶数位为 nums[lenN - 1] 下标递减
            if (i + 1 < lenN) {
                nums[i + 1] = arr[k];
            }
        }
    }

private:
    // 快速选择数组的第 n 下标的数（双指针，相向而行） O(N)
    void quickSelect(vector<int>& nums, int begin, int end, int n) {
        if (begin >= end) {
            return;
        }

        int left = begin;
        int key = (nums[begin] + nums[end]) / 2; // 关键字

        for (int i = begin; i <= end; ++i) {
            if (nums[i] <= key) {
                if (i > left) {
                    swap(nums[i], nums[left]);
                }
                ++left;
            }
        }
        --left;

        if (left > n) {
            quickSelect(nums, begin, left - 1, n);
        } else if (left < n) {
            quickSelect(nums, left + 1, end, n);
        }
    }

    // 中位数划分数组（将小于中位数放左侧，大于中位数放右侧） O(N)
    inline void threeWayPartition(vector<int>& arr, int midNum) {
        int startI = 0, endI = arr.size() - 1, i = 0;
        while (i < endI) {
            if (arr[i] > midNum) {
                swap(arr[i], arr[endI--]);
            } else if (arr[i] < midNum) {
                swap(arr[i++], arr[startI++]);
            } else {
                ++i;
            }
        }
    }
};

//思路1：排序
// O(N*logN)，然后从中间位置进行等分（如果数组长度为奇数，则将中间的元素分到前面），然后将两个数组进行穿插
class Solution1 {
public:
    void wiggleSort(vector<int>& nums) {
        int lenN = nums.size();
        vector<int> arr = nums;

        sort(arr.begin(), arr.end());
        int midI = (lenN + 1) / 2;
        for (int i = 0, j = midI - 1, k = lenN - 1; i < lenN; i += 2, --j, --k) {
            // 奇数位为 nums[midI - 1] 下标递减
            nums[i] = arr[j];
            // 偶数位为 nums[lenN - 1] 下标递减
            if (i + 1 < lenN) {
                nums[i + 1] = arr[k];
            }
        }
    }
};

int main(void) {
    Solution solution;
    int arr1[] = {1, 5, 1, 1, 6, 4};
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    cout << "Before:" << endl;
    MyTools::printVec(nums1);
    solution.wiggleSort(nums1);
    cout << "After:" << endl;
    MyTools::printVec(nums1);
    cout << endl;

    int arr2[] = {1, 3, 2, 2, 3, 1};
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    cout << "Before:" << endl;
    MyTools::printVec(nums2);
    solution.wiggleSort(nums2);
    cout << "After:" << endl;
    MyTools::printVec(nums2);

    int arr3[] = {1, 1, 2, 2, 2, 1};
    vector<int> nums3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    cout << "Before:" << endl;
    MyTools::printVec(nums3);
    solution.wiggleSort(nums3);
    cout << "After:" << endl;
    MyTools::printVec(nums3);

    int arr4[] = {1, 2, 3, 3, 5, 5, 2, 4, 5, 2, 3, 2};
    vector<int> nums4(arr4, arr4 + sizeof(arr4) / sizeof(int));
    cout << "Before:" << endl;
    MyTools::printVec(nums4);
    solution.wiggleSort(nums4);
    cout << "After:" << endl;
    MyTools::printVec(nums4);

    return 0;
}
