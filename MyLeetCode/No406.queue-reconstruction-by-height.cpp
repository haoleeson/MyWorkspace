/**
 * No406. 根据身高重建队列 (贪心)
 * 假设有打乱顺序的一群人站成一个队列。 每个人由一个整数对(h, k)表示，其中h是这个人的身高，k是排在这个人前面且身高大于或等于h的人数。 编写一个算法来重建这个队列。

注意：
总人数少于1100人。

示例
输入:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
输出:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/queue-reconstruction-by-height
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "myTools.h"
using namespace std;

/**
 * 时间复杂度：O(n * log(n))
 */
class Solution {
    // 重写比较函数
    static bool myComp(const vector<int>& a, const vector<int>& b) {
        return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
    }
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int>> ans;
        // 自定义倒序排序 O(n * log(n))
        sort(people.begin(), people.end(), myComp);
        // 按下标顺序插入
        for (vector<int>& tmp : people) {
            ans.insert(ans.begin() + tmp[1], tmp);
        }
        return ans;
    }
};

/**
 * 解题思路：
 * 贪心先排最大身高（以k为下标插入），再递减身高
 */
class Solution1 {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int size = people.size(), tmpMaxHigh;
        vector<vector<int>> ans;
        sort(people.begin(), people.end());
        for (int i = size - 1; i > -1; --i) {
            tmpMaxHigh = people[i][0];
            while (i > 0 && people[i - 1][0] == tmpMaxHigh) {
                --i;
            }
            for (int j = i; j < size && people[j][0] == tmpMaxHigh; ++j) {
                ans.insert(ans.begin() + people[j][1], people[j]);
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    int arr[6][2] = {
            {7, 0},
            {4, 4},
            {7, 1},
            {5, 0},
            {6, 1},
            {5, 2}
    };
    vector<vector<int>> people(6, vector<int>(2));
    for (int i = 0; i < 6; ++i) {
        people[i][0] = arr[i][0];
        people[i][1] = arr[i][1];
    }
    vector<vector<int>> result = solution.reconstructQueue(people);
    MyTools::printVec2D(result);
    return 0;
}
