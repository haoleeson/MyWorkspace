/**
 * No327. 区间和的个数 (前缀和 + 归并排序)
 * 给定一个整数数组nums，返回区间和在[lower, upper]之间的个数，包含lower和upper。
区间和S(i, j)表示在nums中，位置从i到j的元素之和，包含i和j(i ≤ j)。

说明:
最直观的算法复杂度是O(n^2) ，请在此基础上优化你的算法。

示例:
输入: nums = [-2,5,-1], lower = -2, upper = 2,
输出: 3
解释: 3个区间分别是: [0,0], [2,2], [0,2]，它们表示的和分别为: -2, -1, 2。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-of-range-sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

/**
 * 力扣官解：前缀和 + 归并排序
 *
 */
class Solution {
public:
    int countRangeSumRecursive(vector<long>& sum, int lower, int upper, int left, int right) {
        if (left == right) {
            return 0;
        } else {
            int mid = (left + right) / 2;
            int n1 = countRangeSumRecursive(sum, lower, upper, left, mid);
            int n2 = countRangeSumRecursive(sum, lower, upper, mid + 1, right);
            int ret = n1 + n2;

            // 首先统计下标对的数量
            int i = left;
            int l = mid + 1;
            int r = mid + 1;
            while (i <= mid) {
                while (l <= right && sum[l] - sum[i] < lower) l++;
                while (r <= right && sum[r] - sum[i] <= upper) r++;
                ret += (r - l);
                i++;
            }

            // 随后合并两个排序数组
            vector<int> sorted(right - left + 1);
            int p1 = left, p2 = mid + 1;
            int p = 0;
            // 归并排序有序两数组
            while (p1 <= mid || p2 <= right) {
                if (p1 > mid) {
                    sorted[p++] = sum[p2++];
                } else if (p2 > right) {
                    sorted[p++] = sum[p1++];
                } else {
                    if (sum[p1] < sum[p2]) {
                        sorted[p++] = sum[p1++];
                    } else {
                        sorted[p++] = sum[p2++];
                    }
                }
            }
            // 将sum的[left, right]区段替换为排序后的有序段
            for (int i = 0; i < sorted.size(); i++) {
                sum[left + i] = sorted[i];
            }
            return ret;
        }
    }

    int countRangeSum(vector<int>& nums, int lower, int upper) {
        long s = 0;
        vector<long> sum{0};
        for(auto& v: nums) {
            s += v;
            sum.push_back(s);
        }
        return countRangeSumRecursive(sum, lower, upper, 0, sum.size() - 1);
    }
};


/**
 * 方法一：依次递增区间长度，求区间和（压缩到一阶），仍然超时
 * 时间复杂度: O(n^2)
 * 空间复杂度：O(n)
 */
class Solution1 {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int i = 0, subLen = 0, ans = 0, size = nums.size();
        // sum[i] : 表示以下标 i 开头的子区间和（由区间长度控制）
        vector<long> sum(size, 0);

        // 子区间长度 ：subLen + 1
        while (subLen < size) {
            for (i = 0; i < size - subLen; ++i) {
                sum[i] += nums[i + subLen];
                if (sum[i] >= lower && sum[i] <= upper) {
                    ++ans;
                }
            }
            ++subLen;
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int arr[] = {-2, 5, -1};
    int lower = -2;
    int upper = 2;
    vector<int> A(arr, arr + sizeof(arr) / sizeof(int));
    cout << solution.countRangeSum(A, lower, upper) << endl;
    return 0;
}
