//
// Created by eisenhao on 2022/6/24.
//

#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// 解法：等概率映射替换
// 设黑名单大小为 m，则每个非黑名单数的概率为 1/(n-m)
// 只需生成 [0, n-m) 的随机数，并将其中的黑名单数字恰好地映射到[n-m,n)的白名单数字即可
class Solution {
public:
    Solution(int n, vector<int>& blacklist) {
        int m = blacklist.size();
        bound = n - m;

        // 暂存黑名单中 大于 n-m 的黑名单数（需根据其得到 [n-m,n) 的白名单集合）
        unordered_set<int> blackNums;
        for (int num : blacklist) {
            if (num >= bound) {
                blackNums.emplace(num);
            }
        }

        // 将 [0, n-m) 中的黑名单数 映射到 [n-m, n) 的白名单数
        int num = bound;
        for (int i : blacklist) {
            if (i < bound) {
                // 恰好地依次映射到 [n-m,n) 中的所有白名单数字（跳过[n-m,n) 中的黑名单数）
                while (blackNums.count(num)) {
                    num++;
                }
                blackToWriteMap[i] = num++;
            }
        }
    }

    int pick() {
        int x = rand() % bound;
        return blackToWriteMap.count(x) ? blackToWriteMap[x] : x;
    }

private:
    // [0,n-m) 之间的黑名单数字到 [n-m, n] 的白名单数字之间的映射
    unordered_map<int, int> blackToWriteMap;
    int bound;
};

int main(void) {
    int arr1[] = {2, 3, 5};
    vector<int> blacklist(arr1, arr1 + sizeof(arr1) / sizeof(int));
    Solution solution(7, blacklist);

    cout << solution.pick() << endl;
    cout << solution.pick() << endl;
    cout << solution.pick() << endl;
    cout << solution.pick() << endl;
    cout << solution.pick() << endl;
    cout << solution.pick() << endl;
    cout << solution.pick() << endl;
    return 0;
}
