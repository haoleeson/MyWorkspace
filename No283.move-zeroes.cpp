/**
 * No283. 移动零
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:
输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/move-zeroes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size(), zeroCnt = 0;
        // 第 i 个非零元素前置 zeroCnt 位
        for (int i = 0; i < size; ++i) {
            if (nums[i] == 0) {
                ++zeroCnt;
            } else {
                nums[i - zeroCnt] = nums[i];
            }
        }
        // 末尾 zeroCnt 个元素置零
        for (int i = size - zeroCnt; i < size; ++i) {
            nums[i] = 0;
        }
    }
};

int main() {
    Solution solution;
    int arr[] = {0,12,0,3,1};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(int));
    solution.moveZeroes(A);
    MyTools::printVec(A);
    return 0;
}
