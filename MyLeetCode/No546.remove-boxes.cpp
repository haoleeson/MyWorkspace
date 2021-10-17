#include <iostream>
#include <vector>
#include <memory.h>
using namespace std;

/**
 * No546. 移除盒子（动态规划）
 * 给出一些不同颜色的盒子，盒子的颜色由数字表示，即不同的数字表示不同的颜色。
 * 你将经过若干轮操作去去掉盒子，直到所有的盒子都去掉为止。每一轮你可以移除具有相同颜色的连续 k 个盒子（k>= 1），这样一轮之后你将得到 k*k 个积分。
 * 当你将所有盒子都去掉之后，求你能获得的最大积分和。

示例：
输入：boxes = [1,3,2,2,2,3,4,3,1]
输出：23
解释：
[1, 3, 2, 2, 2, 3, 4, 3, 1]

----> [1, 3, 3, 4, 3, 1] (移除相邻的3个2，3*3=9 分)
----> [1, 3, 3, 3, 1] (移除1个4，1*1=1 分)
----> [1, 1] (移除相邻的3个3，3*3=9 分)
----> [] (移除相邻的2个1，2*2=4 分)
9 + 1 + 9 + 4 = 23

提示：
1 <= boxes.length <= 100
1 <= boxes[i]<= 100

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/remove-boxes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


/**
 * 力扣题解：
 * 设dp[l][r][k]表示：
 * 起始下标l(以0开始)，结束下标r，k表示在下标r后面紧接着有k个元素值和boxes[r]相同，的最大积分和。
 *
 * 情况1：
 * 比如：[l,l+1,···,r-1,r,值同r，值同r，值同r]:
 * 这里有3个元素和boxes[r]相同，即k==3，那么dp[l][r][3]=dp[l][r-1][0]+4*4，因为有3个和[r]相同，共可以消除4个，所以加上4*4。可得到初始化条件： dp[l][r][k]=dp[l][r-1][0] + (k+1)*(k+1)
 *
 * 情况2：但是有可能在boxes[l]~boxes[r-1]中也存在和boxes[r]相同值的元素，有可能获得更大的积分和
 * 比如[l,l+1,···,i,···,r-1,r,值同r，值同r，值同r]，假设boxes[i]==boxes[r]
 * 那么可能先移除boxes[i+1]~boxes[r-1]，这样就能使原来的dp[l][r][3]的k=3变的更大，但是r变得更小，但是积分和更大
 * 因此就需要在boxes[l]~boxes[r-1]中找到boxes[i]==boxes[r]
 * 这样子先移除boxes[i+1]~boxes[r-1]，这一部分的最大积分和是dp[i+1][r-1][0]
 * 移除之后是[l,l+1,···,i,值同i(原来是r)，值同i(原来是r+1)，值同i(原来是r+2)，值同i(原来是r+3)]
 * 剩下这部分是dp[l][i][k+1]
 *
 * 总和起来就是dp[l][r][k] = max(dp[l][r][k],dp[i+1][r-1][0]+dp[l][i][k+1])
 * 最后的答案就是dp[0][boxes.size()-1][0]
 */

class Solution {
public:
    int removeBoxes(vector<int>& boxes) {
        memset(dp, 0, sizeof(dp));
        return getDp(boxes, 0, (int)boxes.size() - 1, 0);
    }

private:
    int dp[100][100][100];
    int getDp(vector<int>& boxes, int l, int r, int k) {
        if (l > r) {
            return 0;
        }
        if (dp[l][r][k] != 0) {
            return dp[l][r][k];
        }
        // 加速缩小r增大k，以剪枝递归
        while (l < r && boxes[r - 1] == boxes[r]) {
            --r;
            ++k;
        }

        // 情况1：初始化最小值，仅移除(l,r)段的最后一个数（及后续k个与r同值且连续的数）
        dp[l][r][k] = getDp(boxes, l, r - 1, 0) + (k + 1) * (k + 1);

        // 情况2：找(l,r-1)中是否有与r同值的数，若存在则可与后面(k+1)个数组成更大的积分
        for (int i = l, tmpScore = 0; i < r; ++i) {
            if (boxes[i] == boxes[r]) {
                tmpScore = getDp(boxes, i + 1, r - 1, 0) + getDp(boxes, l, i, k + 1);
                dp[l][r][k] = std::max( dp[l][r][k], tmpScore );
            }
        }
        return dp[l][r][k];
    }
};

/**
 * 解题思路：暴力，超时且情况考虑不完全
 * coder: eisenhao
 * date: 20200819
 */
class SolutionOld {
public:
    int removeBoxes(vector<int>& boxes) {
        len = boxes.size();
        dp = new int[len]{0}; // 表示每个数左侧连续数个数
        dpLeftCount = new int[len]{0}; // 表示每个数左侧有多少个该数(不要求连续)
        dp[0] = 1;
        dpLeftCount[0] = 1;
        ++count[boxes[0]];

        // 初始化dp
        for (int i = 1; i < len; ++i) {
            dp[i] = (boxes[i] == boxes[i - 1]) ? 1 + dp[i - 1] : 1;
            ++count[boxes[i]];// 统计每种颜色数量
            dpLeftCount[i] = count[boxes[i]];
        }

        int res = 0, leftN = len;
        while (true) {
            int i = 0;
            while(i < len) {
                if (dp[i] != 0 && dp[i] == count[boxes[i]]) {
                    leftN -= dp[i];// 移除 dp[i] 个连续箱子
                    res += dp[i] * dp[i];
                    if (leftN == 0) {
                        return res;
                    }

                    removeBoxes(boxes, i);
                    i = -1;
                }
                ++i;
            }
        }
        return res;
    }

private:
    int len ;
    int count[101] = {0};
    int* dp; // 表示每个数左侧连续数个数
    int* dpLeftCount; // 表示每个数左侧有多少个该数(不要求连续)
    void removeBoxes(vector<int>& boxes, int index) {
        // 变更之后的Dp统计（因移除后出现连续）
        int frontNotZeroIndex = index;
        for (int removeN = dp[index]; frontNotZeroIndex >= 0 && removeN > 0; --frontNotZeroIndex) {
            if (dp[frontNotZeroIndex] == 0) {
                continue;
            }
            --removeN;
        }
        int behindNotZeroIndex = index + 1;
        while (behindNotZeroIndex < len && dp[behindNotZeroIndex] == 0) {
            ++behindNotZeroIndex;
        }
        if (frontNotZeroIndex >= 0 && behindNotZeroIndex < len && boxes[behindNotZeroIndex] == boxes[frontNotZeroIndex]) {
            for (int j = behindNotZeroIndex, tmpCount = dp[frontNotZeroIndex]; j < len; ++j) {
                if (dp[j] == 0) {
                    continue;
                }
                if (boxes[j] == boxes[frontNotZeroIndex]) {
                    dp[j] = ++tmpCount;
                } else {
                    break;
                }
            }
        }

        // 清除已移除箱子的统计值
        for (int j = index, removeN = dp[index]; j >= 0 && removeN > 0; --j) {
            if (dp[j] == 0) {
                continue;
            }
            dp[j] = 0;
            --removeN;
        }
    }
};

int main() {
    int arr[] = {1,3,2,2,2,3,4,3,1};
    vector<int> boxes(arr, arr + sizeof(arr)/sizeof(int));

    Solution solution1;

    cout << solution1.removeBoxes(boxes) << endl;
    return 0;
}
