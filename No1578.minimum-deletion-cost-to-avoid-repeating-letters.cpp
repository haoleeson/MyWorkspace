/**
 * No1578. 避免重复字母的最小删除成本 （贪心）
 * 给你一个字符串 s 和一个整数数组 cost ，其中 cost[i] 是从 s 中删除字符 i 的代价。
 * 返回使字符串任意相邻两个字母不相同的最小删除成本。
 * 请注意，删除一个字符后，删除其他字符的成本不会改变。

示例 1：
输入：s = "abaac", cost = [1,2,3,4,5]
输出：3
解释：删除字母 "a" 的成本为 3，然后得到 "abac"（字符串中相邻两个字母不相同）。

示例 2：
输入：s = "abc", cost = [1,2,3]
输出：0
解释：无需删除任何字母，因为字符串中不存在相邻两个字母相同的情况。

示例 3：
输入：s = "aabaa", cost = [1,2,3,4,1]
输出：2
解释：删除第一个和最后一个字母，得到字符串 ("aba") 。

提示：
s.length == cost.length
1 <= s.length, cost.length <= 10^5
1 <= cost[i] <=10^4
s 中只含有小写英文字母

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/minimum-deletion-cost-to-avoid-repeating-letters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int ans = 0, len = s.length();
        for (int i = 0; i < len - 1; ++i) {
            // 连续字符，增加依次删除的最小成本
            if (s[i] == s[i + 1]) {
                ans += min(cost[i], cost[i + 1]);
                // 将较大成本移到后面，方便下次比较
                if (cost[i + 1] < cost[i]) {
                    cost[i + 1] = cost[i];
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution solution;
    string strs[] = {
            "abaac",
            "abc",
            "aabaa"};
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {1,2,3};
    int arr3[] = {1,2,3,4,1};
    vector<vector<int>> costs;
    vector<int> cost1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    vector<int> cost2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    vector<int> cost3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    costs.emplace_back(cost1);
    costs.emplace_back(cost2);
    costs.emplace_back(cost3);
    for (int i = 0; i < 3; ++i) {
        cout << solution.minCost(strs[i], costs[i]) << endl;
    }
    return 0;
}
