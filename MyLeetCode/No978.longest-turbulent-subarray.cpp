/**
 * No978. 最长湍流子数组
 * 当 A的子数组A[i], A[i+1], ..., A[j]满足下列条件时，我们称其为湍流子数组：
 * 若 i <= k < j，当 k为奇数时，A[k] > A[k+1]，且当 k 为偶数时，A[k] < A[k+1]；
 * 或若 i <= k < j，当 k 为偶数时，A[k] > A[k+1]，且当 k为奇数时，A[k] < A[k+1]。
 * 也就是说，如果比较符号在子数组中的每个相邻元素对之间翻转，则该子数组是湍流子数组。
 * 返回 A 的最大湍流子数组的长度。

示例 1：
输入：[9,4,2,10,7,8,8,1,9]
输出：5
解释：(A[1] > A[2] < A[3] > A[4] < A[5])

示例 2：
输入：[4,8,12,16]
输出：2

示例 3：
输入：[100]
输出：1

提示：
1 <= A.length <= 40000
0 <= A[i] <= 10^9

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/longest-turbulent-subarray
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
using namespace std;

/**
 * 锯齿图解法：
 * [9,4,2,10,7,8,8,1,9]
 *   [\,\,/ ,\,/,=,\,/]
 *   [1,1,2 ,3,4,0,1,2]
 */
class Solution {
    // 大小关系
    enum CMP {
        SMALLER = 0,
        LARGER = 1,
        EQUAL = 2
    };
public:
    int maxTurbulenceSize(vector<int>& A) {
        int maxLen = 0, size = A.size();
        if (size < 3) {
            return (size == 2 && A[0] == A[1]) ? 1 : size;
        }
        CMP tmp, lastTmp = A[0] == A[1] ? EQUAL : (A[1] > A[0] ? LARGER : SMALLER);
        int len = A[0] == A[1] ? 0 : 1;
        for (int i = 2; i < size; ++i) {
            tmp = A[i] == A[i - 1] ? EQUAL : (A[i] > A[i - 1] ? LARGER : SMALLER);
            // 中断锯齿的连续
            if (tmp == lastTmp || tmp == EQUAL) {
                if (len > maxLen) {
                    maxLen = len;
                }
                len = tmp == EQUAL ? 0 : 1;// 初始化子锯齿数
            } else {
                ++len;
            }
            lastTmp = tmp;
        }
        if (len > maxLen) {
            maxLen = len;
        }
        return maxLen + 1;// 锯齿数转换为元素个数（+1）
    }
};

int main() {
    Solution solution;
    int arr[] = {9,4,2,10,7,8,8,1,9};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(int));
    cout << solution.maxTurbulenceSize(A) << endl;
    return 0;
}
