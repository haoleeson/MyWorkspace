#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 值互不相同，表明原数组单调递增，可通过二分逐步逼近找到旋转下标，再在两侧分别二分查找
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lenN = nums.size();
        int rotateI = findRotateIndex(nums, 0, lenN - 1);
        int leftSearchI = binSearch(nums, 0, rotateI, target);
        int rightSearchI = binSearch(nums, rotateI + 1, lenN - 1, target);

        if (leftSearchI == -1 && rightSearchI == -1) {
            return -1;
        }

        return leftSearchI != -1 ? leftSearchI : rightSearchI;
    }

private:
    inline int findRotateIndex(vector<int>& nums, int begin, int end) {
        int left = begin, right = end, mid = (begin + end) / 2;
        while (left < right) {
            // 若中值大于左端点，则旋转下标在中点右侧
            if (nums[mid] > nums[left]) {
                left = mid;
            } else {
                right = mid;
            }
            mid = (left + right) / 2;
        }
        return mid;
    }

    inline int binSearch(vector<int>& nums, int begin, int end, int target) {
        int left = begin, right = end, mid = (begin + end) / 2;
        while (left <= right) {
            if (target == nums[mid]) {
                return mid;
            } else if (target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
            mid = (left + right) / 2;
        }
        return -1;
    }
};

int main(void) {
    Solution solution;
    int arr1[] = {4, 5, 6, 7, 0, 1, 2};
    int target1 = 0;
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    int res1 = solution.search(nums1, target1);
    cout << res1 << endl;

    int arr2[] = {4, 5, 6, 7, 0, 1, 2};
    int target2 = 3;
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    int res2 = solution.search(nums2, target2);
    cout << res2 << endl;

    int arr3[] = {1};
    int target3 = 0;
    vector<int> nums3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    int res3 = solution.search(nums3, target3);
    cout << res3 << endl;

    return 0;
}
