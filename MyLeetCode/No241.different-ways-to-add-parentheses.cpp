#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 官解思路：动态规划
// 链接：https://leetcode.cn/problems/different-ways-to-add-parentheses/solution/wei-yun-suan-biao-da-shi-she-ji-you-xian-lyw6/

class Solution {
public:
    vector<int> diffWaysToCompute(string expression) {
        // 获取数字和操作符
        vector<int> ops;
        obtainNumsAndExps(expression, ops);
        int opsSize = ops.size();

        // dpTab[l][r] 表示表达式 ops[l : r] 能产生的所有结果
        vector<vector<vector<int>>> dpTab(opsSize, vector<vector<int>>(opsSize));
        // 初始化不包含运算符时，其结果为自身数字
        for (int i = 0; i < opsSize; i += 2) {
            dpTab[i][i] = {ops[i]};
        }

        // 遍历表达式元素长度
        for (int opsLen = 3; opsLen <= opsSize; opsLen++) {
            // 遍历表达式的起始下标
            for (int j = 0; j <= opsSize - opsLen; j += 2) {
                int l = j;
                int r = j + opsLen - 1;
                // 遍历分割计算符的下标， [i : j] 之间
                for (int k = j + 1; k < r; k += 2) {
                    auto& left = dpTab[l][k - 1];
                    auto& right = dpTab[k + 1][r];
                    // 遍历 分割计算符 左右两边所有可能解（组合）
                    for (auto& num1 : left) {
                        for (auto& num2 : right) {
                            if (ops[k] == ADDITION) {
                                dpTab[l][r].push_back(num1 + num2);
                            } else if (ops[k] == SUBTRACTION) {
                                dpTab[l][r].push_back(num1 - num2);
                            } else if (ops[k] == MULTIPLICATION) {
                                dpTab[l][r].push_back(num1 * num2);
                            }
                        }
                    }
                }
            }
        }

        // 最终返回 dpTab[0 : opsSize - 1] 全量表达式元素的结果
        return dpTab[0][opsSize - 1];
    }

private:
    // 运算符表示
    const int ADDITION = -1;       // +
    const int SUBTRACTION = -2;    // -
    const int MULTIPLICATION = -3; // *

    // 获取数字和操作符
    void obtainNumsAndExps(const string& s, vector<int>& ops) {
        size_t i = 0, lenS = s.length();
        int num = 0;

        while (i < lenS) {
            // 若为数字字符
            if (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + s[i] - '0';
            } else {
                // 存数字
                ops.push_back(num);
                // 存操作符
                int opExp;
                switch (s[i]) {
                    case '+':
                        opExp = ADDITION;
                        break;
                    case '-':
                        opExp = SUBTRACTION;
                        break;
                    case '*':
                        opExp = MULTIPLICATION;
                        break;
                    default:
                        break;
                }
                ops.push_back(opExp);
                num = 0;
            }
            ++i;
        }
        // 存最后一个数字
        ops.push_back(num);
    }
};

class Solution0 {
public:
    vector<int> diffWaysToCompute(string expression) {
        int len = expression.length();

        vector<int> res;
        vector<int> ops;
        vector<char> exps;
        obtainNumsAndExps(expression, ops, exps);

        return res;
    }

private:
    void obtainNumsAndExps(const string& s, vector<int>& ops, vector<char>& exps) {
        size_t i = 0, lenS = s.length();
        int num = 0;

        while (i < lenS) {
            // 数字字符
            if (s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + s[i] - '0';
            } else {
                // 存数字
                ops.push_back(num);
                // 存操作符
                exps.push_back(s[i]);
                num = 0;
            }
            ++i;
        }
        // 存最后一个数字
        ops.push_back(num);
    }

    // 无校验字符转数字
    int str2int(string& s, int startI, int endI) {
        int num = 0;
        for (int i = startI; i <= endI; ++i) {
            num = num * 10 + s[i] - '0';
        }
        return num;
    }

    // 计算
    int calc(string& s, int index) {
        int lenS = s.length();

        // 获取前后数字
        int numBefore = 0, numAfter = 0;
        for (int i = max(0, index - 2); i < index; ++i) {
            if (s[i] < '0' || s[i] > '9') {
                continue;
            }
            numBefore = numBefore * 10 + s[i] - '0';
        }
        for (int i = index + 1; i < min(lenS, index + 3); ++i) {
            if (s[i] < '0' || s[i] > '9') {
                continue;
            }
            numAfter = numAfter * 10 + s[i] - '0';
        }

        int res = 0;
        switch (s[index]) {
            case '+': {
                res = numBefore + numAfter;
                break;
            }
            case '-': {
                res = numBefore - numAfter;
                break;
            }
            case '*': {
                res = numBefore * numAfter;
                break;
            }
            default: {
                res = 0;
            }
        }
        return res;
    }
};

int main(void) {
    Solution solution;

    string expression1 = "2-1-1";
    vector<int> res1 = solution.diffWaysToCompute(expression1);
    MyTools::printVec(res1);

    string expression2 = "2*3-4*5";
    vector<int> res2 = solution.diffWaysToCompute(expression2);
    MyTools::printVec(res2);

    return 0;
}
