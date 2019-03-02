/** 题目描述：
 * 53. 最大子序和
 * 给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
示例:
输入: [-2,1,-3,4,-1,2,1,-5,4],
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6。

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
    int maxSubArray(vector<int>& nums) {
        int sum = nums[0];
        int result = sum;
//        int iterator_star, iterator_end ;//记录连续字数组的起始下标
        for (int i=1; i<nums.size(); i++) {
            if (sum + nums[i] < nums[i]) {
                sum = nums[i];//更新子序列头元素
//                iterator_star = i; //更新子序列头元素下标
            } else {
                sum += nums[i];
            }
            if (sum > result) {
                result = sum;
//                iterator_end = i;//更新子序列尾元素下标
            }
        }
        //输出最大子数组的起始坐标
//        cout << "star:" << iterator_star << " , end:" << iterator_end << endl;
        return result;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    vector<int> Input = {-2,1,-3,4,-1,2,1,-5,4};
    cout << "Input = {";
    for(int i=0; i<Input.size()-1; i++){
        cout << Input[i] << ",";
    }
    cout << Input[Input.size()-1] <<"}" << endl;
    cout << "Output = " << solution.maxSubArray(Input)  << endl;
}
