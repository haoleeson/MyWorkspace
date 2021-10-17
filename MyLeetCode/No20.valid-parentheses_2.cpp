/** 题目描述：[迭代方式]
 * 20. 有效的括号
 * 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。

 * 有效字符串需满足：
左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。
注意空字符串可被认为是有效字符串。

示例 1:
输入: "()[]{}"
输出: true

示例 2:
输入: "(]"
输出: false

示例 3:
输入: "([)]"
输出: false

示例 4:
输入: "{[]}"
输出: true
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190225
 * */
#include <iostream>
//#include <vector>
#include <string.h>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        //空字符串可被认为是有效字符串
        if (s.length()==0) {
            return true;
        }
        //基数个符号 直接返回不能全不配对
        if(s.length()%2 == 1){
            return false;
        }
        int now_pre_iterator=0, j=now_pre_iterator+1;
        char now_pre = s[0];
        for( ; j<s.length(); j++){
            if (s[j]=='(' || s[j]=='{' || s[j]=='['){
                now_pre = s[j];
                now_pre_iterator++;
                continue;
            }
            //匹配， 配对消除
            if((s[j]==')' && now_pre=='(') || (s[j]=='}' && now_pre=='{') || (s[j]==']' && now_pre=='[')){
                //从字符串中消除已配对字符串，并递归调用该函数
                s.erase(now_pre_iterator, 2);
                if(s.length()==0){
                    return true;
                }
                now_pre_iterator = (now_pre_iterator == 0) ? 0 : now_pre_iterator-1;
                j = now_pre_iterator;
                now_pre = s[now_pre_iterator];
            }
            //不匹配，无效字符串，返回错误
            else {
                return false;
            }
        }
        if(j>=s.length()){
            return false;
        }
        return  false;
    }
};


int main(int argc, const char * argv[]) {
    Solution solution;
    string Input = "{[(){}]}";
    cout << "Input = " << Input << endl;
    cout << "Output = " <<  solution.isValid(Input) << endl;
}
