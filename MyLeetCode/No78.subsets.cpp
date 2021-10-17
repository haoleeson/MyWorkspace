#include <iostream>
#include <algorithm>
#include "myTools.h"
using namespace std;

/**
 * No78. 子集 (dfs)
 * 给定一组不含重复元素的整数数组nums，返回该数组所有可能的子集（幂集）。
 * 说明：解集不能包含重复的子集。

示例:
输入: nums = [1,2,3]
输出:
[
  [3],
 [1],
 [2],
 [1,2,3],
 [1,3],
 [2,3],
 [1,2],
 []
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/subsets
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    vector<vector<int>> m_ans;
    vector<int> m_tmp;
    int m_size;
    void dfs(vector<int>& nums, int startI) {
        for (int i = startI; i < m_size; ++i) {
            m_tmp.push_back(nums[i]);
            m_ans.push_back(m_tmp);
            dfs(nums, i + 1);
            m_tmp.pop_back();

            // 避免重复
            while (i + 1 < m_size && nums[i] == nums[i + 1]) {
                ++i;
            }
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        m_ans.push_back(m_tmp);
        m_size  = nums.size();
        if (m_size < 2) {
            if (m_size == 1) {
                m_ans.push_back(nums);
            }
            return m_ans;
        }
        sort(nums.begin(), nums.end());
        dfs(nums, 0);
        return m_ans;
    }
};

int main() {
    Solution solution;
    int arr[] = {1, 2, 3};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    vector<vector<int>> result = solution.subsets(nums);
    MyTools::printVec2D(result);
    return 0;
}