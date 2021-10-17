#include <iostream>
#include <vector>

using namespace std;

/**
 * No491. 递增子序列（递归枚举 + 剪枝）
 * 给定一个整型数组, 你的任务是找到所有该数组的递增子序列，递增子序列的长度至少是2。

示例:

输入: [4, 6, 7, 7]
输出: [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7,7], [4,7,7]]
说明:

给定数组的长度不会超过 15。
数组中的整数范围是[-100,100]。
给定数组中可能包含重复数字，相等的数字应该被视为递增的一种情况。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/increasing-subsequences
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 力扣官解思路：递归枚举 + 剪枝
 * 思路与算法
 * 用递归的方法实现二进制枚举，那样枚举出所有元素是否被选择[0, 2^n - 1]，然后判断每个序列是否合法。
 *
 * 注意点：
 * 子序列去重：
 * function1.（存储合法的子序列二进制哈希值，若在遇到重复哈希值则跳过）
 * function2. 对选择和不选择做一些简单的限定，让枚举出来的都是合法的并且不重复
 * 合法性：给「选择」做一个限定条件，只有当前的元素大于等于上一个选择的元素的时候才能选择这个元素，这样枚举出来的所有元素都是合法的
 * 不重复性：给「不选择」做一个限定条件，只有当当前的元素不等于上一个选择的元素的时候，才考虑不选择当前元素
 *
 *
 * 【不重复性解释】：如果有两个相同的元素，我们会考虑这样四种情况：
 * 1.前者被选择，后者被选择
 * 2.前者被选择，后者不被选择
 * 3.前者不被选择，后者被选择
 * 4.前者不被选择，后者不被选择
 * 第二种情况和第三种情况其实是等价的，我们这样限制之后，舍弃了第二种，保留了第三种，于是达到了去重的目的。
 */
class Solution {
public:
    vector<int> tmp;
    vector<vector<int>> m_ans;
    int m_size = 0;

    /**
     *
     * @param curIndex 当前元素下标
     * @param lastNum 上一个被选择的元素
     * @param nums 数组
     */
    void dfs(int curIndex, int lastNum, vector<int>& nums){
        // 递归终止条件，走到最后，每个元素是/否被选择都已确定
        if (curIndex == m_size) {
            if (tmp.size() >= 2) {
                m_ans.push_back(tmp);
            }
            return;
        }

        // 是/否选择当前元素
        // 【是】合法性：只有当前的元素大于等于上一个选择的元素的时候才能选择这个元素
        if (nums[curIndex] >= lastNum) {
            tmp.push_back(nums[curIndex]);
            dfs(curIndex + 1, nums[curIndex], nums);
            tmp.pop_back();// 弹出当前元素（为不选择准备）
        }

        // 【否】不重复性：只有当前元素不等于上一个选择的元素的时候，才考虑不选择当前元素
        if (nums[curIndex] != lastNum) {
            dfs(curIndex + 1, lastNum, nums);
        }
    }

    vector<vector<int>> findSubsequences(vector<int>& nums) {
        m_size = nums.size();
        dfs(0, INT32_MIN, nums);
        return m_ans;
    }
};

void printVector(vector<vector<int>> vec2D) {
    cout << "total size = " << vec2D.size() << endl;
    for (int i = 0; i < vec2D.size(); ++i) {
        cout << "[";
        for (int j = 0; j < vec2D[i].size() - 1; ++j) {
            cout << vec2D[i][j] << ",";
        }
        cout << vec2D[i][vec2D[i].size() - 1] << "]" << endl;
    }
}

int main() {
    Solution solution;
    int arr[] = {4, 6, 7, 7};
    vector<int> nums(arr, arr + 4);

    vector<vector<int>> result = solution.findSubsequences(nums);
    printVector(result);

    return 0;
}
