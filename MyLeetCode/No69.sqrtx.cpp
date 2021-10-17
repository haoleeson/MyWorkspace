/** 题目描述：
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
            return 0;
        }
        int i=1;
        //最坏终止条件：INT_MAX = 2147483647, sqrt = 46341
        while(i < 46341){
            if(i*i > x) {
                break;
            }
            i++;
        }
        return i-1;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int Input = 2;
    cout << "Input = " << Input << endl;
    cout << "Output = " << solution.mySqrt(Input) << endl;
}
