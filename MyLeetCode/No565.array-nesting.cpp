#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;
// 官解：原地标记（标记为不存在下标 n）
// 链接：https://leetcode.cn/problems/array-nesting/solution/shu-zu-qian-tao-by-leetcode-solution-7ur3/
class Solution {
public:
    int arrayNesting(vector<int>& nums) {
        int ans = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            while (nums[i] < n) {
                int num = nums[i];
                nums[i] = n; // 标记为不存在下标 n
                i = num;
                ++cnt;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};

// 官解：遍历数组
// 链接：https://leetcode.cn/problems/array-nesting/solution/shu-zu-qian-tao-by-leetcode-solution-7ur3/
class Solution1 {
public:
    int arrayNesting(vector<int>& nums) {
        int ans = 0, n = nums.size();
        vector<int> vis(n);
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            while (!vis[i]) {
                vis[i] = true;
                i = nums[i];
                ++cnt;
            }
            ans = max(ans, cnt);
        }
        return ans;
    }
};

class Solution0 {
public:
    int arrayNesting(vector<int>& nums) {
        int lenN = nums.size();
        if (lenN < 2) {
            return lenN;
        }
        int res = 0;

        // 是否访问标记
        bool* accessedFlg = new bool[lenN]{false};
        accessedFlg[0] = true;

        // 遍历起始下标，模拟访问
        for (int i = 0; i < lenN; ++i) {
            int cnt = 0;
            while (!accessedFlg[i]) {
                accessedFlg[i] = true;
                i = nums[i];
                ++cnt;
            }
            if (cnt > res) {
                res = cnt;
            }
        }

        delete[] accessedFlg;
        return res;
    }
};

int main(void) {
    Solution solution;

    int arr1[] = {5, 4, 0, 3, 1, 6, 2};
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    int res1 = solution.arrayNesting(nums1);
    cout << endl << "res1: " << res1 << endl;

    return 0;
}
