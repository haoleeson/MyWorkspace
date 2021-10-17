/** 题目描述：   【用牛顿迭代法实现 sqrt ， 只返回整数部分】
 * 69. x 的平方根
 * 实现 int sqrt(int x) 函数。

计算并返回 x 的平方根，其中 x 是非负整数。

由于返回类型是整数，结果只保留整数的部分，小数部分将被舍去。

示例 1:

输入: 4
输出: 2
示例 2:

输入: 8
输出: 2
说明: 8 的平方根是 2.82842...,
     由于返回类型是整数，小数部分将被舍去。
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
    int mySqrt(int x) {
        //错误检测
        if (x <= 0) {
            return x;
        }
        /**【牛顿迭代法】：相当于求 f(x) = x^2 - c 的正根（只保留整数）
         * 【近似值】： X[n+1] = X[n] - f(X[n]) / f'(X[n])   【随着n的增加，越来越逼近精确真值】
         * 【带入公式f(x)，近似值】： X_n_1 = X_n - (X_n * X_n - c) / (2 * X_n)
         * 【整理近似值公式】： X_n_1 = (X_n + c / X_n) / 2
         * */
        int X_n = x > 46340 ? 46340 : x; //32位int限制，x的解不可能超过46340
        int X_n_1 = (X_n + x / X_n) / 2;
        //当二者相等，说明已求解到整数
        while (X_n > X_n_1) {
            X_n = X_n_1; //更新X[n]
            X_n_1 = (X_n + x / X_n) / 2; //计算X[n+1]，求解更精确的近似解。
        }
        return X_n;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int Input = 64;
    cout << "Input = " << Input << endl;
    cout << "Output = " << solution.mySqrt(Input) << endl;
}
