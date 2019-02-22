/** 题目描述：
 *  判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190222
 * */
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

class Solution {
public:
    bool isPalindrome(int x) {
        //负数一定不是回文数
        if (x < 0) {
            return false;
        }
        //计算数字位数？
        int wei_num = 1;//至少一位
        int tmp = x/10;
        for(; tmp>0; wei_num++){
            tmp /= 10;
        }
        //先判断首末位是否相同
        if ((x/(int)pow(10, wei_num-1) != (x%10))) {
            return false;
        }
        //再两边向中间逐位比较
        for(int i=0; i<wei_num/2 - 1; i++){
            //左边第i位  compare  右边第i位
            if(x/(int)pow(10, wei_num-2-i)%10 != x/(int)pow(10, i+1)%10) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int Input = 123585321;
    cout << "Input = " << Input << endl;
    cout << "Output = " <<  solution.isPalindrome(Input) << endl;
}
