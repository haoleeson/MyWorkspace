/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190222
 * */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        if(x < -2147483647){
            //无法用转换后的正数表示
            return 0;
        }
        bool isNegative = false;
        int result = 0;
        if(x < 0){
            x = -x;
            isNegative = true;
        }
        while(x > 0){
            int tmp = x % 10;
            x = x / 10;
            /**溢出判断
             * MAX_VALUE : 2147483647
             * MIN_VALUE : -2147483648
             * 要判断最后一位不要大于 7 和 不要小于8
             * 若溢出，返回0
             * */
             if(result > 214748364){
                 //下步乘10将会溢出
                 result = 0;
                 break;
             }else if(result == 214748364 && tmp >7){
                 //将会溢出
                 result = 0;
                 break;
             }
            result = result * 10 + tmp;
        }
        return isNegative ? -result : result;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int Input = -2147483648;
    cout << "Input = " << Input << endl;
    cout << "Output = " <<  solution.reverse(Input) << endl;
}
