#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * No39. 组合总和（回溯）
 * 给定一个无重复元素的数组 candidates 和一个目标数 target，找出 candidates 中所有可以使数字和为 target 的组合。
 * candidates中的数字可以无限制重复被选取。

说明：
所有数字（包括target）都是正整数。
解集不能包含重复的组合。

示例1：
输入：candidates = [2,3,6,7], target = 7,
所求解集为：
[
  [7],
  [2,2,3]
]

示例2：
输入：candidates = [2,3,5], target = 8,
所求解集为：
[
 [2,2,2,2],
 [2,3,3],
 [3,5]
]


提示：
1 <= candidates.length <= 30
1 <= candidates[i] <= 200
candidate 中的每个元素都是独一无二的。
1 <= target <= 500

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> tmp;
        int size = candidates.size();
        int count[201] = {0};
        int minCanIndex, leftTarget, maxCanIndex = size - 1;// 组合的最大数字所在下标

        sort(candidates.begin(), candidates.end());

        // 确定组合的最大数字[7/6/3/2]
        while (maxCanIndex >= 0) {

            // 初始化最大数字的个数
            count[candidates[maxCanIndex]] = target / candidates[maxCanIndex];
            leftTarget = target - count[candidates[maxCanIndex]] * candidates[maxCanIndex];
            minCanIndex = maxCanIndex;

            // 直至最大数字个个数为0
            while (count[candidates[maxCanIndex]] > 0) {

                // 用最大数贪心凑
                while (leftTarget >= candidates[minCanIndex]) {
                    ++count[candidates[minCanIndex]];
                    leftTarget -= candidates[minCanIndex];
                }

                // 若能整凑，则记录组合
                if (leftTarget == 0) {
                    // 构建 tmp 输出
                    for (int i = minCanIndex; i <= maxCanIndex; ++i) {
                        for (int j = 0; j < count[candidates[i]]; ++j) {
                            tmp.push_back(candidates[i]);
                        }
                    }
                    ans.push_back(tmp);
                    tmp.clear();
                    vector<int>().swap(tmp);

                    if (minCanIndex != 0) {
                        --count[candidates[minCanIndex]];
                        leftTarget += candidates[minCanIndex];
                    }
                }

                // 若不能整凑，且已到最小下标0，回溯
                if (minCanIndex == 0) {
                    if (count[candidates[minCanIndex]] != 0) {
                        leftTarget += count[candidates[minCanIndex]] * candidates[minCanIndex];
                        count[candidates[minCanIndex++]] = 0;
                    }
                    if (minCanIndex > maxCanIndex) {
                        break;
                    }
                    while (minCanIndex < maxCanIndex && count[candidates[minCanIndex]] == 0) {
                        ++minCanIndex;
                    }
                    --count[candidates[minCanIndex]];
                    if (count[candidates[minCanIndex]] > -1) {
                        leftTarget += candidates[minCanIndex];
                    }
                }

                // 若不能整凑，但未到最小下标，则继续下探
                --minCanIndex;
            }
            --maxCanIndex;
        }
        return ans;
    }
};

template<typename T>
void printVec2D(vector<vector<T>>& vec) {
    int size = vec.size(), size2;
    cout << "[" << endl;
    if (size > 0) {

        size2 = vec[0].size();
        cout << "    [" << vec[0][0];
        for (int j = 1; j < size2; ++j) {
            cout << "," << vec[0][j];
        }
        cout << "]";

        for (int i = 1; i < size; ++i) {
            size2 = vec[i].size();
            cout << "," << endl << "    [" << vec[i][0];
            for (int j = 1; j < size2; ++j) {
                cout << "," << vec[i][j];
            }
            cout << "]";
        }
    }
    cout << endl << "]" << endl;
}

int main() {
    Solution solution;
    int arr[] = {2,3,5};
    int target = 8;
    vector<int> candidates(arr, arr + sizeof(arr) / sizeof(int));
    vector<vector<int>> result = solution.combinationSum(candidates, target);
    printVec2D(result);
    return 0;
}