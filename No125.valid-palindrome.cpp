/** 题目描述：
 * 125. 验证回文串
 * 给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。

说明：本题中，我们将空字符串定义为有效的回文串。

示例 1:

输入: "A man, a plan, a canal: Panama"
输出: true
示例 2:

输入: "race a car"
输出: false

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190319
 * */
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        if (s.length() < 2) {
            return true;
        }
        //全部转换成小写字母
        vector<char> strBuff(s.length(), 0);
        int realLength = 0;
        char ch;
        for (int i=0; i<s.length(); i++) {
            ch = s[i];
            if ((ch>'a'-1 && ch<'z'+1) || (ch>'0'-1 && ch<'9'+1)) {
                strBuff[realLength++] = ch;
            }
            if (ch>'A'-1 && ch<'Z'+1){
                strBuff[realLength++] = ch - ('A'-'a');
            }
        }
        int i=0, j=realLength-1;
        //验证
        while (i < j) {
            if (strBuff[i++] != strBuff[j--]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, const char * argv[]) {
    Solution s;
    string Input = "A man, a plan, a canal: Panama";
    cout << "Input:" << Input << endl;
    cout << "Output:" << s.isPalindrome(Input) << endl;
    cout << endl;
}

