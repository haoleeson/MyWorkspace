#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/**
 * No84. 柱状图中最大的矩形 （单调栈）
 * 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
 * 求在该柱状图中，能够勾勒出来的矩形的最大面积。
 *             ▇
 *          ▇ ▇
 *          ▇ ▇
 *          ▇ ▇    ▇
 *    ▇    ▇ ▇ ▇ ▇
 *    ▇ ▇ ▇ ▇ ▇ ▇
 * 以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。
 * 最大矩形面积为第[2,3]柱状构成的矩形，面积为 10 单位。
 * @return
 */

/**
 * 力扣官解：单调栈
 * 利用单调栈，用O(n)时间复杂度，分别求出以每个元素height[i]为高的矩形的  左（右）边界所在下标
 * 再O(n)求每个矩形的最大面积，并找到最大值
 */
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        vector<int> leftIndex(size), rightIndex(size);// 记录左右边界下标
        stack<int> mono_stack;

        // 从左向右遍历，对以第i个柱子为高的，求最左端柱子index (最终矩形的左边界，第一个小于heights[i])
        for (int i = 0; i < size; ++i) {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                mono_stack.pop();// 出栈比当前 i 大的下标（其不可能是左边界）
            }
            leftIndex[i] = (mono_stack.empty() ? -1 : mono_stack.top());// 记录左边界
            mono_stack.push(i);// 入栈下标
        }

        // 从右向左遍历，对以第i个柱子为高的，求最右端柱子index (最终矩形的右边界，第一个小于heights[i])
        mono_stack = stack<int>();
        for (int i = size - 1; i >= 0; --i) {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
                mono_stack.pop();// 出栈比当前 i 大的下标（其不可能是右边界）
            }
            rightIndex[i] = (mono_stack.empty() ? size : mono_stack.top());// 记录右边界
            mono_stack.push(i);
        }

        int maxArea = 0, tmpArea = 0;
        for (int i = 0; i < size; ++i) {
            tmpArea = (rightIndex[i] - leftIndex[i] - 1) * heights[i];
            if (tmpArea > maxArea) {
                maxArea = tmpArea;
            }
        }
        return maxArea;
    }
};

/**
 * 解题思路：暴力枚举所有子序列
 * O(n^2)，超时
 */
class Solution0 {
public:
    // 按宽枚举 O(n^2)
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        int tmpHigh, tmpArea, maxArea = 0;

        // 枚举所有子序列 [i, j]
        for (int i = 0; i < size; ++i) {
            tmpHigh = INT32_MAX;
            for (int j = i; j < size; ++j) {
                tmpHigh = min(tmpHigh, heights[j]);
                tmpArea = (j - i + 1) * tmpHigh;
                if (tmpArea > maxArea) {
                    maxArea = tmpArea;
                }
            }
        }
        return maxArea;
    }
    // 按高枚举 O(n^2)
    int largestRectangleArea2(vector<int>& heights) {
        int size = heights.size();

        // 确定一根柱子为高（即最矮），向两边扩展
        int leftIndex = 0, rightIndex = 0, tmpArea = 0, maxArea = 0;
        for (int i = 0; i < size; ++i) {
            leftIndex = i - 1;
            rightIndex = i + 1;
            // 向两边扩展，指导小于高度的
            while (leftIndex >= 0 && heights[leftIndex] >= heights[i]) {
                --leftIndex;
            }
            while (rightIndex < size && heights[rightIndex] >= heights[i]) {
                ++rightIndex;
            }
            // 消除多减和多加
            ++leftIndex;
            --rightIndex;
            tmpArea = heights[i] * (rightIndex - leftIndex + 1);
            if (tmpArea > maxArea) {
                maxArea = tmpArea;
            }
        }
        return maxArea;
    }
};

int main() {
    Solution solution;
    int arr[] = {2,1,5,6,2,3};
    vector<int> heights(arr, arr + sizeof(arr)/sizeof(int));
    cout << solution.largestRectangleArea(heights) << endl;
    return 0;
}
