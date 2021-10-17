/** 题目描述：
 * 121. 买卖股票的最佳时机
 * 给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。
 * 如果你最多只允许完成一笔交易（即买入和卖出一支股票），设计一个算法来计算你所能获取的最大利润。

 * 注意: 你不能在买入股票前卖出股票。

  示例 1:
输入: [7,1,5,3,6,4]
输出: 5
解释: 在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格。

  示例 2:
输入: [7,6,4,3,1]
输出: 0
解释: 在这种情况下, 没有交易完成, 所以最大利润为 0。

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190318
 * */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //特殊值
        if (prices.size() < 2) {
            return 0;
        }
        int sub_Profit=prices[1] - prices[0], max_Profit = sub_Profit, tmp=0, diff;
        for (int i=1; i<prices.size()-1; i++) {
            diff = prices[i+1] - prices[i];
            //求出今天和明天的利润值，得到N-1的利润值，求解最大子序列和
            if (sub_Profit + diff < diff) {
                sub_Profit = diff;
            } else {
                sub_Profit += diff;
            }
            if (sub_Profit > max_Profit) {
                max_Profit = sub_Profit;
            }
        }
        return max_Profit < 0 ? 0 : max_Profit;
    }
};
int main(int argc, const char * argv[]) {
    Solution s;
    vector<int> Input = {7,6,4,3,1};
    cout << "Output:" << s.maxProfit(Input) << endl;
    for(int i=0; i<Input.size(); i++){
        cout << Input[i] << " ";
    }
    cout << endl;
}

