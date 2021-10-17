#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * No17. 电话号码的字母组合（dfs）
 * 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

            2(abc)      3(def)
 4(ghi)     5(jkl)      6(mno)
 7(pqrs)    8(tuv)      9(wxyz)

示例:
输入："23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].

说明:
尽管上面的答案是按字典序排列的，但是你可以任意选择答案输出的顺序。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/letter-combinations-of-a-phone-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    vector<string> m_ans;
    int m_len = 0;
    string m_combineStr = "";
    void dfs(int currIndex, string& digits) {
        // 结束标志
        if (currIndex == m_len) {
            m_ans.push_back(m_combineStr);
        }

        // 根据数字映射字母
        switch (digits[currIndex]) {
            case '2':
                m_combineStr[currIndex] = 'a';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'b';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'c';
                dfs(currIndex + 1, digits);
                break;
            case '3':
                m_combineStr[currIndex] = 'd';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'e';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'f';
                dfs(currIndex + 1, digits);
                break;
            case '4':
                m_combineStr[currIndex] = 'g';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'h';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'i';
                dfs(currIndex + 1, digits);
                break;
            case '5':
                m_combineStr[currIndex] = 'j';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'k';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'l';
                dfs(currIndex + 1, digits);
                break;
            case '6':
                m_combineStr[currIndex] = 'm';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'n';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'o';
                dfs(currIndex + 1, digits);
                break;
            case '7':
                m_combineStr[currIndex] = 'p';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'q';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'r';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 's';
                dfs(currIndex + 1, digits);
                break;
            case '8':
                m_combineStr[currIndex] = 't';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'u';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'v';
                dfs(currIndex + 1, digits);
                break;
            case '9':
                m_combineStr[currIndex] = 'w';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'x';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'y';
                dfs(currIndex + 1, digits);
                m_combineStr[currIndex] = 'z';
                dfs(currIndex + 1, digits);
                break;
        }
    }
    
    vector<string> letterCombinations(string digits) {
        m_len = digits.length();
        m_combineStr = digits;
        if (m_len > 0) {
            dfs(0, digits);
        }
        return m_ans;
    }
};

void printVector(vector<string> vector) {
    int size = vector.size();
    cout << "total size = " << size << endl;
    cout << "[";
    for (int i = 0; i < vector.size() - 1; ++i) {
        cout << "\"" << vector[i] << "\", ";
    }
    cout << "\"" << vector[size - 1] << "\"]." << endl;
}

int main() {
    Solution solution;
    string inputStr = "23";

    vector<string> result = solution.letterCombinations(inputStr);
    printVector(result);

    return 0;
}
