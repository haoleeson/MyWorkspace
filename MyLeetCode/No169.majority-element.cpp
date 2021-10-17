/**
 * 169. 求众数
 * 给定一个大小为 n 的数组，找到其中的众数。众数是指在数组中出现次数大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在众数。

示例 1:

输入: [3,2,3]
输出: 3
示例 2:

输入: [2,2,1,1,1,2,2]
输出: 2

 * coder:eisenhao
 * 20190322
 * */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int tmp, times, size = nums.size(), i, j;
        for (i=0; i<=(size>>1);) {
            tmp = nums[i], times = 1;
            for (j=i+1; j<size; j++) {
                if (nums[j] == nums[i]) {
                    times++;
                }
            }
            if (times > size>>1) {
                break;
            }
            //增加i到前方从未出现过的数字的下标处
            i++;
            while (i < size) {
                //判断该数字nums[i]之前是否有出现(已比较过)
                for (j=0; j<i; j++){
                    if (nums[j] == nums[i]) {
                        break;
                    }
                }
                //找到从前未出现的数字
                if (i == j) {
                    break;
                }
                i++;
            }
        }
        return tmp;
    }
};

int main(void) {
    Solution s;
    vector<int> Input = {2,2,1,1,1,2,2};
    cout << "Output = " << s.majorityElement(Input) << endl;
    return 0;
}

