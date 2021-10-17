/** 题目描述： 【Fibonacci 数列】
 * 70. 爬楼梯
 * 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

注意：给定 n 是一个正整数。

示例 1：

输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。
1.  1 阶 + 1 阶
2.  2 阶
示例 2：

输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。
1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190302
 * */
#include <iostream>

using namespace std;

class Solution {
public:
        /**
     * 分析：
     * Dp思想： 总情况数为最后一步走"1"步到n阶的所有可能 + 最后一步走"2"步到n阶的所有可能
     * Result[n] = Result[n-1] + Result[n-2]
     *
     * Fibonacci 数列
     * x[1] = 1
     * x[2] = 2
     * x[n] = x[n-1] + x[n-2]
     * */
    int climbStairs(int n) {
        //错误情况
        if (n < 1) {
            return 0;
        }else if (n < 3) {
            return n;
        }
        int a = 0, b = 1, c;
        for (int i = 0; i < n; i++) {
            c = a;
            a = b;
            b = c + b;
        }
        return b;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int Input = 35;
    cout << "Input = " << Input << endl;
    cout << "Output = " << solution.climbStairs(Input) << endl;

}
