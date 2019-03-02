/** 题目描述：
 * 58. 最后一个单词的长度
 * 给定一个仅包含大小写字母和空格 ' ' 的字符串，返回其最后一个单词的长度。

如果不存在最后一个单词，请返回 0 。

说明：一个单词是指由字母组成，但不包含任何空格的字符串。

示例:

输入: "Hello World"
输出: 5

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190302
 * */
#include <iostream>
#include <string.h>

using namespace std;

class Solution {
public:
    int lengthOfLastWord(string s) {
        int iterator = s.length() - 1, last_word_len = 1;
        //定位到最后一个单词的尾部下标
        while(iterator > -1){
            if (s[iterator] != ' ') {
                break;
            }
            iterator--;
        }
        //若不存在最后一个单词，返回0
        if (iterator == -1) {
            return 0;
        }
        //"数"最后一个单词长度
        while (iterator > 0) {
            if (s[--iterator] == ' ') {
                break;
            }
            last_word_len++;
        }
        return last_word_len;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    string Input = "Hello World";
    cout << "Input = " << Input  << endl;
    cout << "Output = " << solution.lengthOfLastWord(Input)  << endl;
}
