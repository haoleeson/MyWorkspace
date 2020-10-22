/**
 * No763. 划分字母区间
 * 字符串 S 由小写字母组成。我们要把这个字符串划分为尽可能多的片段，同一个字母只会出现在其中的一个片段。返回一个表示每个字符串片段的长度的列表。

示例 1：
输入：S = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为 "ababcbaca", "defegde", "hijhklij"。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 的划分是错误的，因为划分的片段数较少。

提示：
S的长度在[1, 500]之间。
S只包含小写字母 'a' 到 'z' 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/partition-labels
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <string>
#include "myTools.h"
using namespace std;

/**
 * 解题思路：划分片段尽可能多，每个片段的字符尽可能少
 * 暴力 O(n^2)
 */
class Solution {
public:
    vector<int> partitionLabels(string S) {
        vector<int> lastChIndex(26, 0);
        vector<int> ans;
        int startIndex = 0, endIndex, len = S.length(), i;
        // 统计每个字符最后出现的下标（逆序最先出现）
        for (i = len - 1; i >= 0; --i) {
            if (lastChIndex[S[i] - 'a'] == 0) {
                lastChIndex[S[i] - 'a'] = i;
            }
        }

        while (startIndex < len) {
            endIndex = startIndex;
            for (i = startIndex; i <= endIndex; ++i) {
                if (lastChIndex[S[i] - 'a'] > endIndex) {
                    endIndex = lastChIndex[S[i] - 'a'];
                }
            }
            ans.push_back(endIndex - startIndex + 1);
            startIndex = endIndex + 1;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    string strs[] = {
            "ababcbacadefegdehijhklij",// 9,7,8
    };
    for (string str : strs) {
        vector<int> result = solution.partitionLabels(str);
        MyTools::printVec(result);
    }
    return 0;
}
