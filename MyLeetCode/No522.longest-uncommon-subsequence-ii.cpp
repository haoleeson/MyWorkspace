#include <iostream>
#include <vector>

using namespace std;

// 官解思路：对于给定的某个字符串 str[i]，如果它的一个子序列 sub 是「特殊序列」，那么 str[i] 本身也是一个「特殊序列」。
// 这是因为假设 sub 没有在除了 str[i] 之外的字符串中以子序列的形式出现过，那么给 sub 不断地添加字符，它也不会出现。而
// str[i] 就是 sub 添加若干个（可以为零个）字符得到的结果。
//
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        int lenV = strs.size(), res = -1;

        for (int i = 0; i < lenV; ++i) {
            bool notAnySubStr = true;
            int lenI = strs[i].size();

            // 判断 strs[i] 是否为 strs[j] 的子序列（贪心 + 双指针）
            for (int j = 0; j < lenV; ++j) {
                // 非特殊字串，无需再继续判断
                if (i != j && isSubStr(strs[i], strs[j])) {
                    notAnySubStr = false;
                    break;
                }
            }

            // str[i] 不为其他字符串的子串
            if (notAnySubStr) {
                res = max(res, lenI);
            }
        }

        return res;
    }

private:
    // 判断 s 是否为 t 的子串（贪心 + 双指针）
    inline bool isSubStr(const string& s, const string& t) {
        int lenS = s.size(), lenT = t.size();
        if (lenS > lenT) {
            return false;
        }

        int ptrS = 0, ptrT = 0;
        while (ptrS < lenS && ptrT < lenT) {
            if (s[ptrS] == t[ptrT]) {
                ++ptrS;
            }
            ++ptrT;
        }

        return ptrS == lenS;
    }
};

int main(void) {
    Solution solution;
    string arr1[] = {"aba", "cdc", "eae"};
    vector<string> strs1(arr1, arr1 + sizeof(arr1) / sizeof(string));
    int res1 = solution.findLUSlength(strs1);
    cout << res1 << endl;

    string arr2[] = {"aaa", "aaa", "aa"};
    vector<string> strs2(arr2, arr2 + sizeof(arr2) / sizeof(string));
    int res2 = solution.findLUSlength(strs2);
    cout << res2 << endl;
    return 0;
}
