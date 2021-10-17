/** 题目描述：
 * 27. 移除元素
 * 给定一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，返回移除后数组的新长度。

不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1) 额外空间的条件下完成。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
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
    int removeElement(vector<int>& nums, int val) {
        int i = 0, iterator = nums.size();
        while(iterator > 0){
            if(nums[iterator-1] != val) {
                break;
            }
            iterator--;
        }
        while(i < iterator) {
            if (nums[i] == val) {
                nums[i] = nums[--iterator];
                while(iterator > 0){
                    if(nums[iterator-1] != val) {
                        break;
                    }
                    iterator--;
                }
            }
            i++;
        }
        return iterator;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    vector<int> Input = {0,1,2,2,3,0,4,2};
    int val = 2;
    cout << "Input = {";
    for(int i=0; i<Input.size()-1; i++){
        cout << Input[i] << ",";
    }
    cout << Input[Input.size()-1] <<"}" << endl;

    cout << "val = " << val << endl << endl;

    cout << "Output = " << solution.removeElement(Input, val)  << endl;

    cout << "After Input = {";
    for(int i=0; i<Input.size()-1; i++){
        cout << Input[i] << ",";
    }
    cout << Input[Input.size()-1] <<"}" << endl;

}
