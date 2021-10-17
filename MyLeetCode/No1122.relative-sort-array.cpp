/**
 * No1122. 数组的相对排序
 * 给你两个数组，arr1 和arr2，arr2中的元素各不相同，arr2 中的每个元素都出现在arr1中。
 * 对 arr1中的元素进行排序，使 arr1 中项的相对顺序和arr2中的相对顺序相同。未在arr2中出现过的元素需要按照升序放在arr1的末尾。

示例：
输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
输出：[2,2,2,1,4,3,3,9,6,7,19]

提示：
arr1.length, arr2.length <= 1000
0 <= arr1[i], arr2[i] <= 1000
arr2中的元素arr2[i]各不相同
arr2 中的每个元素arr2[i]都出现在arr1中

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/relative-sort-array
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "myTools.h"
using namespace std;

/**
 * 时间复杂度：max{O(size1), O(n * log(n))}, 其中 n = size1 - size2
 * 空间复杂度：O(size1) + K, K为常数
 */
class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        bool isA2Exist[1001] = {false};
        int a1Count[1001] = {0};
        int iterator = arr1.size();
        vector<int> ans(iterator, 0);

        // 标记arr2中出现过的数字
        for (int num : arr2) {
            isA2Exist[num] = true;
        }
        // 统计arr1中arr2中数字的个数
        for (int num : arr1) {
            if (isA2Exist[num]) {
                ++a1Count[num];
            } else {
                // 非arr2中的数字放ans尾部
                ans[--iterator] = num;
            }
        }
        // 用arr2的数字（及其出现次数）填充ans前部
        iterator = -1;
        for (int num : arr2) {
            while (a1Count[num]--) {
                ans[++iterator] = num;
            }
        }
        // 对ans尾部非arr2中的子数组排序（升）
        sort(ans.begin() + iterator + 1, ans.end());
        return ans;
    }
};

int main() {
    Solution solution;
    int arr1[] = {2,3,1,3,2,4,6,7,9,2,19};
    int arr2[] = {2,1,4,3,9,6};
    vector<int> A1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    vector<int> A2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    vector<int> result = solution.relativeSortArray(A1, A2);
    MyTools::printVec(result);
    return 0;
}
