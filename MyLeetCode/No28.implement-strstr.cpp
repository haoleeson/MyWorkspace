/** 题目描述：
 * 28. 实现strStr()
 * 实现 strStr() 函数。
 给定一个 haystack 字符串和一个 needle 字符串，
 在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。
 如果不存在，则返回  -1。
 备注：当 needle 是空字符串时我们应当返回 0 。
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190228
 * */
#include <iostream>
#include <string.h>

using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        //特殊情况 needle 为空， 返回0
        if(needle.length() ==0){
            return 0;
        }
        for (int i=0; i<haystack.length(); i++) {
            //如果首位字符相同，则继续判断
            if (haystack[i] == needle[0]) {
                int j=1;
                while ((j<needle.length()) && (i+j < haystack.length())) {
                    if (haystack[i+j] != needle[j]) {
                        break;
                    }
                    j++;
                }
                if (j == needle.length()) {
                    return i;
                } else if (i+j == haystack.length()) {
                    return -1;
                }
            }
        }
        return -1;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    string haystack = "mississippi";
    string needle = "issip";
    cout << "Input:" << endl;
    cout << "haystack = " << haystack << endl;
    cout << "needle = " << needle << endl;

    cout << "Output = " << solution.strStr(haystack, needle)  << endl;

}
