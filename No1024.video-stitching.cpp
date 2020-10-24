/**
 * No1024. 视频拼接 （动态规划）
 * 你将会获得一系列视频片段，这些片段来自于一项持续时长为 T 秒的体育赛事。这些片段可能有所重叠，也可能长度不一。
 * 视频片段clips[i]都用区间进行表示：开始于clips[i][0]并于clips[i][1]结束。我们甚至可以对这些片段自由地再剪辑，例如片段[0, 7]
 * 可以剪切成[0, 1] +[1, 3] + [3, 7]三部分。我们需要将这些片段进行再剪辑，并将剪辑后的内容拼接成覆盖整个运动过程的片段（[0, T]）。
 * 返回所需片段的最小数目，如果无法完成该任务，则返回-1 。



示例 1：

输入：clips = [[0,2],[4,6],[8,10],[1,9],[1,5],[5,9]], T = 10
输出：3
解释：
我们选中 [0,2], [8,10], [1,9] 这三个片段。
然后，按下面的方案重制比赛片段：
将 [1,9] 再剪辑为 [1,2] + [2,8] + [8,9] 。
现在我们手上有 [0,2] + [2,8] + [8,10]，而这些涵盖了整场比赛 [0, 10]。

示例 2：
输入：clips = [[0,1],[1,2]], T = 5
输出：-1
解释：
我们无法只用 [0,1] 和 [1,2] 覆盖 [0,5] 的整个过程。

示例 3：
输入：clips = [[0,1],[6,8],[0,2],[5,6],[0,4],[0,3],[6,7],[1,3],[4,7],[1,4],[2,5],[2,6],[3,4],[4,5],[5,7],[6,9]], T = 9
输出：3
解释： 
我们选取片段 [0,4], [4,7] 和 [6,9] 。

示例 4：
输入：clips = [[0,4],[2,8]], T = 5
输出：2
解释：
注意，你可能录制超过比赛结束时间的视频。

提示：
1 <= clips.length <= 100
0 <= clips[i][0] <=clips[i][1] <= 100
0 <= T <= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/video-stitching
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

/**
 * 解题思路：动态规划
 */
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        bool change = true;// 是否发生改变
        int i, j, size = clips.size();
        // dp[i] ： 从0秒到i秒需经历的最小片段数
        vector<int> dp(T + 1, INT32_MAX);
        // 记录clips[i][0]对应的dp[clips[i][0]]值，若改动，则触发更新
        vector<int> triggerVal(size, INT32_MAX);
        dp[0] = 0;
        while (change) {
            change = false;
            for (i = 0; i < size; ++i) {
                // 与记录值不同，触发更新
                if (clips[i][0] < T && dp[clips[i][0]] != triggerVal[i]) {
                    change = true;
                    for (j = clips[i][0] + 1; j <= min(clips[i][1], T); ++j) {
                        if (dp[j] > dp[clips[i][0]] + 1) {
                            dp[j] = dp[clips[i][0]] + 1;
                        }
                    }
                    triggerVal[i] = dp[clips[i][0]];// 更新触发值
                }
            }
        }
        return dp[T] != INT32_MAX ? dp[T] : -1;
    }
};

int main() {
    Solution solution;
    int T = 5;
    vector<vector<int>> clips;
    vector<int> tmp(2, 0);
    tmp[0] = 5;
    tmp[1] = 7;
    clips.push_back(tmp);
    tmp[0] = 1;
    tmp[1] = 8;
    clips.push_back(tmp);
    tmp[0] = 0;
    tmp[1] = 0;
    clips.push_back(tmp);
    tmp[0] = 2;
    tmp[1] = 3;
    clips.push_back(tmp);
    tmp[0] = 4;
    tmp[1] = 5;
    clips.push_back(tmp);
    tmp[0] = 0;
    tmp[1] = 6;
    clips.push_back(tmp);
    tmp[0] = 5;
    tmp[1] = 10;
    clips.push_back(tmp);
    tmp[0] = 7;
    tmp[1] = 10;
    clips.push_back(tmp);

    cout << solution.videoStitching(clips, T) << endl;
    return 0;
}
