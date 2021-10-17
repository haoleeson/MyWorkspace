/** 题目描述：
 * 罗马数字转整数
 * 罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。

字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。

通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：

I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个罗马数字，将其转换成整数。输入确保在 1 到 3999 的范围内。
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190225
 * */
#include <iostream>
#include <string.h>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        int result = 0;
        char* Ptr = &s[0];
        for(int i=0; i<s.length(); i++){
            int tmp = 0;
            bool isNegative = false; //是否为负数标志
            switch (*(Ptr + i)){
                case 'I':
                    tmp = 1;
                    if ((i+1 < s.length()) && (*(Ptr+i+1)=='V' || *(Ptr+i+1)=='X')){
                        isNegative = true;
                    }
                    break;
                case 'X':
                    tmp = 10;
                    if ((i+1 < s.length()) && (*(Ptr+i+1)=='L' || *(Ptr+i+1)=='C')){
                        isNegative = true;
                    }
                    break;
                case 'C':
                    tmp = 100;
                    if ((i+1 < s.length()) && (*(Ptr+i+1)=='D' || *(Ptr+i+1)=='M')){
                        isNegative = true;
                    }
                    break;

                case 'V':
                    tmp = 5;
                    break;
                case 'L':
                    tmp = 50;
                    break;
                case 'D':
                    tmp = 500;
                    break;
                case 'M':
                    tmp = 1000;
                    break;

                default:
                    break;
            }
            if(isNegative){
                result -= tmp;
            } else {
                result += tmp;
            }
        }
        return result;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    string Input = "MCMXCIV";
    cout << "Input = " << Input << endl;
    cout << "Output = " <<  solution.romanToInt(Input) << endl;
}
