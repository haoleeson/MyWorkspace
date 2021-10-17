/**
 * 最大乘积_牛客网
 * 题目描述：
给定一个无序数组，包含正数、负数和0，要求从中找出3个数的乘积，使得乘积最大，要求时间复杂度：O(n)，空间复杂度：O(1)

 输入描述:
无序整数数组A[n]

 输出描述:
满足条件的最大乘积

 示例1
输入:
3 4 1 2
输出:
24
 *
 * coder: eisenhao
 * 20190320
 * */

#include <iostream>

using namespace std;

int main(void)
{
    //获取输入值
    int NumsOfArray;
    cin >> NumsOfArray;
    vector<int> InputNums(NumsOfArray);
    for (int i=0; i<NumsOfArray; i++) {
        cin >> InputNums[i];
    }
    //求 3个 最大正数 和 2个最小负数
    int maxPositiveNum[3] = {0, 0, 0};
    int minNegativeNums[2] = {0, 0};
    for (int i=0, tmp; i<InputNums.size(); i++) {
        tmp = InputNums[i];
        //大于最大正数
        if (tmp >= maxPositiveNum[0]) {
            maxPositiveNum[2] = maxPositiveNum[1];//第三大
            maxPositiveNum[1] = maxPositiveNum[0];//第二大
            maxPositiveNum[0] = tmp;//最大
        }
            //大于第二大正数
        else if (tmp >= maxPositiveNum[1]) {
            maxPositiveNum[2] = maxPositiveNum[1];//第三大
            maxPositiveNum[1] = tmp;//第二大
        }
            //大于第三大正数
        else if (tmp >= maxPositiveNum[2]) {
            maxPositiveNum[2] = tmp;//第三大
        }
            //小于最小负数
        else if (tmp <= minNegativeNums[0]) {
            minNegativeNums[1] = minNegativeNums[0];//次小负数
            minNegativeNums[0] = tmp;//最小负数
        }
            //小于最次小负数
        else if (tmp <= minNegativeNums[1]) {
            minNegativeNums[1] = tmp;//次小负数
        }
    }
    long long int result1 = (long long int)maxPositiveNum[0]*maxPositiveNum[1]*maxPositiveNum[2],
                  result2 = (long long int)minNegativeNums[0]*minNegativeNums[1]*maxPositiveNum[0];

    result1 = result1 > result2 ? result1 : result2;
    cout << result1;
    return 0;
}

