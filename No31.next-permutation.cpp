/**
 * No31. 下一个排列
 * 实现获取下一个排列的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须原地修改，只允许使用额外常数空间。

以下是一些例子，输入位于左侧列，其相应输出位于右侧列。
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/next-permutation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int i, j, size = nums.size();
        // 1. 从后向前查找第一个相邻升序的元素 nums[i] < nums[i + 1]。此时 [i+1, end) 必然是降序
        i = size - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            --i;
        }

        if (i > -1) {
            // 2a. 继续在[i+1, end)逆序寻找到第一个(最小的) nums[j] > nums[i]
            j = size - 1;
            while (nums[j] <= nums[i]) {
                --j;
            }
            // 3. 交换 nums[i], nums[j]，此时 [i+1, end) 必然是降序
            nums[i] ^= nums[j];
            nums[j] ^= nums[i];
            nums[i] ^= nums[j];
            // 4. 要使下一个排列最小，翻转降序数组[i+1, end)（使其升序）
        }
        // 2b. 若未交换（降序排列），翻转降序数组[0, end)（使其升序）
        ++i;
        // 翻转降序数组
        j = size - 1;
        while (i < j) {
            nums[i] ^= nums[j];
            nums[j] ^= nums[i];
            nums[i] ^= nums[j];
            ++i;
            --j;
        }
    }
};

int main() {
    Solution solution;
    int arr[] = {1,3,2};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    solution.nextPermutation(nums);
    MyTools::printVec(nums);
    return 0;
}
