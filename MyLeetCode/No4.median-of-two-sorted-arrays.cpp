#include <iostream>
#include <vector>
using namespace std;
/**
 * No4.寻找两个正序数组的中位数
 * 给定两个大小为 m 和 n 的正序（从小到大）数组nums1 和nums2。

请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为O(log(m + n))。

你可以假设nums1和nums2不会同时为空。

示例 1:
nums1 = [1, 3]
nums2 = [2]
则中位数是 2.0

示例 2:
nums1 = [1, 2]
nums2 = [3, 4]
则中位数是 (2 + 3)/2 = 2.5
*/

/**
 * 官方思路：
 * 假设两个有序数组分别是A和B。要找到第k个元素，我们可以比较 A[k/2-1]和 B[k/2-1]，其中 / 表示整数除法。
 * 由于 A[k/2-1]和 B[k/2-1] 的前面分别有 A[0,..,k/2-2] 和 B[0,..,k/2-2]，即 k/2-1 个元素，
 * 对于 A[k/2-1] 和 B[k/2-1] 中的较小值，最多只会有 (k/2-1)+(k/2-1) <= k-2 个元素比它小，那么它就不能是第 k 小的数了(故可排除/偏移)。
 *
 * 因此我们可以归纳出三种情况：
 * 1.如果 A[k/2-1] < B[k/2-1]，
 * 则比 A[k/2-1] 小的数最多只有 A 的前 k/2-1 个数和 B 的前 k/2-1 个数，即比 A[k/2-1] 小的数最多只有 k-2 个，因此 A[k/2-1] 不可能是第 k 个数，A[0] 到 A[k/2-1] 也都不可能是第 k 个数，可以全部排除。
 *
 * 2.如果 A[k/2-1] > B[k/2-1]，则可以排除 B[0] 到 B[k/2-1]。
 *
 * 3.如果 A[k/2-1] = B[k/2-1]，则可以归入第1.种情况处理。
 */
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2){
        int sumLen = nums1.size() + nums2.size();

        // 两数组大小之和若为奇数，则返回第k个数
        if (sumLen % 2 != 0) {
            return findKthElement(nums1, nums2, sumLen / 2 + 1);
        }
        // 为偶数，则返回第k-1个数和第k个数的平均值
        int kthElement1 = findKthElement(nums1, nums2, sumLen / 2);
        int kthElement2 = findKthElement(nums1, nums2, sumLen / 2 + 1);
        return (kthElement1 + kthElement2) / 2.0;
    }

    /**
     * 找到两个有序数组（归并后的）的第k个元素
     * @param nums1
     * @param nums2
     * @param k
     * @return
     */
    int findKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
        int Len1 = nums1.size(), Len2 = nums2.size(), offset1 = 0, offset2 = 0;
        int newOffset1 = 0, newOffset2 = 0;

        while (true) {
            // 若排除完其中一个数组，则顺序取另一数组元素直到第k个
            if (offset1 == Len1) {
                return nums2[offset2 + k - 1];
            }
            if (offset2 == Len2) {
                return nums1[offset1 + k - 1];
            }
            if (k == 1) {
                return min(nums1[offset1], nums2[offset2]);
            }

            // 防数组越界
            newOffset1 = min (offset1 + k / 2 - 1, Len1 - 1);
            newOffset2 = min (offset2 + k / 2 - 1, Len2 - 1);
            if (nums1[newOffset1] <= nums2[newOffset2]) {
                k -= newOffset1 - offset1 + 1;
                offset1 = newOffset1 + 1;
            } else {
                k -= newOffset2 - offset2 + 1;
                offset2 = newOffset2 + 1;
            }
        }
    }
};

int main() {
    Solution solution;
    int n1[4] = {1, 3, 4, 9};
    int n2[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> nums1(n1, n1 + 4);
    vector<int> nums2(n2, n2 + 10);

    cout << "median of two sorted arrays is: " << solution.findMedianSortedArrays(nums1, nums2) << endl;

    return 0;
}
