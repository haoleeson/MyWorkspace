/**
No204. 计数质数（埃氏筛、线性筛）
统计所有小于非负整数 n 的质数的数量。

示例 1：
输入：n = 10
输出：4
解释：小于 10 的质数一共有 4 个, 它们是 2, 3, 5, 7 。

示例 2：
输入：n = 0
输出：0

示例 3：
输入：n = 1
输出：0

提示：
0 <= n <= 5 * 106

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/count-primes
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
package LeetCode

/**
判断一个数是否质数(素数)
@param num 待判断数字
@return true -- 是质数；false -- 非质数
 */
func isPrime(num int) bool {
    for i := 2; i * i <= num; i++ {
        if num % i == 0 {
            return false
        }
    }
    return true
}

/*
解题思路：暴力枚举 + 标记已有质数的倍数（为非质数）, 以加速判断
即埃氏筛
时间复杂度：O(n * loglogn)
空间复杂度：O(n)
*/
func countPrimes1(n int) int {
    count := 0
    // 非质数标记数组
    notPrime := make([]bool, n)
    for i := 2; i < n; i++ {
        // 若是之前出现过的质数倍数（被标记，跳过）
        if notPrime[i] {
            continue
        }
        // 由于是从2累加，所有合数已被较小质数倍数包括，这里的i一定以质数
        //notPrime[i] = true // 加上更符合逻辑，不过后面用不上notPrime[i]notPrime[i]，可注释
        count++
        // 标记该质数的倍数为（非质数），注：从 i * i 开始标，因为之前的已被其他质数倍数标记过了
        if int64(i * i) < int64(n) {
            for j := i * i; j < n; j += i {
                notPrime[j] = true
            }
        }
    }
    return count
}

/**
力扣官解：线性筛，相较于埃氏筛，减少了倍数非质数的冗余标记，保证只被标记一次
时间复杂度：O(n)
空间复杂度：O(n)
 */
func countPrimes(n int) int {
    // 暂存已有质数的数组
    primes := make([]int, n/2)
    lenPrimes := 0
    // 是质数标志
    notPrime := make([]bool, n)
    for i := 2; i < n; i++ {
        // 若 i 是质数，添加到质数的数组
        if !notPrime[i] {
            primes[lenPrimes] = i
            lenPrimes++
        }
        for j := 0; j < lenPrimes && primes[j] * i < n; j++ {
            notPrime[i * primes[j]] = true
            if i % primes[j] == 0 {
                break
            }
        }
    }
    return lenPrimes
}