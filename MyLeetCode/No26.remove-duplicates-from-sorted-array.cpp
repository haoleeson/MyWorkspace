/** 题目描述：
 * 26. 删除排序数组中的重复项
 * 给定一个排序数组，你需要在原地删除重复出现的元素，使得每个元素只出现一次，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190226
 * */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //特殊情况：数组内元素个数为0或为1
        if (nums.size()<2) {
            return nums.size();
        }
        int Final_iterator = 0;
        for (int j=1; j<nums.size(); j++) {
            //寻到有无重复元素
            while (nums[j]==nums[Final_iterator]) {
                j++;
                //若直到末尾均重复
                if (j == nums.size()){
                    return Final_iterator+1;
                }
            }
            //将下标j移到不重复且有效的位置
            nums[++Final_iterator] = nums[j];
        }
        return Final_iterator+1;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    vector<int> Input = {0,0,1,1,1,2,2,3,3,4};
    cout << "Input = {";
    for(int i=0; i<Input.size()-1; i++){
        cout << Input[i] << ",";
    }
    cout << Input[Input.size()-1] <<"}" << endl;

    cout << "Output = " << solution.removeDuplicates(Input)  << endl;

    cout << "After Input = {";
    for(int i=0; i<Input.size()-1; i++){
        cout << Input[i] << ",";
    }
    cout << Input[Input.size()-1] <<"}" << endl;

}
