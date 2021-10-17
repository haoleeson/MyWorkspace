#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

/**
 * No679. 24点游戏（递归，回溯）
 * 你有 4 张写有 1 到 9 数字的牌。你需要判断是否能通过*，/，+，-，(，)的运算得到 24。

示例 1:

输入: [4, 1, 8, 7]
输出: True
解释: (8-4) * (7-1) = 24
示例 2:

输入: [1, 2, 1, 2]
输出: False
注意:

除法运算符/表示实数除法，而不是整数除法。例如 4 / (1 - 2/3) = 12 。
每个运算符对两个数进行运算。特别是我们不能用-作为一元运算符。例如，[1, 1, 1, 1]作为输入时，表达式-1 - 1 - 1 - 1是不允许的。
你不能将数字连接在一起。例如，输入为[1, 2, 1, 2]时，不能写成 12 + 12 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/24-game
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 */


/**
 * 分析：经历共三次计算(+,-,*,/)，每次计算相当于少了一个数
 *
 * eg.[4,1,8,7]  == (8-4)*(7-1)
 * 第一次计算：8-4，得到[4,1,7]      ，共有 c(4,2) = 6种选择组，+,*,-,/,被-,被/，6种组合计算方法 6x6,36种
 * 第二次计算：7-1，得到[4,6]        ，共有 c(3,2) = 3种选择组，同理6种计算方法，3x6, 18种
 * 第三次计算：4*6，得到[24]         , 共有 c(2,2) = 1种选择组，同理5种计算方法，1x6，6种
 * 累计：36 x 18 x 6 = 3888种可能性
 */
class Solution {
    constexpr static const double TARGET = 24.0;
    constexpr static const double EPSILON = 1e-6;
public:
    bool judgePoint24(vector<int>& nums) {
        int size = nums.size();
        if (size < 1 || size > 4) {
            return false;
        }
        double numsCopy[4] = {0.0};
        for (int i = 0; i < size; ++i) {
            numsCopy[i] = static_cast<double>(nums[i]);
        }
        bool ans = solve(numsCopy, size);
        return ans;
    }

    bool solve(double* nums, int size) {
        if (size < 2) {
            return (size == 1) ? fabs(nums[0] - TARGET) < EPSILON : false;
        }
        bool ans = false;
        double nums2[4] = {0.0};// 构造下一步数组（存储未被选中的数，和选中两数的计算结果）

        // 选择两个数nums[i], nums[j]
        for (int i = 0; i < size; ++i) {
            for (int j = i + 1; j < size; ++j) {

                // 拷贝未被选中的数
                for (int k = 0, iterator = 0; k < size; ++k) {
                    if (k == i || k == j) {
                        continue;
                    }
                    nums2[++iterator] = nums[k];
                }

                // 依次执行6种计算
                for (int k = 0; k < 6; ++k) {
                    switch (k) {
                        case 0:
                            nums2[0] = nums[i] + nums[j];// 计算 +
                            break;
                        case 1:
                            nums2[0] = nums[i] * nums[j];// 计算 *
                            break;
                        case 2:
                            nums2[0] = nums[i] - nums[j];// 计算 -
                            break;
                        case 3:
                            nums2[0] = nums[j] - nums[i];// 计算 被-
                            break;
                        case 4:
                            if (fabs(nums[j] - 0.0) < EPSILON) {
                                continue;// 被除数为0，跳过
                            }
                            nums2[0] = nums[i] / nums[j];// 计算 /
                            break;
                        case 5:
                            if (fabs(nums[i] - 0.0) < EPSILON) {
                                continue;// 被除数为0，跳过
                            }
                            nums2[0] = nums[j] / nums[i];// 计算 被/
                            break;
                    }
                    ans = solve(nums2, size - 1);
                    if (ans) {
                        return true;
                    }
                }

            }
        }
        return false;
    }
};


int main() {
    Solution solution;
    int arr[] = {1,5,9,1};
    vector<int> nums(arr, arr + 4);

    cout << solution.judgePoint24(nums) << endl;

    return 0;
}
