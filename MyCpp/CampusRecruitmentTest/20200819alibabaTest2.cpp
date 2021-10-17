#include <iostream>
using namespace std;

/**
 * 20200819阿里校园招聘机试题2
 * 描述：
 * 输入一个数组，大小为n，定义求长度为 k 的子序列的值为，其中 k 个数的最小值。
 * 求：对于每个取值 k （k = [1, n]），求该数组中能找到的对应每个k的最大子序列
 *
示例1：
输入：
5
2, 5, 3, 1, 2

输出：
k=1, choose[a2], ans is 5.
k=2, choose[a2,a3], ans is 3.
k=3, choose[a1,a2,a3], ans is 2.
k=4, choose[a1,a2,a3,a4], ans is 1.
k=5, choose[a1,a2,a3,a4,a5], ans is 1.
 */


/**
 * 解题思路：动态规划
 * coder: eisenhao
 * date: 20200819
 */
class Solution{
public:
    void maxValue(int* a, int n) {
        int* dp = new int[n]{0};
        // k = 1时，为其自身
        for (int i = 0; i < n; ++i) {
            dp[i] = a[i];
        }

        for (int k = 1; k <= n; ++k) {

            if (k > 1) {
                // 处理
                for (int i = n - 1; i >= k - 1; --i) {
                    int tmp = min(dp[i - 1], a[i]);
                    dp[i] = min(dp[i - 1], a[i]);
                }
            }

            // 遍历dp，找到最大值
            int tmpMax = 0, tmpMaxIndex = 0;
            for (int i = k - 1; i < n; ++i) {
                if (dp[i] > tmpMax) {
                    tmpMax = dp[i];
                    tmpMaxIndex = i;
                }
            }
            // 输出
            printRes(k, tmpMax, tmpMaxIndex);
        }
    }

    void printRes(int k, int tmpMax, int tmpMaxIndex) {
        cout << "k=" << k << ", choose[";
        for (int i = 0; i < k-1; ++i) {
            cout << "a" << tmpMaxIndex - k + i + 2 << ",";
        }
        cout << "a" << tmpMaxIndex + 1 << "], ans is " << tmpMax << ". " << endl;
    }
};


int main() {
    int n = 0;
    Solution solution;
    cin >> n;
    int *a = new int[n]{0};
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

//    int b[5] = {2, 5, 3, 1, 2};
//    solution.maxValue(b, 5);
    solution.maxValue(a, 5);
    return 0;
}
