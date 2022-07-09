#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// 官解：动态规划
// 链接：https://leetcode.cn/problems/length-of-longest-fibonacci-subsequence/solution/zui-chang-de-fei-bo-na-qi-zi-xu-lie-de-c-8trz/
class Solution {
public:
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();

        // 记录 <所有数, 其下标> ，方便下方找 arr[k] 时快速查询
        unordered_map<int, int> indices;
        for (int i = 0; i < n; i++) {
            indices[arr[i]] = i;
        }

        // dp[j][i] 表示 以 arr[j], arr[i] 结尾的斐波那契数列的最大长度
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int ans = 0;

        // 遍历 arr[i]、arr[j] （由于性质 arr[k] + arr[j] = arr[i]，故只需找 2 arr[j] > arr[i]）
        for (int i = 2; i < n; ++i) {
            for (int j = i - 1; j >= 0 && arr[j] * 2 > arr[i]; --j) {
                // 找是否存在倒数第三位数 arr[k]，与 arr[j], arr[i] 构成斐波那契数列 （arr[k] = arr[i] - arr[j]）
                int k = -1;
                if (indices.count(arr[i] - arr[j])) {
                    k = indices[arr[i] - arr[j]];
                }
                // 若存在，更新 dp[j][i] 为 dp[k][j] + 1（表示：以 arr[j],arr[i] 结尾的斐波那契序列长度 为
                // 以 arr[k],arr[k] 结尾的斐波那契子序列长度 + 1
                if (k > -1) {
                    dp[j][i] = max(dp[k][j] + 1, 3);
                    if (dp[j][i] > ans) {
                        ans = dp[j][i];
                    }
                }
            }
        }
        return ans;
    }
};

int main(void) {
    Solution solution;

    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> arr1(a1, a1 + sizeof(a1) / sizeof(int));
    int res1 = solution.lenLongestFibSubseq(arr1);
    cout << res1 << endl;

    int a2[] = {1, 3, 7, 11, 12, 14, 18};
    vector<int> arr2(a2, a2 + sizeof(a2) / sizeof(int));
    int res2 = solution.lenLongestFibSubseq(arr2);
    cout << res2 << endl;

    return 0;
}
