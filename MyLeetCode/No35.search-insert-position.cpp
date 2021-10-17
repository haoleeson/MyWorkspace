/** 题目描述：
 * 35. 搜索插入位置
 * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

你可以假设数组中无重复元素。

示例 1:

输入: [1,3,5,6], 5
输出: 2
示例 2:

输入: [1,3,5,6], 2
输出: 1
示例 3:

输入: [1,3,5,6], 7
输出: 4
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190228
 * */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int i=0;
        while (i<nums.size()){
            if (target <= nums[i]) {
                return i;
            }
            i++;
        }
        return i;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    vector<int> Input = {1,3,5,6};
    int target = 5;
    cout << "Input = {";
    for(int i=0; i<Input.size()-1; i++){
        cout << Input[i] << ",";
    }
    cout << Input[Input.size()-1] <<"}" << endl;

    cout << "target = " << target << endl << endl;

    cout << "Output = " << solution.searchInsert(Input, target)  << endl;

}
