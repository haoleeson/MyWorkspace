/**
No454. 四数相加 II (两两组合)
给定四个包含整数的数组列表A , B , C , D ,计算有多少个元组 (i, j, k, l)，使得A[i] + B[j] + C[k] + D[l] = 0。
为了使问题简单化，所有的 A, B, C, D 具有相同的长度N，且 0 ≤ N ≤ 500 。所有整数的范围在 -228 到 228 - 1 之间，最终结果不会超过231 - 1 。

例如:
输入:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]
输出:
2

解释:
两个元组如下:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
package LeetCode

/**
两两组合，时间复杂度为 O(n^2) + O(n^2), 仍然为O(n^2)
 */
func fourSumCount(a, b, c, d []int) (ans int) {
    countAB := map[int]int{}
    for _, v := range a {
        for _, w := range b {
            countAB[v + w]++
        }
    }
    for _, v := range c {
        for _, w := range d {
            // 若存在 A + B的和中若存在 count个 -(C + D)组合，即有count个4和为0的组合
            if countAB[-v - w] != 0 {
                ans += countAB[-v - w]
            }
        }
    }
    return
}
