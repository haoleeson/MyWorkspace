#include <iostream>
#include <vector>
using namespace std;

/**
 * No216. 组合总和 III （回溯 、dfs）
 * 找出所有相加之和为 n 的 k个数的组合。组合中只允许含有 1-9 的正整数，并且每种组合中不存在重复的数字。
 * 说明：
 * 所有数字都是正整数。
 * 解集不能包含重复的组合。

示例 1:
输入: k = 3, n = 7
输出: [[1,2,4]]

示例 2:
输入: k = 3, n = 9
输出: [[1,2,6], [1,3,5], [2,3,4]]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/combination-sum-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

/**
 * 方法2：回溯
 * 力扣用例执行用时：0ms
 * 力扣用例内存消耗：6.3MB
 */
class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> ans;
        vector<int> tmp(k, 0);
        // [0, i]的累加和
        int nSum[10] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
        bool choseFlag[10]{false};
        int leftN, iterator, num, maxNum = 9;

        // 逐一确定最大值[9/8/7/6/.../1]
        while (maxNum) {
            // 加速，最小组合仍大于n
            if (maxNum + nSum[k - 1] > n) {
                --maxNum;
                continue;
            }
            // 终止，最大组合仍小于 n
            if (maxNum < k || nSum[maxNum] - nSum[maxNum - k] < n) {
                break;
            }
            leftN = n - maxNum;
            iterator = k - 1;
            choseFlag[maxNum] = true;
            tmp[k - 1] = maxNum;
            num = maxNum - 1;

            while (choseFlag[maxNum]) {
                if (num + nSum[iterator - 1] <= leftN && (num < iterator || nSum[num] - nSum[num - iterator] >= leftN)) {
                    choseFlag[num] = true;
                    tmp[--iterator] = num;
                    leftN -= num;

                    if (iterator == 0) {
                        if (leftN == 0) {
                            ans.push_back(tmp);
                        }
                        choseFlag[num] = false;
                        ++iterator;
                        leftN += num;
                    }
                }

                // 已到最小下标0 或 leftN 提前到0，回溯
                if (num == 1 || leftN <= 0) {
                    if (num == 1 && choseFlag[1]) {
                            leftN += 1;
                            ++iterator;
                            choseFlag[1] = false;
                    }
                    while (num <  maxNum && !choseFlag[num]) {
                        ++num;
                    }
                    choseFlag[num] = false;
                    ++iterator;
                    leftN += num;
                }
                // 若不能整凑，但未到最小下标，则继续下探
                --num;
            }
            --maxNum;
        }
        return ans;
    }
};

/**
 * 方法1：dfs
 * 力扣用例执行用时：4ms
 * 力扣用例内存消耗：6.7MB
 */
class Solution1 {
public:
    bool m_choseFlag[10]{false};
    vector<vector<int>> m_ans;

    void dfs(vector<int>& tmp, int k, int n, int lastNum) {
        if (k == 0 || n < 0) {
            if (n == 0 && k == 0) {
                m_ans.push_back(tmp);
            }
            return;
        }

        for (int i = lastNum - 1; i > 0; --i) {
            if (!m_choseFlag[i] && i <= n) {
                m_choseFlag[i] = true;
                tmp[k - 1] = i;
                dfs(tmp, k - 1, n - i, i);
                m_choseFlag[i] = false;
            }
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> tmp(k, 0);
        dfs(tmp, k, n, 10);
        return m_ans;
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
    int k = 4;
    int n = 24;
    vector<vector<int>> result = solution.combinationSum3(k, n);
    printVec2D(result);
    return 0;
}