/** 题目描述：【排列组合，int超出范围】可计算n=[0,38]
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
    //理解为: 在一排 n-2*i 个值为1小球中间插入 i 个值为2的小球（不限一个球）
    int climbStairs(int n) {
        long int result = 0;
        long int tmp;
        /*** 分情况讨论走2步的次数 i=[0,n/2] ***/
        for(int i=0; i<=n/2; i++) {
            /** 分析：
             * 总共走的步数为： (i + n-2*i), 即 n-i 步，相当于从 n-i 步中选出 i 步走”2“步，其余走”1“步
             * 由【排列组合】知，有  C(n-i, i) 种走法
             * 公式：              C(n  , m) = n! / ((n-m)! * m!)
             *                              = n(n-1)(n-2)...(n-m+1) / m(m-1)(m-2)...1
             * */
            //计算上部
            long int Up = 1, Up_iterator = n-i;
            while (Up_iterator > (n-2*i)) {
                Up *= Up_iterator--;
            }
            //计算下部
            long int Down = 1, Down_iterator = i;
            while (Down_iterator > 1){
                Down *= Down_iterator--;
            }
            tmp = Up / Down;
            result += tmp;
            //cout << "i= " << i << ", tmp = " << tmp << endl;
        }
        return (int)result;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int Input = 38;
    cout << "Input = " << Input << endl;
    cout << "Output = " << solution.climbStairs(Input) << endl;
}
