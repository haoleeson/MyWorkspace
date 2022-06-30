#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int lenN = nums.size();

        int iterator = 0;

        for (int i = 0, j; i < lenN; ++i) {
            // 尝试向后找重复元素，nums[i] ~ nums[j] 为重复元素
            j = i + 1;
            while (j < lenN && nums[j] == nums[i]) {
                ++j;
            }
            --j;

            // 出现重复字符时
            if (j > i) {
                nums[iterator] = nums[i];
                nums[iterator + 1] = nums[i];
                iterator += 2;
                i = j;
            } else {
                nums[iterator] = nums[i];
                ++iterator;
            }
        }

        // 删除尾部多余元素
        nums.erase(nums.begin() + iterator, nums.end());

        return iterator;
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {1, 1, 1, 2, 2, 3};
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    MyTools::printVec(nums1);
    int res1 = solution.removeDuplicates(nums1);
    MyTools::printVec(nums1);
    cout << res1 << endl;

    int arr2[] = {0, 0, 1, 1, 1, 1, 2, 3, 3};
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    MyTools::printVec(nums2);
    int res2 = solution.removeDuplicates(nums2);
    MyTools::printVec(nums2);
    cout << res2 << endl;

    int arr3[] = {3};
    vector<int> nums3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    MyTools::printVec(nums3);
    int res3 = solution.removeDuplicates(nums3);
    MyTools::printVec(nums3);
    cout << res3 << endl;

    return 0;
}
