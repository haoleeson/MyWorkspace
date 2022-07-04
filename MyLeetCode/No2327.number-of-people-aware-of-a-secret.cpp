#include <iostream>

#include "myTools.h"

using namespace std;

class Solution {
    const int MOD = 1e9 + 7;

public:
    int peopleAwareOfSecret(int n, int delay, int forget) {
        // 定义 f 为对每个人来说，第 i 天知晓秘密后的人数 i = [0, forget]
        vector<int> f(forget, 0);
        f[0] = 1;

        for (int day = 2; day <= n; ++day) {
            // 处理第二天的状态
            // a. 第 [delay, forget - 1] 天知晓秘密的人，分享秘密给新人新人
            long shareNum = 0;
            for (int i = forget - 1; i >= delay; --i) {
                f[i] = f[i - 1];
                shareNum = (shareNum + f[i - 1]) % MOD;
            }
            // b. 第 [1, delay - 1] 天知晓秘密的人，保守秘密
            for (int i = delay - 1; i > 0; --i) {
                f[i] = f[i - 1];
            }
            // c. 第 0 天知晓秘密的人数
            f[0] = (int)(shareNum);
        }

        int res = 0;
        for (int i = 0; i < forget; ++i) {
            res = (res + f[i]) % MOD;
        }

        return res;
    }
};

int main(void) {
    Solution solution;

    int n1 = 6;
    int delay1 = 2;
    int forget1 = 4;
    int res1 = solution.peopleAwareOfSecret(n1, delay1, forget1);
    cout << res1 << endl;

    int n2 = 4;
    int delay2 = 1;
    int forget2 = 3;
    int res2 = solution.peopleAwareOfSecret(n2, delay2, forget2);
    cout << res2 << endl;

    return 0;
}
