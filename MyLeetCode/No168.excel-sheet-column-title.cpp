/**
 * 168. Excel表列名称
 * 给定一个正整数，返回它在 Excel 表中相对应的列名称。

例如 :
    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
    ...
示例 1:

输入: 1
输出: "A"
示例 2:

输入: 28
输出: "AB"
示例 3:

输入: 701
输出: "ZY"

 * coder:eisenhao
 * 20190322
 * */

#include <iostream>

using namespace std;

class Solution {
public:
    string convertToTitle(int n) {
        string result = "";
        while (n-- > 0) {
            result.insert(result.begin(), (char)(n % 26 + 65));//开始处插入一个字符
            n /= 26;
        }
        return result;
    }
};

int main(void) {
    Solution s;
    int Input = 701;
    cout << "Input  = " << Input << endl;
    cout << "Output = " << s.convertToTitle(Input) << endl;
    return 0;
}

