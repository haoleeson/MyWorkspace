/**
 * No977. 有序数组的平方（双指针）
 * 给定一个按非递减顺序排序的整数数组 A，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。

示例 1：
输入：[-4,-1,0,3,10]
输出：[0,1,9,16,100]

示例 2：
输入：[-7,-3,2,3,11]
输出：[4,9,9,49,121]

提示：
1 <= A.length <= 10000
-10000 <= A[i] <= 10000
A已按非递减顺序排序。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/squares-of-a-sorted-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include "myTools.h"
using namespace std;

class Solution {
private:
    int abs(int a) {
        return a < 0 ? -a : a;
    }
public:
    vector<int> sortedSquares(vector<int>& A) {
        int size = A.size(), startIndex = 0, endIndex = size - 1, iterator = size - 1;
        if (size < 1) {
            return vector<int>();
        }
        vector<int> ans(size);
        // 按绝对值大小倒叙放入ans
        while (startIndex < endIndex) {
            if (abs(A[startIndex]) > abs(A[endIndex])) {
                ans[iterator--] = A[startIndex++];
            } else {
                ans[iterator--]  = A[endIndex--];
            }
        }
        ans[iterator--] = A[startIndex];
        // 计算平方
        for (int i = 0; i < size; ++i) {
            ans[i] *= ans[i];
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int arr[] = {-7,-3,2,3,11};
    vector<int> A(arr, arr + sizeof(arr) / sizeof(int));
    vector<int> result = solution.sortedSquares(A);
    MyTools::printVec(result);
    return 0;
}
