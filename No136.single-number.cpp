/** 题目描述：
 * 136. 只出现一次的数字
 * 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。

说明：

你的算法应该具有线性时间复杂度。 你可以不使用额外空间来实现吗？

示例 1:

输入: [2,2,1]
输出: 1
示例 2:

输入: [4,1,2,1,2]
输出: 4

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190319
 * */
#include <iostream>
#include <vector>

using namespace std;

//分析，利用异或的特性： a ^ a = 0,   0 ^ a = a
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int result = nums[0];
        for (int i=1; i<nums.size(); i++) {
            result ^= nums[i];
        }
        return result;
    }
};

int main(int argc, const char * argv[]) {
    Solution s;
    vector<int> Input = {4,1,2,1,2};
    cout << "Output:" << s.singleNumber(Input) << endl;
    cout << endl;
}

