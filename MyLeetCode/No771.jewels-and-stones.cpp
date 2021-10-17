#include <iostream>
using namespace std;

/**
 * No771. 宝石与石头
 * 给定字符串J代表石头中宝石的类型，和字符串S代表你拥有的石头。S中每个字符代表了一种你拥有的石头的类型，你想知道你拥有的石头中有多少是宝石。

J中的字母不重复，J和S中的所有字符都是字母。字母区分大小写，因此"a"和"A"是不同类型的石头。

示例 1:

输入: J = "aA", S = "aAAbbbb"
输出: 3

示例 2:
输入: J = "z", S = "ZZ"
输出: 0

注意:
S和J最多含有50个字母。
J中的字符不重复。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/jewels-and-stones
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */

class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int ans = 0;
        int counts[52] = {0};
        // count
        for (char ch : S) {
            if (ch >= 'a' && ch <= 'z') {
                ++counts[ch - 'a' + 26];
            } else if (ch >= 'A' && ch <= 'Z') {
                ++counts[ch - 'A'];
            }
        }
        // calc
        for (char ch : J) {
            if (ch >= 'a' && ch <= 'z') {
                ans += counts[ch - 'a' + 26];
            } else if (ch >= 'A' && ch <= 'Z') {
                ans += counts[ch - 'A'];
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    string J = "aA";
    string S = "aAAbbbb";
    cout << solution.numJewelsInStones(J, S) << endl;
    return 0;
}