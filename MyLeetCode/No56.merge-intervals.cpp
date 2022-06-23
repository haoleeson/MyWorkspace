#include <algorithm>
#include <iostream>
#include <vector>

#include "myTools.h"
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), mycmp);

        int i = 0;
        while (i < intervals.size()) {
            int j = i + 1;
            int tmpEnd = intervals[i][1];
            while (j < intervals.size() && intervals[j][0] <= tmpEnd) {
                tmpEnd = max(tmpEnd, intervals[j][1]);
                j++;
            }
            --j;

            // merge
            if (j > i) {
                intervals[i][1] = tmpEnd;
                intervals.erase(intervals.begin() + i + 1, intervals.begin() + j + 1);
            }
            ++i;
        }

        return intervals;
    }

private:
    static bool mycmp(vector<int>& a, vector<int>& b) { return a[0] != b[0] ? a[0] < b[0] : a[1] < b[1]; }
};

int main(void) {
    Solution solution;

    int arr1[][2] = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> intervals1;
    for (int i = 0; i < 4; ++i) {
        vector<int> tmp(arr1[i], arr1[i] + 2);
        intervals1.push_back(tmp);
    }
    vector<vector<int>> res1 = solution.merge(intervals1);
    MyTools::printVec2D(res1);

    int arr2[][2] = {{1, 4}, {4, 5}};
    vector<vector<int>> intervals2;
    for (int i = 0; i < 2; ++i) {
        vector<int> tmp(arr2[i], arr2[i] + 2);
        intervals2.push_back(tmp);
    }
    vector<vector<int>> res2 = solution.merge(intervals2);
    MyTools::printVec2D(res2);

    return 0;
}
