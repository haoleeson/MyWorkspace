#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

/**
 * No347. 前 K 个高频元素
 * 给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

示例 1:
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例 2:
输入: nums = [1], k = 1
输出: [1]

提示：
你可以假设给定的k总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
你的算法的时间复杂度必须优于 O(n log n) ,n是数组的大小。
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的。
你可以按任意顺序返回答案。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/top-k-frequent-elements
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


// 自定义比较函数
bool cmp(pair<int, int>a, pair<int, int>b) {
    return a.second > b.second || (a.second == b.second && a.first < b.first);
}

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        int tmp, size = nums.size();
        vector<int> ans;
        vector<pair<int, int>> orderNumVec;
        map<int, int> numsTimes;
        map<int, int>::iterator it;
        sort(nums.begin(), nums.end());

        // 统计次数
        for (int i = 0; i < size; ++i) {
            it = numsTimes.find(nums[i]);
            // 找到
            if (it != numsTimes.end()) {
                ++it->second;
            } else {
                numsTimes.insert(pair<int, int>(nums[i], 1));
            }
        }

        // 按 value 排序
        for (map<int, int>::iterator it = numsTimes.begin(); it != numsTimes.end(); ++it) {
            orderNumVec.push_back(pair<int, int>(it->first, it->second));
        }
        sort(orderNumVec.begin(), orderNumVec.end(), cmp);

        // out
        for (int i = 0; i < k; ++i) {
            tmp = orderNumVec[i].first;
            ans.push_back(tmp);
        }
        return ans;
    }
};

template<typename T>
void printVec2D(vector<T> vec) {
    int size = vec.size();
    cout << "[";
    if (size > 0) {
        cout << vec[0];
        for (int i = 1; i < size; ++i) {
            cout << ", " << vec[i];
        }
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;
    int arr[] = {5,1,1,4,4,4,5};
    int k = 2;
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));
    vector<int> result = solution.topKFrequent(nums, k);
    printVec2D(result);
    return 0;
}