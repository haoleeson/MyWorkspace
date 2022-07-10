#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 贪心：每次减去 最大 和次大值
class Solution {
public:
    int fillCups(vector<int>& amount) {
        vector<int> arr(amount);
        int res = 0;

        while (arr[0] > 0 || arr[1] > 0 || arr[2] > 0) {
            // 排序获取最大两个数
            if (arr[0] < arr[2]) {
                swap(arr[0], arr[2]);
            }
            if (arr[1] < arr[2]) {
                swap(arr[1], arr[2]);
            }
            if (arr[0] < arr[1]) {
                swap(arr[0], arr[1]);
            }

            // 减去最大的两个数
            if (arr[0] > 0) --arr[0];
            if (arr[1] > 0) --arr[1];

            ++res;
        }
        return res;
    }
};

int main(void) {
    Solution solution;

    int a1[] = {1, 4, 2};
    vector<int> amount1(a1, a1 + sizeof(a1) / sizeof(int));
    int res1 = solution.fillCups(amount1);
    cout << res1 << endl;

    int a2[] = {5, 4, 4};
    vector<int> amount2(a2, a2 + sizeof(a2) / sizeof(int));
    int res2 = solution.fillCups(amount2);
    cout << res2 << endl;

    return 0;
}
