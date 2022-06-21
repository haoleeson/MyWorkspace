#include<iostream>
#include<vector>
using namespace std;

// 自底向上（迭代）
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 初始化 dp table
        int* dpTab = new int[amount + 1];
        dpTab[0] = 0;
        for (int i = 1; i < amount + 1; ++i) {
            dpTab[i] = INT_MAX;

        }

        for (int i = 1; i <= amount; ++i) {
            int minChoose = INT_MAX;
            for (int& coin : coins) {
                int subAmount = i - coin;
                if (subAmount >= 0 && dpTab[subAmount] != -1 && dpTab[subAmount] != INT_MAX && dpTab[subAmount] < minChoose) {
                    minChoose = dpTab[subAmount];
                }
            }
            if (minChoose != INT_MAX) {
                dpTab[i] = min(dpTab[i], minChoose + 1);
            } else {
                dpTab[i] = -1;
            }
        }

        return dpTab[amount];
    }
};

// 自顶向下（递归） + 备忘录；，dp() 执行 15 次；
class Solution2 {
public:
    int coinChange(vector<int>& coins, int amount) {
        memo = new int[amount + 1]{0};
        int res = dp(coins, amount);
        cout << "dp run times: " << dpRunTimes << endl;
        return res;
    }

private:
    int dpRunTimes = 0;
    int* memo;

    int dp (vector<int>& coins, int amount) {
        if (memo[amount] != 0) {
            return memo[amount];
        }

        dpRunTimes++;

        if (amount == 0) {
            return 0;
        } else if (amount == 1) {
            return 1;
        } else if (amount < 0) {
            return -1;
        }


        int minChoose = INT_MAX;
        for (int& coin: coins) {
            int dp_i = dp(coins, amount - coin);

            if (dp_i != -1 && dp_i < minChoose) {
                minChoose = dp_i;
            }
        }

        if (minChoose != INT_MAX) {
            memo[amount] = minChoose + 1;
            return minChoose + 1;
        }

        return -1;
    }
};

// 自顶向下（递归），dp() 执行 544 次；
class Solution1 {
public:
    int coinChange(vector<int>& coins, int amount) {
        int res = dp(coins, amount);
        cout << "dp run times: " << dpRunTimes << endl;
        return res;
    }

private:
    int dpRunTimes = 0;

    int dp (vector<int>& coins, int amount) {
        dpRunTimes++;

        if (amount == 0) {
            return 0;
        } else if (amount == 1) {
            return 1;
        } else if (amount < 0) {
            return -1;
        }

        int minChoose = INT_MAX;
        for (int& coin: coins) {
            int dp_i = dp(coins, amount - coin);

            if (dp_i != -1 && dp_i < minChoose) {
                minChoose = dp_i;
            }
        }

        return (minChoose != INT_MAX) ? minChoose + 1 : -1;
    }
};

int main(void) {
    Solution solution;
    int arr1[] = {1, 2, 5};
    vector<int> coins1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    cout << solution.coinChange(coins1, 11) << endl;

    return 0;
}
