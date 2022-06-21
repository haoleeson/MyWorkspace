#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


// 官解 O(NlogN)动态规划
//作者：LeetCode-Solution
//        链接：https://leetcode.cn/problems/russian-doll-envelopes/solution/e-luo-si-tao-wa-xin-feng-wen-ti-by-leetc-wj68/
//来源：力扣（LeetCode）
//著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int len = envelopes.size();
        if (len == 0) {
            return 0;
        }

        sort(envelopes.begin(), envelopes.end(), [](const auto& e1, const auto& e2) {
            return e1[0] == e2[0] ? e1[1] > e2[1] : e1[0] < e2[0];
        });

        vector<int> f = {envelopes[0][1]};
        for (int i = 1; i < len; ++i) {
            int num = envelopes[i][1];
            if ( num > f.back()) {
                f.push_back(num);
            }
            else {
                auto it = lower_bound(f.begin(), f.end(), num);
                *it = num;
            }
        }
        return f.size();
    }
};


// O(n^2)动态规划，超时
class Solution0 {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int len = envelopes.size();
        if (len == 0) {
            return 0;
        }

        int maxSubLen = 1;

        // 按宽度升序，高度降序排序
        sort(envelopes.begin(), envelopes.end(), cmpFunc);

        /** 对高度求最长子序列，动态规划 O(n^2) **/
        // 定义 dpTab：为以 envelopes 高度[i] 结尾的最长子序列 长度
        int* dpTab = new int[len];
        for (int i = 0; i < len; ++i) {
            dpTab[i] = 1;
        }

        for (int i = 1; i < len; ++i) {
            for (int j = 0; j < i; ++j) {
                if (envelopes[j][1] < envelopes[i][1] && dpTab[j] + 1 > dpTab[i]) {
                    dpTab[i] = dpTab[j] + 1;
                    if (dpTab[i] > maxSubLen) {
                        maxSubLen = dpTab[i];
                    }
                }
            }
        }

        return maxSubLen;
    }

private:
    static bool cmpFunc(vector<int>&a, vector<int>&b) {
        return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
    }
};

int main(void) {
    Solution solution;
    int arr1[][2] = {{5,4}, {6,4}, {6,7}, {2,3}};
    int len1 = sizeof(arr1)/ sizeof(arr1[0]);
    vector<vector<int>> envelopes1;
    for (int i = 0; i < len1; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + sizeof(arr1[i]) / sizeof(int));
        envelopes1.push_back(tmp);
    }
    cout << solution.maxEnvelopes(envelopes1) << endl;

    int arr2[][2] = {{1,1}, {1,1}, {1,1}};
    int len2 = sizeof(arr2)/ sizeof(arr2[0]);
    vector<vector<int>> envelopes2;
    for (int i = 0; i < len2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + sizeof(arr2[i]) / sizeof(int));
        envelopes2.push_back(tmp);
    }
    cout << solution.maxEnvelopes(envelopes2) << endl;

    return 0;
}
