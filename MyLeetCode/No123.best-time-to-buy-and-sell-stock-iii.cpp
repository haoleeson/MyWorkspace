#include <iostream>
#include <vector>
using namespace std;

// 官解：动态规划
// 链接：https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-iii/solution/mai-mai-gu-piao-de-zui-jia-shi-ji-iii-by-wrnt/
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        // 设定初始值
        int buy1 = -prices[0], sell1 = 0;
        int buy2 = -prices[0], sell2 = 0;

        // 遍历第 i 天四种操作的结果
        for (int i = 1; i < n; ++i) {
            buy1 = max(buy1, -prices[i]);
            sell1 = max(sell1, buy1 + prices[i]);
            buy2 = max(buy2, sell1 - prices[i]);
            sell2 = max(sell2, buy2 + prices[i]);
        }

        return sell2;
    }
};

int main() {
    Solution solution;

    int arr1[] = {3, 3, 5, 0, 0, 3, 1, 4};
    vector<int> prices1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    int res1 = solution.maxProfit(prices1);
    cout << res1 << endl;

    int arr2[] = {1, 2, 3, 4, 5};
    vector<int> prices2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    int res2 = solution.maxProfit(prices2);
    cout << res2 << endl;

    int arr3[] = {7, 6, 4, 3, 1};
    vector<int> prices3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    int res3 = solution.maxProfit(prices3);
    cout << res3 << endl;

    return 0;
}
