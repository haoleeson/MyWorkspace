#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * No40. 组合总和 II（回溯）
 * 给定一个数组candidates和一个目标数target，找出candidates中所有可以使数字和为target的组合。
 * candidates中的每个数字在每个组合中只能使用一次。

说明：
所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。

示例1:
输入: candidates =[10,1,2,7,6,1,5], target =8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]

示例2:
输入: candidates =[2,5,2,1,2], target =5,
所求解集为:
[
 [1,2,2],
 [5]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> tmp;
        int size = candidates.size();
        vector<bool> choseFlag(size, false);
        int lastHuiSuNum, lastMaxVal = -1, minCanIndex, leftTarget, maxCanIndex = size - 1;// 组合的最大数字所在下标

        sort(candidates.begin(), candidates.end());

        // 确定组合的最大数字[10/7/6/5/2/1]
        while (maxCanIndex >= 0) {

            if (candidates[maxCanIndex] > target || candidates[maxCanIndex] == lastMaxVal) {
                --maxCanIndex;
                continue;
            }
            choseFlag[maxCanIndex] = true;
            lastMaxVal = candidates[maxCanIndex];
            leftTarget = target - candidates[maxCanIndex];
            minCanIndex = maxCanIndex;
            lastHuiSuNum = -1;

            // 直至最大数字个个数为0
            while (choseFlag[maxCanIndex]) {

                // 用最大数贪心凑
                if (!choseFlag[minCanIndex] && lastHuiSuNum != candidates[minCanIndex] && leftTarget >= candidates[minCanIndex]) {
                    choseFlag[minCanIndex] = true;
                    leftTarget -= candidates[minCanIndex];
                }

                // 若能整凑，则记录组合
                if (leftTarget == 0) {
                    // 构建 tmp 输出
                    for (int i = minCanIndex; i <= maxCanIndex; ++i) {
                        if (choseFlag[i]) {
                            tmp.push_back(candidates[i]);
                        }
                    }
                    ans.push_back(tmp);
                    tmp.clear();
                    vector<int>().swap(tmp);
                    if (minCanIndex != 0) {
                        choseFlag[minCanIndex] = false;
                        lastHuiSuNum = candidates[minCanIndex];
                        leftTarget += candidates[minCanIndex];
                        while (minCanIndex > 0 && candidates[minCanIndex] == candidates[minCanIndex - 1]) {
                            --minCanIndex;
                        }
                    }
                }

                // 若不能整凑，且已到最小下标0，回溯
                if (minCanIndex == 0) {
                    if (choseFlag[minCanIndex]) {
                        leftTarget += candidates[minCanIndex];
                        choseFlag[minCanIndex++] = false;
                    }
                    if (minCanIndex > maxCanIndex) {
                        break;
                    }
                    while (minCanIndex < maxCanIndex && !choseFlag[minCanIndex]) {
                        ++minCanIndex;
                    }
                    if (choseFlag[minCanIndex]) {
                        leftTarget += candidates[minCanIndex];
                        lastHuiSuNum = candidates[minCanIndex];
                    }
                    choseFlag[minCanIndex] = false;
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
    int arr[] = {10,1,2,7,6,1,5};
    int target = 8;
    vector<int> candidates(arr, arr + sizeof(arr) / sizeof(int));
    vector<vector<int>> result = solution.combinationSum2(candidates, target);
    printVec2D(result);
    return 0;
}