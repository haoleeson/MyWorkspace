#include <iostream>
using namespace std;

/**
 * 20200819阿里校园招聘机试题1
 * 描述：
 * 给定三个数组 a, b, c，其长度分别为 n, m, n+m
 * 规则：每次只能从 a 或 b 数组的最前端取出一个数字，不可重复取
 * 求：c 数组 能否由以上规则从 a 和 b数组中按取得先后顺序构成
 *
示例1：
输入：
2
1 3 4
2 3 6
1 2 3 4 3 6
1 3 4
2 3 6
1 3 6 3 4 2
输出：
possible
not possible
 */

/**
 * 解题思路：回溯 、归并
 * coder: eisenhao
 * date: 20200819
 */
class Solution{
public:
    // a，b数组是否能构成数组c
    bool juge(int* a, int* b, int* c, int n, int m) {
        int iteratorA = 0, iteratorB = 0, iteratorC = 0;
        while (iteratorC < (n + m)) {
            // 特殊情况，a，b前端数字相等
            if ((a[iteratorA] == b[iteratorB]) && (a[iteratorA] == c[iteratorC])) {
                bool chooseA = juge(a + iteratorA + 1, b + iteratorB, c + iteratorC + 1, n - iteratorA - 1, m - iteratorB);
                if (chooseA) {
                    return true;
                }
                bool chooseB = juge(a + iteratorA, b + iteratorB + 1, c + iteratorC + 1, n - iteratorA, m - iteratorB - 1);
                if (chooseB) {
                    return true;
                }
                return false;
            }
            if (a[iteratorA] == c[iteratorC]) {
                ++iteratorA;
                ++iteratorC;
                continue;
            }
            if (b[iteratorB] == c[iteratorC]) {
                ++iteratorB;
                ++iteratorC;
                continue;
            }
            return false;
        }
        return true;
    }
};


int main() {
    int T = 0, n = 0, m = 0;
    Solution solution;
    cin >> T;

    while (T--) {
        cin >> n;
        cin >> m;
        int *a = new int[n]{0};
        int *b = new int[m]{0};
        int *c = new int[n+m]{0};
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < m; ++i) {
            cin >> b[i];
        }
        for (int i = 0; i < n+m; ++i) {
            cin >> c[i];
        }
        if (solution.juge(a, b, c, n, m)) {
            cout << "possible" << endl;
        } else {
            cout << "not possible" << endl;
        }
    }
    return 0;
}
