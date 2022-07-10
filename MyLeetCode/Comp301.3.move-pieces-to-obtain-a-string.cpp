#include <string.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 思路：去掉 '_' 比较两者是否相等
// 链接：https://leetcode.cn/problems/move-pieces-to-obtain-a-string/solution/nao-jin-ji-zhuan-wan-pythonjavacgo-by-en-9sqt/
class Solution {
public:
    bool canChange(string& start, string& target) {
        // 比较去掉 '_' 后的剩余字符（由于'L'与'R'彼此无法跨越），若不同肯定无法通过移动得到
        auto s = start, t = target;
        s.erase(remove(s.begin(), s.end(), '_'), s.end());
        t.erase(remove(t.begin(), t.end(), '_'), t.end());
        if (s != t) return false;

        // 双指针遍历 start[i]，target[j] （只需在意 'L' 与 'R'）
        for (int i = 0, j = 0; i < start.length(); ++i) {
            if (start[i] == '_') continue;
            while (target[j] == '_') ++j;
            // 如果当前字符为 L 且 i<j （即：目标'L'左侧有'_'，而左侧这个'_'无法通过'L'右移得到），返回 false；
            // 如果当前字符为 R 且 i>j（即：目标'R'右侧有'_'，而右侧这个'_'无法通过'R'左移得到），返回 false。
            if (i != j && (start[i] == 'L') != (i > j)) return false;
            ++j;
        }
        return true;
    }
};

class Solution0 {
public:
    bool canChange(string start, string target) {
        int len = start.length();

        // 统计 start 反序值
        int startNegR = 0, startNegL = 0;
        int startCntL = 0, startCntR = 0;
        int cntSpace = 0, startSpaceR = 0, startSpaceL = 0;
        for (char ch : start) {
            if (ch == '_') {
                ++cntSpace;
            } else if (ch == 'R') {
                ++startCntR;
                if (cntSpace) {
                    startSpaceR = cntSpace;
                }
            } else if (ch == 'L' && startCntR) {
                startNegR += startCntR;
            }
        }
        cntSpace = 0;
        for (int i = len - 1; i > -1; --i) {
            if (start[i] == '_') {
                ++cntSpace;
            } else if (start[i] == 'L') {
                ++startCntL;
                if (cntSpace) {
                    startSpaceL = cntSpace;
                }
            } else if (start[i] == 'R' && startCntL) {
                startNegL += startCntL;
            }
        }

        // 统计 target 反序值
        int targetNegR = 0, targetNegL = 0;
        int targetCntL = 0, targetCntR = 0;
        int targetSpaceR = 0, targetSpaceL = 0;
        cntSpace = 0;
        for (char ch : target) {
            if (ch == '_') {
                ++cntSpace;
            } else if (ch == 'R') {
                ++targetCntR;
                if (cntSpace) {
                    targetSpaceR = cntSpace;
                }
            } else if (ch == 'L' && targetCntR) {
                targetNegR += targetCntR;
            }
        }
        cntSpace = 0;
        for (int i = len - 1; i > -1; --i) {
            if (target[i] == '_') {
                ++cntSpace;
            } else if (target[i] == 'L') {
                ++targetCntL;
                if (cntSpace) {
                    targetSpaceL = cntSpace;
                }
            } else if (target[i] == 'R' && targetCntL) {
                targetNegL += targetCntL;
            }
        }

        // 数量不对
        if (startCntL != targetCntL || startCntR != targetCntR) {
            return false;
        }
        // 反序统计不对
        if (startNegL != targetNegL || startNegR != targetNegR) {
            return false;
        }
        if (startSpaceL > targetSpaceL || startSpaceR > targetSpaceR) {
            return false;
        }

        return true;
    }
};

int main(void) {
    Solution solution;
    string start1 = "_L__R__R_";
    string target1 = "L______RR";
    bool res1 = solution.canChange(start1, target1);
    cout << res1 << endl;

    string start2 = "R_L_";
    string target2 = "__LR";
    bool res2 = solution.canChange(start2, target2);
    cout << res2 << endl;

    string start3 = "_R";
    string target3 = "R_";
    bool res3 = solution.canChange(start3, target3);
    cout << res3 << endl;

    return 0;
}
