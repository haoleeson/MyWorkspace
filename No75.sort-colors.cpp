/**
 * No75. 颜色分类
 * 给定一个包含红色、白色和蓝色，一共n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、1 和 2 分别表示红色、白色和蓝色。

注意:
不能使用代码库中的排序函数来解决这道题。

示例:

输入: [2,0,2,1,1,0]
输出: [0,0,1,1,2,2]
进阶：

一个直观的解决方案是使用计数排序的两趟扫描算法。
首先，迭代计算出0、1 和 2 元素的个数，然后按照0、1、2的排序，重写当前数组。
你能想出一个仅使用常数空间的一趟扫描算法吗？

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-colors
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * 思路2：双指针
 */
class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = nums.size(), start0 = 0, end2 = n - 1;
        for (int i = start0; i <= end2; ++i) {
            // 若为0，交换当前值与为0的下标的值
            if (nums[i] == 0) {
                nums[i] = nums[start0];
                nums[start0++] = 0;
            }
            // 若为2，交换当前值与为2的下标的值
            else if (nums[i] == 2) {
                nums[i--] = nums[end2];
                nums[end2--] = 2;
            }
        }
    }
};

/**
 * 思路1：计数
 */
class Solution1 {
public:
    void sortColors(vector<int>& nums) {
        int iterator = 0;
        int count[3] = {0};
        for (int i : nums) {
//            if (0 <= i && i <= 1)
            ++count[i];
        }
        count[1] += count[0];
        count[2] = nums.size();
        for (int i = 0; i < 3; ++i) {
            while (iterator < count[i]) {
                if (nums[iterator] != i) {
                    nums[iterator] = i;
                }
                ++iterator;
            }
        }
    }
};

int main() {
    Solution solution;
    int arr1[] = {2,0,2,1,1,0};
    vector<int> nums(arr1, arr1 + sizeof(arr1) / sizeof(int));
    solution.sortColors(nums);
    MyTools::printVec(nums);
    return 0;
}
