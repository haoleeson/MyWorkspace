/**
 * No1002. 查找常用字符
 * 给定仅有小写字母组成的字符串数组 A，返回列表中的每个字符串中都显示的全部字符（包括重复字符）组成的列表。
 * 例如，如果一个字符在每个字符串中出现 3 次，但不是 4 次，则需要在最终答案中包含该字符 3 次。

你可以按任意顺序返回答案。

示例 1：
输入：["bella","label","roller"]
输出：["e","l","l"]

示例 2：
输入：["cool","lock","cook"]
输出：["c","o"]

提示：
1 <= A.length <= 100
1 <= A[i].length <= 100
A[i][j] 是小写字母

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/find-common-characters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include "myTools.h"
using namespace std;

class Solution {
    string CHAR_TAB[26] = {
            "a", "b", "c", "d", "e",
            "f", "g", "h", "i", "j",
            "k", "l", "m", "n", "o",
            "p", "q", "r", "s", "t",
            "u", "v", "w", "x", "y",
            "z"};
public:
    vector<string> commonChars(vector<string>& A) {
        vector<string> ans;
        int size = A.size();
        int* miniCharCnt = new int[26];
        int* tmpCnt = new int[26];
        for (int i = 0; i < 26; ++i) {
            miniCharCnt[i] = INT32_MAX;
        }

        // 统计
        for (int i = 0, j; i < size; ++i) {
            // 统计每个字符串字符数
            for (j = 0; j < 26; ++j) {
                tmpCnt[j] = 0;
            }
            for (char ch : A[i]) {
                ++tmpCnt[ch - 'a'];
            }
            // 汇总每个字符的最小统计数值
            for (j = 0; j < 26; ++j) {
                if (tmpCnt[j] < miniCharCnt[j]) {
                    miniCharCnt[j] = tmpCnt[j];
                }
            }
        }

        // 输出
        for (int i = 0; i < 26; ++i) {
            while (miniCharCnt[i]--) {
                ans.push_back(CHAR_TAB[i]);
            }
        }
        delete []miniCharCnt;
        delete []tmpCnt;
        return ans;
    }
};

int main() {
    Solution solution;
    string arr[] = {
        "bella",
        "label",
        "roller"
    };
    vector<string> A (arr, arr + 3);
    vector<string> result = solution.commonChars(A);
    MyTools::printVec(result);
    return 0;
}
