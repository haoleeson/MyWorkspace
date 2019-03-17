/** 题目描述：
 * 118. 杨辉三角
 * 给定一个非负整数 numRows，生成杨辉三角的前 numRows 行。
 * 在杨辉三角中，每个数是它左上方和右上方的数的和。

示例:

输入: 5
输出:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190317
 * */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<int> tmp(1, 1);
        vector<vector<int>> Result(numRows, tmp);
        for(int i=1; i<numRows; i++) {
            for(int j=1; j<i; j++) {
                Result[i].push_back(Result[i-1][j-1] + Result[i-1][j]);
            }
            Result[i].push_back(1);
        }
        return Result;
    }
};

int main(int argc, const char * argv[]) {
    Solution s;
    vector<vector<int>> result;
    result = s.generate(5);
    cout << "Output:" << endl;
    for(int i=0; i<result.size(); i++){
        for(int j=0; j<result[i].size(); j++){
            cout << result[i][j] << " ";
        }
        cout << endl;
    }
}

