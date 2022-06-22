#include<iostream>
#include<vector>
#include<stack>
using namespace std;

// 官解1: O(n)
// 分别向左、向右遍历 计算投影（每个柱子 i 两侧的最大高度）
// 两个投影重合部分 减去 柱子自身高度，即为最终在柱 i 上方所盛的最大雨水体积，累加每个柱子所盛的最大雨水体积即为总体积
class Solution1 {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if (len < 3) {
            return 0;
        }

        int* leftMax = new int[len]{0};
        leftMax[0] = height[0];
        int* rightMax = new int[len]{0};
        rightMax[len - 1] = height[len - 1];

        // 正向遍历，计算向右投影
        for (int i = 1; i < len; ++i) {
            leftMax[i] = max(height[i], leftMax[i - 1]);
        }

        // 逆向遍历，计算向左投影
        for (int i = len - 2; i > -1; --i) {
            rightMax[i] = max(height[i], rightMax[i + 1]);
        }

        // 累加每个柱子上方所盛雨水体积
        int sumV = 0;
        for (int i = 0; i < len; ++i) {
            sumV += min(leftMax[i], rightMax[i]) - height[i];
        }

        return sumV;
    }
};

// 官解2：单调栈 O(n)
class Solution2 {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        stack<int> stk;
        int n = height.size();
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && height[i] > height[stk.top()]) {
                int top = stk.top();
                stk.pop();
                if (stk.empty()) {
                    break;
                }
                int left = stk.top();
                int currWidth = i - left - 1;
                int currHeight = min(height[left], height[i]) - height[top];
                ans += currWidth * currHeight;
            }
            stk.push(i);
        }
        return ans;
    }
};

// 官解3：双指针 O(n^2)
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]);
            rightMax = max(rightMax, height[right]);
            if (height[left] < height[right]) {
                ans += leftMax - height[left];
                ++left;
            } else {
                ans += rightMax - height[right];
                --right;
            }
        }
        return ans;
    }
};


// My 动态规划： O(n^2)
class Solution0 {
public:
    int trap(vector<int>& height) {
        int len = height.size();

        // dpTab[i] 表示前 i 个柱子能接的雨水量
        int* dpTab = new int[len]{0};
        dpTab[0] = 0;
        // sumV[i] 表示前 i 个柱子的体积和
        int* sumV = new int[len]{0};
        sumV[0] = height[0];

        for (int i = 1; i < len; ++i) {
            sumV[i] = height[i] + sumV[i - 1];

            // 高度不超过前一柱子，接雨水体积不变，跳过
            if (height[i] <= height[i - 1]) {
                dpTab[i] = dpTab[i - 1];
                continue;
            }

            // 向前找到“第一个高度不低于 height[i] 的” 或 “最大的” 柱子 height[j]
            int j = i - 2;
            int tmpMax = 0;
            int tmpMaxIndex;
            while (j > -1) {
                if (height[j] > tmpMax) {
                    tmpMax = height[j];
                    tmpMaxIndex = j;
                }
                if (height[j] >= height[i]) {
                    break;
                }
                --j;
            }

            // 未找到，或不超过前一柱子，接雨水体积不变，跳过
            if (tmpMax <= height[i - 1]) {
                dpTab[i] = dpTab[i - 1];
                continue;
            }

            // 增量增加雨水量 = (tmpMaxIndex, i] 区间两侧边所盛水体积 - 区间内所有柱子的体积和
            dpTab[i] = min(height[i], tmpMax) * (i - tmpMaxIndex - 1) - (sumV[i-1] - sumV[tmpMaxIndex]) + dpTab[tmpMaxIndex];
        }

        return dpTab[len - 1];
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> height1(arr1, arr1 + sizeof(arr1)/sizeof(int));
    cout << solution.trap(height1) << endl;

    int arr2[] = {4,2,0,3,2,5};
    vector<int> height2(arr2, arr2 + sizeof(arr2)/sizeof(int));
    cout << solution.trap(height2) << endl;

    return 0;
}
