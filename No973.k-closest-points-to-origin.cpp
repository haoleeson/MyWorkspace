/**
 * No973. 最接近原点的 K 个点
 * 我们有一个由平面上的点组成的列表 points。需要从中找出 K 个距离原点 (0, 0) 最近的点。
 * （这里，平面上两点之间的距离是欧几里德距离。）
 * 你可以按任何顺序返回答案。除了点坐标的顺序之外，答案确保是唯一的。

示例 1：
输入：points = [[1,3],[-2,2]], K = 1
输出：[[-2,2]]

解释：
(1, 3) 和原点之间的距离为 sqrt(10)，
(-2, 2) 和原点之间的距离为 sqrt(8)，
由于 sqrt(8) < sqrt(10)，(-2, 2) 离原点更近。
我们只需要距离原点最近的 K = 1 个点，所以答案就是 [[-2,2]]。

示例 2：
输入：points = [[3,3],[5,-1],[-2,4]], K = 2
输出：[[3,3],[-2,4]]
（答案 [[-2,4],[3,3]] 也会被接受。）

提示：
1 <= K <= points.length <= 10000
-10000 < points[i][0] < 10000
-10000 < points[i][1] < 10000

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/k-closest-points-to-origin
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include "myTools.h"
using namespace std;

/**
 * 力扣官解：排序
 * 时间复杂度：O(n * log(n))
 * 空间复杂度：O(1)
 */
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(points.begin(), points.end(), [](const vector<int>& u, const vector<int>& v) {
            return u[0] * u[0] + u[1] * u[1] < v[0] * v[0] + v[1] * v[1];
        });
        return {points.begin(), points.begin() + K};
    }
};


/**
 * 方法1：维护前K个最小值，超时
 * 时间复杂度：O(K * n)
 * 空间复杂度：O(1)
 */
class Solution {
    inline int qurDist(int x, int y) {
        return x * x + y * y;
    }
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        int iterator, tmpDist, size = points.size();
        vector<vector<int>> ans(K, vector<int>(2, 0));
        vector<int> distances(K, INT32_MAX);
        vector<int> indexs(K, -1);
        distances[0] = qurDist(points[0][0], points[0][1]);
        indexs[0] = 0;

        // 遍历每个点
        for (int i = 1; i < size; ++i) {
            tmpDist = qurDist(points[i][0], points[i][1]);
            // 后挪
            iterator = K - 1;
            while (distances[iterator] > tmpDist && --iterator >= 0) {
                distances[iterator + 1] = distances[iterator];
                indexs[iterator + 1] = indexs[iterator];
            }
            if (iterator < K - 1) {
                distances[iterator + 1] = tmpDist;
                indexs[iterator + 1] = i;
            }
        }

        // 填充ans
        iterator = 0;
        for (int index : indexs) {
            ans[iterator][0] = points[index][0];
            ans[iterator][1] = points[index][1];
            ++iterator;
        }

        return ans;
    }
};

int main() {
    Solution solution;
    int K = 3;
    vector<vector<int>> points;
    vector<int> point(2, 0);
    point[0] = 3;
    point[1] = 3;
    points.push_back(point);
    point[0] = 5;
    point[1] = -1;
    points.push_back(point);
    point[0] = -2;
    point[1] = 4;
    points.push_back(point);
    point[0] = 2;
    point[1] = 1;
    points.push_back(point);
    vector<vector<int>> result = solution.kClosest(points, K);
    MyTools::printVec2D(result);
    return 0;
}
