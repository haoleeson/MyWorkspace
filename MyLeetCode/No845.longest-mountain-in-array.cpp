/**
 * No845. 数组中的最长山脉
 * 我们把数组 A 中符合下列属性的任意连续子数组 B 称为 “山脉”：B.length >= 3
 * 存在 0 < i < B.length - 1 使得 B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
 * （注意：B 可以是 A 的任意子数组，包括整个数组 A。）
 * 给出一个整数数组 A，返回最长 “山脉”的长度。如果不含有 “山脉”则返回 0。

示例 1：
输入：[2,1,4,7,3,2,5]
输出：5
解释：最长的 “山脉” 是 [1,4,7,3,2]，长度为 5。

示例 2：
输入：[2,2,2]
输出：0
解释：不含 “山脉”。

提示：
0 <= A.length <= 10000
0 <= A[i] <= 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-mountain-in-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int longestMountain(vector<int>& A) {
        int i, maxLen = -1, size = A.size();
        vector<int> leftSmall(size, 0);
        vector<int> rightBig(size, 0);
        // 统计 A[i] 左边连续比 A[i]小的个数
        for (i = 1; i < size; ++i) {
            leftSmall[i] = A[i] > A[i - 1] ? leftSmall[i - 1] + 1 : 0;
        }
        // 统计 A[i] 右边连续比 A[i]大的个数
        for (i = size - 2; i >= 0; --i) {
            rightBig[i] = A[i] > A[i + 1] ? rightBig[i + 1] + 1 : 0;
        }
        for (i = 1; i < size - 1; ++i) {
            if (leftSmall[i] == 0 || rightBig[i] == 0) {
                continue;
            }
            if (leftSmall[i] + rightBig[i] > maxLen) {
                maxLen = leftSmall[i] + rightBig[i];
            }
        }
        return maxLen + 1;
    }
};

int main() {
    Solution solution;
    int arr[] = {0,1,0};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(int));
    cout << solution.longestMountain(A) << endl;
    return 0;
}
