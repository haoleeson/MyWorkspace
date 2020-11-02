/**
 * No349. 两个数组的交集
 * 给定两个数组，编写一个函数来计算它们的交集。

示例 1：
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]

示例 2：
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]

说明：
输出结果中的每个元素一定是唯一的。
我们可以不考虑输出结果的顺序。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/intersection-of-two-arrays
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include "myTools.h"
using namespace std;

/**
 * 用 set 存
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        set<int> s1;
        set<int> s2;
        set<int> combine;
        if (nums1.size() < nums2.size()) {
            for (int num : nums1) {
                s1.insert(num);
            }
            for (int num : nums2) {
                if (s1.find(num) != s1.end()) {
                    combine.insert(num);
                }
            }
        } else {
            for (int num : nums2) {
                s2.insert(num);
            }
            for (int num : nums1) {
                if (s2.find(num) != s2.end()) {
                    combine.insert(num);
                }
            }
        }
        for (set<int>::iterator it = combine.begin(); it != combine.end(); ++it) {
            ans.push_back(*it);
        }
        return ans;
    }
};

/**
 * 先排序再比较
 * 时间复杂度：O(n * log(n))
 * 空间复杂度：O(1)
 */
class Solution1 {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        int index1 = 0, index2 = 0, size1 = nums1.size(), size2 = nums2.size();
        // 先排序: O(n * log(n))
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        while (index1 < size1 && index2 < size2) {
            if (nums1[index1] > nums2[index2]) {
                // index2 后移
                ++index2;
                while (index2 < size2 && nums2[index2] == nums2[index2 - 1]) {
                    ++index2;
                }
            } else if (nums1[index1] < nums2[index2]) {
                // index1 后移
                ++index1;
                while (index1 < size1 && nums1[index1] == nums1[index1 - 1]) {
                    ++index1;
                }
            } else {
                ans.push_back(nums1[index1]);
                // index1 后移
                ++index1;
                while (index1 < size1 && nums1[index1] == nums1[index1 - 1]) {
                    ++index1;
                }
                // index2 后移
                ++index2;
                while (index2 < size2 && nums2[index2] == nums2[index2 - 1]) {
                    ++index2;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int arr1[] = {4,9,5};
    int arr2[] = {9,4,9,8,4};
    vector<int> num1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    vector<int> num2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    vector<int> result = solution.intersection(num1, num2);
    MyTools::printVec(result);
    return 0;
}
