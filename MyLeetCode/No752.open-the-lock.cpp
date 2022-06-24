//
// Created by eisenhao on 2022/6/24.
//

#include <iostream>
#include <queue>
#include <set>

#include "myTools.h"
using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        int step = 0, sz;
        queue<string> q;
        q.push("0000");

        set<string> s;
        for (auto& str : deadends) {
            s.insert(str);
        }

        while (!q.empty()) {
            // 遍历上一步记录的的所有可能解
            sz = q.size();
            for (int i = 0; i < sz; ++i) {
                string str = q.front();
                q.pop();

                // 若是死亡数字或已遍历过，跳过
                if (s.count(str)) {
                    continue;
                }

                if (str == target) {
                    return step;
                }

                // 找它下一种可能的数字 第 j 位加减
                for (int j = 0; j < 4; ++j) {
                    // 第 j 位加一
                    string str1(str);
                    if (str1[j] >= '0' && str1[j] < '9') {
                        str1[j]++;
                    } else if (str1[j] == '9') {
                        str1[j] = '0';
                    }
                    // 若是死亡数字或已遍历过，不添加
                    if (!s.count(str1)) {
                        q.push(str1);
                    }

                    // 第 j 位减一
                    string str2(str);
                    if (str2[j] > '0' && str2[j] <= '9') {
                        str2[j]--;
                    } else if (str2[j] == '0') {
                        str2[j] = '9';
                    }
                    // 若是死亡数字或已遍历过，不添加
                    if (!s.count(str2)) {
                        q.push(str2);
                    }
                }

                // 将已遍历的数字加入死亡数组，防止重复遍历
                s.insert(str);
            }
            ++step;
        }

        // 未找到
        return -1;
    }
};

int main(void) {
    Solution solution;
    string arr1[] = {"0201", "0101", "0102", "1212", "2002"};
    string target1 = "0202";
    vector<string> deadends1(arr1, arr1 + sizeof(arr1) / sizeof(string));
    int res1 = solution.openLock(deadends1, target1);
    cout << res1 << endl;

    string arr2[] = {"8888"};
    string target2 = "0009";
    vector<string> deadends2(arr2, arr2 + sizeof(arr2) / sizeof(string));
    int res2 = solution.openLock(deadends2, target2);
    cout << res2 << endl;

    string arr3[] = {"8887", "8889", "8878", "8898", "8788", "8988", "7888", "9888"};
    string target3 = "8888";
    vector<string> deadends3(arr3, arr3 + sizeof(arr3) / sizeof(string));
    int res3 = solution.openLock(deadends3, target3);
    cout << res3 << endl;
    return 0;
}
