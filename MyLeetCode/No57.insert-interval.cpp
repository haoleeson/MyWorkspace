#include <iostream>
#include <vector>
#include "myTools.h"
using namespace std;

/**
 * No57. 插入区间
 * 给出一个无重叠的 ，按照区间起始端点排序的区间列表。
在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

示例1：
输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
输出：[[1,5],[6,9]]

示例2：
输入：intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
输出：[[1,2],[3,10],[12,16]]
解释：这是因为新的区间 [4,8] 与 [3,5],[6,7],[8,10]重叠。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/insert-interval
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
    int* m_parts;
    int m_iterator = 0;
    bool m_openStat = false;
    inline void pushOpen(int val) {
        // 若之前状态为关，正常输入开。若为开，则此次开无效
        if (!m_openStat) {
            m_parts[m_iterator++] = val;
            m_openStat = true;
        }
    }
    inline void pushClose(int val) {
        // 若之前状态为开，则正常关。若为关，则之前的关无效
        if (!m_openStat) {
            --m_iterator;
        }
        m_parts[m_iterator++] = val;
        m_openStat = false;
    }
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int N = intervals.size() * 2, start = newInterval[0], end = newInterval[1], val;
        bool usedStart = false, usedEnd = false;
        m_parts = new int[N + 2]{0};

        for (int i = 0; i < N; ++i) {
            val = intervals[i / 2][i % 2];
            // 过滤无效值（：落在newInterval区间内的值）
            if (start <= val && val <= end) {
                continue;
            }

            // Interval 区间 优先
            if (!usedStart && start < val) {
                pushOpen(start);
                usedStart = true;
            }
            if (!usedEnd && end < val) {
                pushClose(end);
                usedEnd = true;
            }

            // 正常输入原区段
            if (i % 2 == 0) {
                // 输入开
                pushOpen(val);
            } else {
                // 输入关
                pushClose(val);
            }
        }

        if (!usedStart) {
            pushOpen(start);
        }
        if (!usedEnd) {
            pushClose(end);
        }

        vector<int> part(2, 0);
        vector<vector<int>> ans(m_iterator / 2, part);
        // 填充值
        for (int i = 0; i < m_iterator; ++i) {
            ans[i / 2][i % 2] = m_parts[i];
        }

        delete []m_parts;
        return ans;
    }
};


int main() {
    Solution solution;
    vector<vector<int>> intervals;
    vector<int> part(2, 0);
    part[0] = 1;
    part[1] = 2;
    intervals.push_back(part);
    part[0] = 3;
    part[1] = 5;
    intervals.push_back(part);
    part[0] = 6;
    part[1] = 7;
    intervals.push_back(part);
    part[0] = 8;
    part[1] = 10;
    intervals.push_back(part);
    part[0] = 12;
    part[1] = 16;
    intervals.push_back(part);
    part[0] = 4;
    part[1] = 8;
    vector<int> newInterval(part);

    vector<vector<int>> result = solution.insert(intervals, newInterval);

    MyTools::printVec2D(result);
    return 0;
}