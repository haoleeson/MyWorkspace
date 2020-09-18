#include <iostream>
#include <algorithm>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No47.全排列II (dfs)
 * 给定一个可包含重复数字的序列，返回所有不重复的全排列

示例:
输入: [1,1,2]
输出:
[
 [1,1,2]
 [1,2,1]
 [2,1,1]
 ]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/permutations-ii/
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    vector<vector<int>> m_ans;
    int m_size;
    vector<int> m_tmp;
    bool* m_flag;

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        m_size = nums.size();
        // 0 or 1
        if (m_size < 2) {
            if (m_size == 1) {
                m_ans.push_back(nums);
            }
            return m_ans;
        }
        m_flag = new bool[m_size]{false};
        vector<int> tmp(m_size, 0);
        m_tmp = tmp;

        // 先排序 O(NlogN)
        sort(nums.begin(), nums.end());

        dfs(nums, 0);

        delete []m_flag;
        return m_ans;
    }

    void dfs(vector<int>& nums, int index) {
        if (index == m_size) {
            m_ans.push_back(m_tmp);
            return;
        }

        for (int i = 0; i < m_size; ++i) {
            // 未访问过
            if (!m_flag[i]) {
                m_flag[i] = true;
                m_tmp[index] = nums[i];
                dfs(nums, index + 1);
                m_flag[i] = false;// 恢复状态
                // 同一index，排除相同值（剪枝）
                while (i + 1 < m_size && nums[i] == nums[i + 1]) {
                    ++i;
                }
            }
        }
    }
};


int main() {
    Solution solution;
    int arr[] = {1,1,2};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    vector<vector<int>> result = solution.permuteUnique(nums);
    MyTools::printVec2D(result);
    return 0;
}