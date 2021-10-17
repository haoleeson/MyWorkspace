#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * No15. 三数之和（双指针）
 * 给你一个包含 n 个整数的数组nums，判断nums中是否存在三个元素 a，b，c ，
 * 使得a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例：
给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/3sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/**
 * 解题思路：排序后 选定最左端元素，双指针向内搜索
 */
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int size = nums.size(), tmp = 0, lastLeftNum = INT32_MIN, leftIndex = 0, midIndex = 0, rightIndex = 0;
        vector<vector<int>> ans;
        vector<int> tmpVec(3);

        // 排序
        sort(nums.begin(),nums.end());

        // 选定组合的最左端元素
        for (leftIndex = 0; leftIndex < size - 2; ++leftIndex) {
            // 若与上一次最左端元素值相等（已搜索过），跳过
            if (nums[leftIndex] == lastLeftNum) {
                continue;
            }
            lastLeftNum = nums[leftIndex];

            // 加速，若加上最右两个最大组合仍小于0，跳过
            if (nums[leftIndex] + nums[size - 2] + nums[size - 1] < 0) {
                continue;
            }
            // 加速，若加上紧挨最左元素的最小组合仍大于0，则后面不必判断
            if (nums[leftIndex] + nums[leftIndex + 1] + nums[leftIndex + 2] > 0) {
                break;
            }

            // 初始化中间和左端两个指针，相向而行搜索可能的组合
            midIndex = leftIndex + 1;
            rightIndex = size - 1;
            while ( midIndex < rightIndex ) {
                tmp = nums[leftIndex] + nums[midIndex] + nums[rightIndex];
                // 找到这三个数，添加到ans
                if (tmp == 0) {
                    tmpVec[0] = nums[leftIndex];
                    tmpVec[1] = nums[midIndex];
                    tmpVec[2] = nums[rightIndex];
                    ans.push_back(tmpVec);
                    // 针对最左端选定，可能不止一种组合，继续搜索（跳过已选择的值）
                    tmp = nums[midIndex];
                    while (midIndex < rightIndex && nums[midIndex] == tmp) {
                        ++midIndex;
                    }
                    tmp = nums[rightIndex];
                    while (midIndex < rightIndex && nums[rightIndex] == tmp) {
                        --rightIndex;
                    }
                    if (midIndex == rightIndex) {
                        break;// 已找完
                    }
                    continue;
                } else if (tmp < 0) {
                    // 和小于0，rightIndex已最大，只能增加 midIndex
                    ++midIndex;
                } else {
                    // 和大于0，midIndex 已最小，只能减小 rightIndex
                    --rightIndex;
                }
            }
        }
        return ans;
    }
};

void printVector(vector<vector<int>> vec2D) {
    int size = vec2D.size();
    cout << "total size = " << size << endl;
    for (int i = 0; i < size; ++i) {
        cout << "[";
        for (int j = 0; j < vec2D[i].size() - 1; ++j) {
            cout << vec2D[i][j] << ",";
        }
        cout << vec2D[i][vec2D[i].size() - 1] << "]" << endl;
    }
}

int main() {
    Solution solution;
    int arr[] = {-1, 0, 1, 2, -1, -4};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));

    vector<vector<int>> result = solution.threeSum(nums);
    printVector(result);

    return 0;
}
