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
 * 解题思路：
 * 贪心先排最大身高（以k为下标插入），再递减身高
 */
class Solution {
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
    vector<vector<int>> people;
    vector<int> pair(2, 0);
    pair[0] = 7;
    pair[1] = 0;
    people.push_back(pair);
    pair[0] = 4;
    pair[1] = 4;
    people.push_back(pair);
    pair[0] = 7;
    pair[1] = 1;
    people.push_back(pair);
    pair[0] = 5;
    pair[1] = 2;
    people.push_back(pair);
    pair[0] = 6;
    pair[1] = 1;
    people.push_back(pair);
    pair[0] = 5;
    pair[1] = 0;
    people.push_back(pair);
    vector<vector<int>> result = solution.reconstructQueue(people);
    MyTools::printVec2D(result);
    return 0;
}
