#include <algorithm>
#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        int len = arr.size();
        sort(arr.begin(), arr.end());

        vector<vector<int>> res;
        int minDiff = INT_MAX;

        for (int i = 1; i < len; ++i) {
            int diff = arr[i] - arr[i - 1];
            if (diff == minDiff) {
                res.push_back({arr[i - 1], arr[i]});
            } else if (diff < minDiff) {
                vector<vector<int>> newRes;
                res.clear();
                res.swap(newRes);
                res.push_back({arr[i - 1], arr[i]});
                minDiff = diff;
            }
        }

        return res;
    }
};

int main(void) {
    Solution solution;
    int a1[] = {4, 2, 1, 3};
    vector<int> arr1(a1, a1 + sizeof(a1) / sizeof(int));
    vector<vector<int>> res1 = solution.minimumAbsDifference(arr1);
    MyTools::printVec2D(res1);

    int a2[] = {1, 3, 6, 10, 15};
    vector<int> arr2(a2, a2 + sizeof(a2) / sizeof(int));
    vector<vector<int>> res2 = solution.minimumAbsDifference(arr2);
    MyTools::printVec2D(res2);

    int a3[] = {3, 8, -10, 23, 19, -4, -14, 27};
    vector<int> arr3(a3, a3 + sizeof(a3) / sizeof(int));
    vector<vector<int>> res3 = solution.minimumAbsDifference(arr3);
    MyTools::printVec2D(res3);

    return 0;
}
