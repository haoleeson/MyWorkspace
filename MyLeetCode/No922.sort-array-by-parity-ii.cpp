/**
 * No922. 按奇偶排序数组 II
 * 给定一个非负整数数组A， A 中一半整数是奇数，一半整数是偶数。
 * 对数组进行排序，以便当A[i] 为奇数时，i也是奇数；当A[i]为偶数时， i 也是偶数。
 * 你可以返回任何满足上述条件的数组作为答案。

示例：
输入：[4,2,5,7]
输出：[4,5,2,7]
解释：[4,7,2,5]，[2,5,4,7]，[2,7,4,5] 也会被接受。

提示：
2 <= A.length <= 20000
A.length % 2 == 0
0 <= A[i] <= 1000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/sort-array-by-parity-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * 分析：一半奇数一半偶 ==> 数组个数为偶数；且奇偶数相等；
 * 若存在偶数在奇坐标，则必然存在奇数在偶坐标，交换之使平衡
 */
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& A) {
        int indexJi = 1, indexOu = 0, size = A.size();
        vector<int> ans(A);

        // 分别找到奇偶不在其位的奇偶下标（偶数在奇坐标，奇数在偶坐标）
        while(true) {
            // 寻找奇坐标不为奇数（寻偶数）
            while (ans[indexJi] & 0x01) {
                indexJi += 2;// 下一个奇坐标
                if (indexJi > size) {
                    return ans;
                }
            }
            // 寻找偶坐标不为偶数（寻奇数）
            while (!(ans[indexOu] & 0x01)) {
                indexOu += 2;// 下一个偶坐标
                if (indexOu == size) {
                    return ans;
                }
            }
            // 交换不在其位的奇偶数
            ans[indexJi] ^= ans[indexOu];
            ans[indexOu] ^= ans[indexJi];
            ans[indexJi] ^= ans[indexOu];
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int arr[] = {4,2,5,7};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(int));
    vector<int> result = solution.sortArrayByParityII(A);
    MyTools::printVec(result);
    return 0;
}
