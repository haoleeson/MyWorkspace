/** 题目描述：
 * 判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。
 * 
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
    bool isPalindrome(int x) {
        //负数一定不是回文数
        if (x < 0) {
            return false;
        }
        //缓存数字的每一位到容器
        vector<char> numList;
        while (x > 0){
            char tmp = x % 10 + 48;
            numList.push_back(tmp);
            x /= 10;
        }
        for(int i=0; i<numList.size()/2; i++){
            if(numList[i] != numList[numList.size()-1-i]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int Input = 123321;
    cout << "Input = " << Input << endl;
    cout << "Output = " <<  solution.isPalindrome(Input) << endl;
}
