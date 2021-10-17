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
        int max_Profit=0, max_iterator=0, min_iterator=0;
        /**探索最低点和最高点下标*/
        for (int i=1; i<prices.size(); i++) {
            if (prices[i] >= prices[max_iterator]) {
                max_iterator = i;
            }
            if (prices[i] < prices[min_iterator]) {
                min_iterator = i;
            }
        }
        /**取巧*/
        if (max_iterator > min_iterator) {
            return prices[max_iterator] - prices[min_iterator];
        }
        //常规方式O(n^2)
        for (int i=0; i<prices.size()-1; i++) {
            /**取巧, 直接比较最大值减 ->> 加速*/
            if ((prices[max_iterator] - prices[i]) <= max_Profit) {
                //无需比较
                continue;
            } else if (i < max_iterator) {
                //最大值有效（下标能取到），更新 max_Profit
                max_Profit = prices[max_iterator] - prices[i];
                continue;
            } else {
                //最大值不能取到，老实计算次最大值
                int second_max = prices[i+1];
                for (int j=i+2; j<prices.size(); j++) {
                    if (second_max < prices[j]) {
                        second_max = prices[j];
                    }
                }
                if ((second_max - prices[i]) > max_Profit) {
                    max_Profit = second_max - prices[i];
                }
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

