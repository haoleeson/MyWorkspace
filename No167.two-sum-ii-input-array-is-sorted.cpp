/**
 * 167. 两数之和 II - 输入有序数组
 * 给定一个已按照升序排列 的有序数组，找到两个数使得它们相加之和等于目标数。

函数应该返回这两个下标值 index1 和 index2，其中 index1 必须小于 index2。

说明:

返回的下标值（index1 和 index2）不是从零开始的。
你可以假设每个输入只对应唯一的答案，而且你不可以重复使用相同的元素。
示例:

输入: numbers = [2, 7, 11, 15], target = 9
输出: [1,2]
解释: 2 与 7 之和等于目标数 9 。因此 index1 = 1, index2 = 2 。

 * coder:eisenhao
 * 20190321
 * */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result;
//        vector<int> numbers = {2,7,11,15};
//        int target = 9;
        //特殊情况: 最小的两位数之和都比target大
        if (numbers[0]+numbers[1] > target) {
            return result;
        }
        //特殊情况： 最大两个数之和都小于target
        if (numbers[numbers.size()-2]+numbers[numbers.size()-1] < target) {
            return result;
        }
        int index1, index2, mid=1;//下标
        //求离target的一半最近的下标mid_index
        {
            int tmp = target >> 1, left = 1, right = numbers.size()-1;
            while  (left <= right) {
                mid = (left + right) >> 1;
                if (numbers[mid]==tmp){
                    break;
                }
                if (numbers[mid] < tmp) {
                    left = mid+1;
                }
                if (numbers[mid] > tmp) {
                    right = mid-1;
                }
            }
        }
        //开始向左， 向右搜寻解
        index2 = mid;
        //index2向右移动
        while (index2 < numbers.size()) {
            //index1向左移动
            index1 = index2 - 1;
            while (numbers[index1]+numbers[index2]>=target && index1>-1) {
                //若找到
                if (numbers[index1]+numbers[index2] == target) {
                    result.push_back(++index1);
                    result.push_back(++index2);
                    return result;
                }
                index1--;
            }
            index2++;
        }
        return result;
    }
};

int main(void) {
    Solution s;
    vector<int> num = {0,0,3,4};
    vector<int> res;
    res = s.twoSum(num, 0);
    if (res.size()==0) {
        cout << "[]" << endl;
    } else {
        cout << "[" << res[0] << ", " << res[1] << "]" << endl;
    }
    return 0;
}

