#include <iostream>
#include <vector>
using namespace std;

/**
 * NO77. 组合（回溯）
 * 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

示例:
输入: n = 4, k = 2
输出:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combinations
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 回溯
 */
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ans;
        if (k < 1 || n < k) {
            return ans;
        }
        vector<int> a(k);
        int iterator = 0, maxStartValue = n - k + 1;

        a[0] = 1;
        while (a[0] <= maxStartValue) {
            // 若当前数字非法，回溯
            if (a[iterator] > maxStartValue + iterator) {
                --iterator;
                ++a[iterator];
                continue;
            }

            // 合法，且非第k个数，则继续遍历下一位数
            if (iterator < k - 1) {
                ++iterator;
                a[iterator] = a[iterator - 1] + 1;
            }
            // 合法，且为第k个数
            else {
                ans.push_back(a);
                ++a[iterator];
            }
        }
        return ans;
    }
};


template <typename T>
void printVec2D(vector<vector<T>> vec) {
    int size = vec.size();
    cout << "[" << endl;
    if (size > 0) {
        for (int i = 0; i < size; ++i) {
            cout << "    [";
            cout << vec[i][0];
            for (int j = 1; j < vec[i].size(); ++j) {
                cout << "," << vec[i][j];
            }
            cout << "]" << endl;
        }
    }
    cout << "]" << endl;
}

int main()
{
    Solution solution;
    vector<vector<int>> result = solution.combine(4, 3);
    printVec2D(result);
    cout << "hello world" << endl;
    return 0;
}
