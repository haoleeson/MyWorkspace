#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

//官解：二分，对于无法判断 a[l]=a[mid]=a[r] 情况时，收敛边界（左边界+1，右边界-1）
//链接：https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/solution/sou-suo-xuan-zhuan-pai-xu-shu-zu-ii-by-l-0nmp/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        if (n == 1) {
            return nums[0] == target;
        }

        int l = 0, r = n - 1, mid;
        while (l <= r) {
            mid = (l + r) / 2;

            if (nums[mid] == target) {
                return true;
            }

            // 收敛边界
            if (nums[l] == nums[mid] && nums[mid] == nums[r]) {
                ++l;
                --r;
            } else if (nums[l] <= nums[mid]) {
                if (nums[l] <= target && target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[n - 1]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }

        return false;
    }
};

// 原数组非降序，可通过二分逐步逼近找到旋转下标，再在两侧分别二分查找
class Solution0 {
public:
    bool search(vector<int>& nums, int target) {
        int lenN = nums.size();
        if (lenN == 1) {
            return nums[0] == target;
        }

        int rotateI = findRotateIndex(nums, 0, lenN - 1);
        int leftSearchI = binSearch(nums, 0, rotateI, target);
        int rightSearchI = binSearch(nums, rotateI + 1, lenN - 1, target);

        return (leftSearchI != -1 || rightSearchI != -1);
    }

private:
    inline int findRotateIndex(vector<int>& nums, int begin, int end) {
        int left = begin, right = end, mid;
        int lenN = nums.size();

        // 右侧收敛与左端口相同值
        while (right < lenN && nums[right] == nums[0]) {
            --right;
        }
        // 左侧收敛相同值
        while (left + 1 < lenN && nums[left + 1] == nums[left]) {
            ++left;
        }

        while (left < right) {
            mid = (left + right) / 2;
            // 若中值小于右端点，则旋转下标在中点左侧
            if (nums[mid] < nums[right]) {
                right = mid;
            } else if (nums[mid] > nums[left]) {
                left = mid;
            } else {
                left++;
                right--;
            }
        }
        return mid;
    }

    inline int binSearch(vector<int>& nums, int begin, int end, int target) {
        int left = begin, right = end, mid;
        while (left <= right) {
            mid = (left + right) / 2;
            if (target == nums[mid]) {
                return mid;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return -1;
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {2, 5, 6, 0, 0, 1, 2};
    int target1 = 0;
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    bool res1 = solution.search(nums1, target1);
    cout << res1 << endl;

    int arr2[] = {2, 5, 6, 0, 0, 1, 2};
    int target2 = 3;
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    bool res2 = solution.search(nums2, target2);
    cout << res2 << endl;

    int arr3[] = {2, 2, 2, 2, 2, 2, 2, 2};
    int target3 = 0;
    vector<int> nums3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    bool res3 = solution.search(nums3, target3);
    cout << res3 << endl;

    int arr4[] = {1};
    int target4 = 0;
    vector<int> nums4(arr4, arr4 + sizeof(arr4) / sizeof(int));
    bool res4 = solution.search(nums4, target4);
    cout << res4 << endl;

    int arr5[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1};
    int target5 = 0;
    vector<int> nums5(arr5, arr5 + sizeof(arr5) / sizeof(int));
    bool res5 = solution.search(nums5, target5);
    cout << res5 << endl;

    return 0;
}
