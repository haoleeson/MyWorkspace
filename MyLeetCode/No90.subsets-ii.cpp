#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "myTools.h"

using namespace std;

// 限定条件：
// 1 <= nums.length <= 10
// -10 <= nums[i] <= 10

// 思路：动态规划 + set 去重
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        int lenN = nums.size();
        sort(nums.begin(), nums.end());

        vector<vector<int>> res;
        // 添加 空集
        res.push_back(vector<int>{});

        // 记录已有子集
        unordered_set<string> s;

        // 逐渐增加长度 len， 则子序列 nums[0:i] 的所有排列 为 nums[0:i-1] 的每个子集 考虑是否加上
        // nums[i]（去除重复子集）
        for (int i = 0; i < lenN; ++i) {
            int lenR = res.size();

            // 依次尝试在上一长度的所有解中追加上 nums[i]
            for (int j = 0; j < lenR; ++j) {
                vector<int> tmp(res[j]);
                tmp.push_back(nums[i]);
                string tmpStr = vec2Str(tmp);
                // 若不重复，添加
                if (!s.count(tmpStr)) {
                    res.push_back(tmp);
                    s.insert(tmpStr);
                }
            }
        }

        return res;
    }

    // 将有序数组转换为字符串
    string vec2Str(vector<int>& v) {
        int lenV = v.size();
        if (lenV == 1) {
            return to_string(v[0]);
        }
        string res = to_string(v[0]);
        for (int i = 1; i < lenV; ++i) {
            res += "," + to_string(v[i]);
        }
        return res;
    }
};

int main(void) {
    Solution solution;
    int arr1[] = {1, 2, 2};
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    vector<vector<int>> res1 = solution.subsetsWithDup(nums1);
    MyTools::printVec2D(res1);

    int arr2[] = {0};
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    vector<vector<int>> res2 = solution.subsetsWithDup(nums2);
    MyTools::printVec2D(res2);

    return 0;
}
