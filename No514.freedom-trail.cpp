/**
 * No514. 自由之路 （动态规划）
 * 视频游戏“辐射4”中，任务“通向自由”要求玩家到达名为“Freedom Trail Ring”的金属表盘，并使用表盘拼写特定关键词才能开门。
 * 给定一个字符串ring，表示刻在外环上的编码；给定另一个字符串key，表示需要拼写的关键词。您需要算出能够拼写关键词中所有字符的最少步数。
 * 最初，ring的第一个字符与12:00方向对齐。您需要顺时针或逆时针旋转 ring 以使key的一个字符在 12:00 方向对齐，然后按下中心按钮，
 * 以此逐个拼写完key中的所有字符。
 * 旋转ring拼出 key 字符key[i]的阶段中：
 * 您可以将ring顺时针或逆时针旋转一个位置，计为1步。旋转的最终目的是将字符串ring的一个字符与 12:00 方向对齐，并且这个字符必须等于字
 * 符key[i] 。如果字符key[i]已经对齐到12:00方向，您需要按下中心按钮进行拼写，这也将算作1 步。按完之后，您可以开始拼写key的下一个字符（下一阶段）, 直至完成所有拼写。

示例：
输入: ring = "godding", key = "gd"
输出: 4
解释:
 对于 key 的第一个字符 'g'，已经在正确的位置, 我们只需要1步来拼写这个字符。
 对于 key 的第二个字符 'd'，我们需要逆时针旋转 ring "godding" 2步使它变成 "ddinggo"。
 当然, 我们还需要1步进行拼写。
 因此最终的输出是 4。

提示：
ring 和 key 的字符串长度取值范围均为 1 至 100；
两个字符串中都只有小写字符，并且均可能存在重复字符；
字符串key一定可以由字符串 ring旋转拼出。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/freedom-trail
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.size(), m = key.size();
        // 统计字符串环上各个字符的下标集合 O(n)
        vector<int> pos[26];
        for (int i = 0; i < n; ++i) {
            pos[ring[i] - 'a'].push_back(i);
        }
        int dp[m][n];
        memset(dp, 0x3f3f3f3f, sizeof(dp));// 0x3f3f3f3f 类比无穷大（1亿多）
        for (auto& i: pos[key[0] - 'a']) {
            dp[0][i] = min(i, n - i) + 1;
        }
        // 依次寻找每个字符
        for (int i = 1; i < m; ++i) {
            for (auto& j: pos[key[i] - 'a']) {
                for (auto& k: pos[key[i - 1] - 'a']) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][k] + min(abs(j - k), n - abs(j - k)) + 1);
                }
            }
        }
        // 找到最小值
        int minVal = dp[m - 1][0];
        for (int i = 1; i < n; ++i) {
            if (dp[m - 1][i] < minVal) {
                minVal = dp[m - 1][i];
            }
        }
        return minVal;
    }
};

/**
 * 思路1：
 * 缺陷
 */
class Solution1 {
    vector<int> m_chIndex[26];
    int m_lenRing;
    int m_nowIndex = 0;
    inline int myAbs(int val) {
        return val < 0 ? -val : val;
    }
    int minStep(char ch, int& nextIndex) {
        int miniStep = m_lenRing;
        for (int index : m_chIndex[ch - 'a']) {
            if (myAbs(m_nowIndex - index) < miniStep) {
                miniStep = myAbs(m_nowIndex - index);
                nextIndex = index;
            }
        }
        return miniStep;
    }
public:
    int findRotateSteps(string ring, string key) {
        int lenKey = key.length(), ans = lenKey, miniStep, nextIndex;
        m_lenRing = ring.length();
        // 统计字符串环上各个字符的下标集合 O(n)
        for (int i = 0; i < m_lenRing; ++i) {
            m_chIndex[ring[i] - 'a'].push_back(i);
        }

        for (char targetCh : key) {
            if (ring[m_nowIndex] == targetCh) {
                continue;
            }
            // 寻找单步的最小移动步数
            miniStep = minStep(targetCh, nextIndex);
            m_nowIndex = nextIndex;
            ans += miniStep;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    string ring = "godding", key = "gd";
    cout << solution.findRotateSteps(ring, key) << endl;
    return 0;
}
