#include <iostream>
#include <vector>
using namespace std;

/**
 * No22. 括号生成（dfs）
 * 数字 n代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例：
输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/generate-parentheses
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

class Solution {
public:
    vector<string> m_ans;
    char* m_charBuf;
    int m_n;
    int m_len;

    void dfs(int leftCnt, int rightCnt, int index) {
        if (index == m_len - 1) {
            string str(m_charBuf, m_len);
            m_ans.push_back(str);
            return;
        }
        if (leftCnt < m_n) {
            m_charBuf[index] = '(';
            dfs(leftCnt + 1, rightCnt, index + 1);
        }
        if (leftCnt > rightCnt) {
            m_charBuf[index] = ')';
            dfs(leftCnt, rightCnt + 1, index + 1);
        }
    }

    vector<string> generateParenthesis(int n) {
        if (n < 2) {
            vector<string> ans1(1, "()");
            return (n == 1) ? ans1 : m_ans;
        }
        m_n = n;
        m_len = n * 2;
        m_charBuf = new char[m_len]{0};
        m_charBuf[0] = '(';
        m_charBuf[m_len - 1] = ')';

        dfs(1, 0, 1);
        return m_ans;
    }
};

template<typename T>
void printVec(vector<T> vec) {
    int size = vec.size();
    cout << "[" << endl;
    if (size > 0) {
        cout << "\" " << vec[0] << "\"";
    }
    for (int i = 1; i < size; ++i) {
        cout << "," << endl << " \"" << vec[i] << "\"";
    }
    cout << endl << "]" << endl;
    return;
}

int main() {
    Solution solution;
    int n = 3;
    vector<string> result = solution.generateParenthesis(n);
    printVec(result);
    return 0;
}
