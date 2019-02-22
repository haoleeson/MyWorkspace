/** 题目描述：
 * 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
 * 
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190222
 * */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        bool isFind = false;
        int nums_Size = nums.size();
        vector<int> index;
        for(int i=0; i<nums_Size-1; i++){
            int tmp = target - nums[i];
            for(int j=i+1; j<nums_Size; j++){
                if (nums[j] == tmp){
                    index.push_back(i);
                    index.push_back(j);
                    isFind = true;
                    break;
                }
            }
            if(isFind){
                break;
            }
        }
        return index;
    }
};

int main(int argc, const char * argv[]) {
    vector<int> nums = {2, 11, 7, 15};
    vector<int> result;
    int target =  9;
    Solution s;
    result = s.twoSum(nums, target);
    cout << "result = " <<  result[0] << ", " << result[1] << endl;
}
