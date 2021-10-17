/** 题目描述：
 * 38. 报数
 * 报数序列是一个整数序列，按照其中的整数的顺序进行报数，得到下一个数。其前五项如下：

1.     1
2.     11
3.     21
4.     1211
5.     111221
 给定一个正整数 n（1 ≤ n ≤ 30），输出报数序列的第 n 项。

注意：整数顺序将表示为一个字符串。
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190228
 * */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string countAndSay(int n) {
        //输入范围判断
        if (n<1 || n>30) {
            return "";
        }
        string result = "1";
        //从2开始，迭代计算输出到第 n 个序列
        for (int i=1; i<n; i++) {

            string tmp = "";
            int j=0;
            //根据上一序列，求下一序列
            while (j<result.length()) {
                int num = 1;
                //数 有多少重复元素
                while (j+num < result.length()) {
                    if (result[j] != result[j+num]) {
                        break;
                    }
                    num++;
                }
                tmp = tmp  + (char)(num+48) + result[j];//单个数字(int) 与 字符对应关系 (输入n=[1,30]情况下，不会超过一位数)
                j += num;
            }
            result = tmp;
        }
        return result;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int Input = 10;
    cout << "Input = " << Input << endl;
    cout << "Output = " << solution.countAndSay(Input)  << endl;

}
