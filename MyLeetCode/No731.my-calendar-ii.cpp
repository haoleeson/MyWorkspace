#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

#include "myTools.h"

using namespace std;

// 官解：线段树 O(n log1e9)
// 链接：https://leetcode.cn/problems/my-calendar-ii/solution/wo-de-ri-cheng-an-pai-biao-ii-by-leetcod-wo6n/
class MyCalendarTwo {
public:
    MyCalendarTwo() {}

    // 更新线段树（区间和 + 向上更新（递归））
    // @Param start, end 日程安排起止时间
    // @Param val        更新操作 +1 or -1
    // @Param l, r       模拟开辟的有效数组范围 [l, r] eg. [0, 1e9]
    // @Param idx        完全二叉树 tree[idx] 下标  tree[1] 表示根节点 （左子节点 2*n, 右子节点 2*n + 1）
    void update(int start, int end, int val, int l, int r, int idx) {
        // 不在范围[l, r]，退出
        if (r < start || end < l) {
            return;
        }
        // 完全包含范围 [l, r]，增加 val
        if (start <= l && r <= end) {
            tree[idx].first += val;
            tree[idx].second += val;
        } else {
            // 二分递归更新线段树
            int mid = (l + r) >> 1;
            update(start, end, val, l, mid, 2 * idx);         // 更新左线段树
            update(start, end, val, mid + 1, r, 2 * idx + 1); // 更新右线段树
            // 求区间和
            tree[idx].first = tree[idx].second + max(tree[2 * idx].first, tree[2 * idx + 1].first);
        }
    }

    bool book(int start, int end) {
        // 尝试添加范围
        update(start, end - 1, 1, 0, 1e9, 1);
        // 存在大于 2 的子范围
        if (tree[1].first > 2) {
            // 减去范围
            update(start, end - 1, -1, 0, 1e9, 1);
            return false;
        }
        return true;
    }

private:
    unordered_map<int, pair<int, int>> tree;
};

// 思路2：差分数组 O(n^2)
// 链接：https://leetcode.cn/problems/my-calendar-ii/solution/wo-de-ri-cheng-an-pai-biao-ii-by-leetcod-wo6n/
class MyCalendarTwo2 {
public:
    MyCalendarTwo2() {}

    bool book(int start, int end) {
        int ans = 0;
        int maxBook = 0;
        cnt[start]++;
        cnt[end]--;
        for (auto& [_, freq] : cnt) {
            maxBook += freq;
            ans = max(maxBook, ans);
            if (maxBook > 2) {
                cnt[start]--;
                cnt[end]++;
                return false;
            }
        }
        return true;
    }

private:
    map<int, int> cnt;
};

// 思路1：直接遍历，记录所有日程安排起止时间 O(n^2)
class MyCalendarTwo1 {
public:
    MyCalendarTwo1() {}

    bool book(int start, int end) {
        // 若与二次记录仍有交集，返回失败
        for (auto& [l, r] : overlaps) {
            if (l < end && start < r) {
                return false;
            }
        }
        // 添加重合部分到二次记录
        for (auto& [l, r] : booked) {
            if (l < end && start < r) {
                overlaps.emplace_back(max(l, start), min(r, end));
            }
        }
        // 添加到一次记录
        booked.emplace_back(start, end);
        return true;
    }

private:
    // 首次记录
    vector<pair<int, int>> booked;
    // 二次记录
    vector<pair<int, int>> overlaps;
};

int main(void) {
    MyCalendarTwo myCalendar1;
    int arr1[][2] = {{10, 20}, {50, 60}, {10, 40}, {5, 15}, {5, 10}, {25, 55}};
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i) {
        bool tmp = myCalendar1.book(arr1[i][0], arr1[i][1]);
        cout << tmp << endl;
    }

    return 0;
}
