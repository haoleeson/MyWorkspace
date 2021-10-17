/**
 * 重排字符
 * 编写一个程序，将输入字符串中的字符按如下规则排序：
 * 规则1：英文字母从 A 到 Z 排列，不区分大小写。如，输入: Type 输出:epTy
 * 规则2：同一个英文字母的大小同时存在时，按照输入顺序排列（稳定）。如输入:BabA 输出aABb
 * 规则3：非英文字母的其它字符保持原来的位置。如，输入:By?e 输出:Be?y
示例：
 输入：
 A Famous Saying: Much Ado About Nothing (2012/8).
 输出：
 A aaAAbc dFgghh: iimM nNn oooos Sttuuuy (2012/8).
 */
#include <iostream>
using namespace std;

/**
 * 无法保证字母有序（稳定）
 * 时间复杂度：O(n^2)
 */
class Solution1 {
    int charVal(char ch) {
        if (ch >= 'A' && ch <= 'Z') {
            return ch - 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            return ch - 'a';
        }
        return -1;
    }
public:
    string reOrder(string& str) {
        char tmp, chI, chJ;
        // 处理
        int len = str.length();
        for (int i = len - 1; i >= 0; --i) {
            if ((chI = charVal(str[i])) == -1) {
                continue;
            }
            for (int j = i - 1; j >= 0; --j) {
                if ((chJ = charVal(str[j])) == -1) {
                    continue;
                }
                if (chJ > chI) {
                    tmp = str[i];
                    str[i] = str[j];
                    str[j] = tmp;
                    chI = chJ;
                }
            }
        }
        return str;
    }
};

/**
 * 时间复杂度：O(k * n), k为常数26
 */
class Solution {
public:
    string reOrder(string& str) {
        string ans = str;
        bool flag[26]{false};
        int iterator = 0, len = str.length();
        int *val = new int[len]{0};

        // 计算每个字母对应的数值（忽略大小写）
        for (char ch : str) {
            if (ch >= 'A' && ch <= 'Z') {
                flag[ch - 'A'] = true;
                val[iterator++] = ch - 'A';
            } else if (ch >= 'a' && ch <= 'z') {
                flag[ch - 'a'] = true;
                val[iterator++] = ch - 'a';
            } else {
                val[iterator++] = -1;
            }
        }

        // 将26个字母顺序填充
        iterator = 0;
        for (int i = 0; i < 26; ++i) {
            if (!flag[i]) {
                continue;
            }
            for (int j = 0; j < len; ++j) {
                if (val[j] == i) {
                    while (val[iterator] == -1) {
                        ++iterator;
                    }
                    ans[iterator++] = str[j];
                }
            }
        }
        delete []val;
        return ans;
    }
};

int main() {
    Solution solution;
    string strs[] = {
            "Type",
            "BabA",
            "By?e",
            "A Famous Saying: Much Ado About Nothing (2012/8)."
    };

    // 输出
    for (int i = 0; i < 4; ++i) {
        cout << strs[i] << endl;
        cout << solution.reOrder(strs[i]) << endl << endl;
    }
    return 0;
}
