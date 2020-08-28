#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * No18. 四数之和（双指针）
 * 给定一个包含 n 个整数的数组nums和一个目标值target，判断nums中是否存在四个元素 a，b，c和 d，使得a + b + c + d的值与target相等？找出所有满足条件且不重复的四元组。

注意：
答案中不可以包含重复的四元组。

示例：
给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

满足要求的四元组集合为：
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/4sum
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int tmp = 0, lastLeftNum1 = INT32_MIN, lastLeft2NumSum = INT32_MIN, Left2NumSum = 0,
            leftIndex1 = 0, leftIndex2 = 0, midIndex = 0, rightIndex = 0, size = nums.size();
        vector<vector<int>> ans;
        vector<int> tmpVec(4);

        // 排序 O(nlog(n))
        sort(nums.begin(), nums.end());

        // 选定组合的最左端的两个元素
        for (leftIndex1 = 0; leftIndex1 < size - 3; ++leftIndex1) {
            // 若与上一次最左端元素值相等（已搜索过），跳过
            if (nums[leftIndex1] == lastLeftNum1) {
                continue;
            }
            lastLeftNum1 = nums[leftIndex1];
            lastLeft2NumSum = INT32_MIN;
            for (leftIndex2 = leftIndex1 + 1; leftIndex2 < size - 2; ++leftIndex2) {
                Left2NumSum = nums[leftIndex1] + nums[leftIndex2];
                // 若与上一次最左端两元素之和的值相等（已搜索过），跳过
                if (Left2NumSum == lastLeft2NumSum) {
                    continue;
                }
                lastLeft2NumSum = Left2NumSum;

                // 加速，若加上最右两个最大组合仍小于 target，跳过
                if (Left2NumSum + nums[size - 2] + nums[size - 1] < target) {
                    continue;
                }
                // 加速，若加上紧挨最左元素的最小组合仍大于target，则后面不必判断
                if (Left2NumSum + nums[leftIndex2 + 1] + nums[leftIndex2 + 2] > target) {
                    break;
                }

                // 初始化中间和左端两个指针，相向而行搜索可能的组合
                midIndex = leftIndex2 + 1;
                rightIndex = size - 1;
                while ( midIndex < rightIndex ) {
                    tmp = Left2NumSum + nums[midIndex] + nums[rightIndex];
                    // 找到这三个数，添加到ans
                    if (tmp == target) {
                        tmpVec[0] = nums[leftIndex1];
                        tmpVec[1] = nums[leftIndex2];
                        tmpVec[2] = nums[midIndex];
                        tmpVec[3] = nums[rightIndex];
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
                    } else if (tmp < target) {
                        // 和小于target，rightIndex已最大，只能增加 midIndex
                        ++midIndex;
                    } else {
                        // 和大于target，midIndex 已最小，只能减小 rightIndex
                        --rightIndex;
                    }
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
    int target = 0;
    int arr[] = {-3,-2,-1,0,0,1,2,3};
    vector<int> nums(arr, arr + sizeof(arr) / sizeof(int));

    vector<vector<int>> result = solution.fourSum(nums, target);
    printVector(result);

    return 0;
}
