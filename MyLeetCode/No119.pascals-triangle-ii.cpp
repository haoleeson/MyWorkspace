/** 题目描述：
 * 119. 杨辉三角 II
 * 给定一个非负索引 k，其中 k ≤ 33，返回杨辉三角的第 k 行。
 * 在杨辉三角中，每个数是它左上方和右上方的数的和。

示例:

输入: 3
输出: [1,3,3,1]


     [1],        0
    [1,1],       1
   [1,2,1],      2
  [1,3,3,1],     3
 [1,4,6,4,1]     4     n=4
k=  1 2 3

[1,5,10,10,5,1]  n=5         2
k= 1 2  3  4

[1,6,15,20,15,6,1]  n=6      3
k= 1 2  3  4  5

 【备注】输入值不超过33

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190317
 * */
#include <iostream>
#include <vector>

using namespace std;

/**
 * 解题：杨辉三角数学性质
 * https://www.cnblogs.com/henry-1202/p/about_combinatorial_number.html
 * 因为一般的杨辉三角是用上面提到的组合数递推公式来算出每一项的系数的，效率O(n^2)，如果要快速求(a+b)n的值可以用二项式定理O(n)求出
 * 可以得到：
        C(k, n) = (n−k+1) / k ∗ C(k−1, n)
所以也可以用这个公式来O(n)计算出杨辉三角某一行的值
 * */

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        if (rowIndex==0) {
            return vector<int> ({1});
        }
        if (rowIndex==1) {
            return vector<int> ({1,1});
        }
        vector<int> result (rowIndex+1, 1);
        //二项式定理O(n) :    C(k, n) = (n−k+1) ∗ C(k−1, n) / k
        result[1] = rowIndex;
        result[rowIndex-1] = rowIndex;
        for (int i=2; i<rowIndex/2 + 1; i++) {
            long long tmp = (long long)(rowIndex - i + 1) * result[i-1] / i ;
            result[i] = (int)tmp;
            //对称原理
            result[rowIndex-i] = result[i];
        }
        return result;
    }
};

int main(int argc, const char * argv[]) {
    Solution s;
    vector<int> result;
    result = s.getRow(33);
    cout << "Output:" << endl;
    for(int i=0; i<result.size(); i++){
        cout << result[i] << " ";
    }
    cout << endl;
}

