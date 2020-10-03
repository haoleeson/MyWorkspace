/**
 * No1. 两数之和
 * 给定一个整数数组 nums和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

示例:
给定 nums = [2, 7, 11, 15], target = 9
因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/two-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */
#include <iostream>
#include <vector>
#include <map>
#include "myTools.h"
using namespace std;

/**
 * 思路2：用Map记录待寻找的伙伴数
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans;
        int size = nums.size();
        if (size < 2) {
            return ans;
        }
        map<int, int> findNumMap;// 记录 <待寻找的伙伴数，原数下标>
        map<int, int>::iterator iter;
        findNumMap.insert(make_pair(target - nums[0], 0));

        for (int i = 1; i < size; ++i) {
            iter = findNumMap.find(nums[i]);

            // 若找到，返回
            if (iter != findNumMap.end()) {
                ans.push_back(iter->second);
                ans.push_back(i);
                break;
            }
            // 未找到，插入 <待寻找的伙伴数，原数下标>
            findNumMap.insert(make_pair(target - nums[i], i));
        }
        return ans;
    }
};

/**
 * 思路1：暴力枚举
 * 时间复杂度：O(n^2)
 * 空间复杂度：O(1)
 */
class Solution1 {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int tmp, size = nums.size();
        vector<int> ans;

        for (int i = 0; i < size - 1; ++i) {
            tmp = target - nums[i];
            for (int j = i + 1; j < size; ++j) {
                if (nums[j] == tmp){
                    ans.push_back(i);
                    ans.push_back(j);
                    return ans;
                }
            }
        }
        return ans;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    vector<int> nums = {11, 15, 2, 7};
    int target =  9;

    vector<int> result = solution.twoSum(nums, target);
    MyTools::printVec(result);
    return 0;
}
