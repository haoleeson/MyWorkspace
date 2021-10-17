/** 题目描述：
 * 66. 加一
 * 给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。

最高位数字存放在数组的首位， 数组中每个元素只存储一个数字。

你可以假设除了整数 0 之外，这个整数不会以零开头。

示例:

示例 1:

输入: [1,2,3]
输出: [1,2,4]
解释: 输入数组表示数字 123。
示例 2:

输入: [4,3,2,1]
输出: [4,3,2,2]
解释: 输入数组表示数字 4321。
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190302
 * */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int iterator = digits.size() - 1;
        //从最后一位 逆序判断到 第二位，因为第一位涉及可能需要插入一个元素
        while (iterator > 0) {
            if (++digits[iterator] == 10) {
                digits[iterator--] = 0;
            } else {
                return digits;
            }
        }
        //判断第一位是否还会产生进位
        if (++digits[0] == 10) {
            digits[0] = 0;
            digits.insert(digits.begin(), 1);
        }
        return digits;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    vector<int> Input = {9, 9, 9};
    cout << "Input = {";
    for(int i=0; i<Input.size()-1; i++){
        cout << Input[i] << ",";
    }
    cout << Input[Input.size()-1] <<"}" << endl;

    vector<int> Output = solution.plusOne(Input);
    cout << "Output = {";
    for(int i=0; i<Output.size()-1; i++){
        cout << Output[i] << ",";
    }
    cout << Output[Output.size()-1] <<"}" << endl;
}
