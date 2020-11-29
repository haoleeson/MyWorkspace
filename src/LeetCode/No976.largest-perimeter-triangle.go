/**
No976. 三角形的最大周长 (排序 + 贪心)
给定由一些正数（代表长度）组成的数组 A，返回由其中三个长度组成的、面积不为零的三角形的最大周长。
如果不能形成任何面积不为零的三角形，返回0。

示例 1：
输入：[2,1,2]
输出：5

示例 2：
输入：[1,2,1]
输出：0

示例 3：
输入：[3,2,3,4]
输出：10

示例 4：
输入：[3,6,2,3]
输出：8

提示：
3 <= A.length <= 10000
1 <= A[i] <= 10^6

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/largest-perimeter-triangle
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
package LeetCode

import "sort"

// 三角形条件：
// 1. a <= b <= c;
// 2: a + b > c
func largestPerimeter(A []int) int {
    size := len(A)
    // 排序 O(n * log(n))
    sort.Ints(A)
    // 倒叙找到满足 a + b > c 的三条边
    for i := size - 1; i >= 2; i-- {
        if A[i - 1] + A[i - 2] > A[i] {
            return A[i - 1] + A[i - 2] + A[i]
        }
    }
    return 0
}
