#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 求 n 内质数个数，总方案数 = 质数排列组合 * 合数排列组合
// 思路2：优化：避免重复计算，将 100 以内的 25 个质数制作成表，二分查找最终下标+1得到质数个数
class Solution {
public:
    int numPrimeArrangements(int n) {
        // 统计质数，合数个数
        int cnt[2] = {0, 0};

        cnt[0] = cntPrime(n);
        cnt[1] = n - cnt[0];

        // 求质数个数的阶乘 * 合数个数的阶乘
        long long int res = 1;
        for (int i = 0; i < 2; ++i) {
            for (int j = cnt[i]; j > 1; --j) {
                res *= j;
                res %= MOD;
            }
        }

        return (int)res;
    }

private:
    const long MOD = 1e9 + 7;
    const int primeTab[25] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
                              43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

    // 获取范围 n 内的质数个数
    int cntPrime(int n) {
        int left = 0, right = 24, mid;

        while (left < right) {
            mid = (left + right + 1) / 2;
            if (n >= primeTab[mid]) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }

        return right + 1;
    }
};

// 思路：求 n 内质数个数，总方案数 = 质数排列组合 * 合数排列组合
class Solution1 {
private:
    const long MOD = 1e9 + 7;

    // 是否为质数校验
    bool isPrime(int num) {
        if (num < 2) {
            return false;
        }

        for (int i = 2; i * i <= num; ++i) {
            if (num % i == 0) {
                return false;
            }
        }

        return true;
    }

public:
    int numPrimeArrangements(int n) {
        // 统计质数，合数个数
        int cnt[2] = {0, 0};
        int& cntPrime = cnt[0];
        int& cntComposite = cnt[1];
        for (int i = 1; i <= n; ++i) {
            if (isPrime(i)) {
                ++cntPrime;
            }
        }
        cntComposite = n - cntPrime;

        // 求质数个数的阶乘 * 合数个数的阶乘
        long long int res = 1;
        for (int i = 0; i < 2; ++i) {
            for (int j = cnt[i]; j > 1; --j) {
                res *= j;
                res %= MOD;
            }
        }

        return (int)res;
    }
};

int main(void) {
    Solution solution1;
    //    int n1 = 5;
    //    long res1 = solution1.numPrimeArrangements(n1);
    //    cout << res1 << endl;

    int n2 = 100;
    long res2 = solution1.numPrimeArrangements(n2);
    cout << res2 << endl;

    return 0;
}
