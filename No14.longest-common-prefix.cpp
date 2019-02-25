/** 题目描述：
 * 14. 最长公共前缀
 * 编写一个函数来查找字符串数组中的最长公共前缀。
 * 如果不存在公共前缀，返回空字符串 ""。
 * 说明: 所有输入只包含小写字母 a-z 。

示例 1:

输入: ["flower","flow","flight"]
输出: "fl"
示例 2:

输入: ["dog","racecar","car"]
输出: ""
解释: 输出不存在公共前缀。
 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190225
 * */
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()<1){
            return "";
        }
        if(strs.size()==1){
            if (strs[0].length()==0) {
                return "";
            } else {
                return strs[0];
            }
        }
        int Ptr_i = 0; //公共前缀字母个数
        bool isEnd = false;
        for(int i=0; ; i++){
            for(int j=1; j<strs.size(); j++){
                if(strs[0][i] != strs[j][i] || strs[j].length() < i+1){
                    isEnd = true;
                    break;
                }
            }
            if(isEnd){
                break;
            }
            Ptr_i ++;
        }
        string result = (Ptr_i == 0) ? "" : strs[0].substr(0,Ptr_i);
        return result;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    vector<string> Input = {"flower","flow","flight"};
    cout << "Output = " <<  solution.longestCommonPrefix(Input) << endl;
}
