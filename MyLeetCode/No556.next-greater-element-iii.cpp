#include <algorithm>
#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 官解 O(long N)
// 链接：https://leetcode.cn/problems/next-greater-element-iii/solution/xia-yi-ge-geng-da-yuan-su-iii-by-leetcod-mqf1/
class Solution {
public:
    int nextGreaterElement(int n) {
        string nums = uint2str(n);
        int lenN = nums.length();

        // 逆序寻找第一个递增的 <相邻数字对> [i, i+1]
        int i = lenN - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            --i;
        }
        if (i < 0) {
            return -1;
        }

        // 逆序寻找 (i + 1, lenN - 1] 有无更早出现的大于 nums[i] 的数字
        int j = lenN - 1;
        while (j >= 0 && nums[j] <= nums[i]) {
            --j;
        }
        swap(nums[i], nums[j]);

        // 翻转 [i + 1, len - 1]
        int left = i + 1, right = lenN - 1;
        while (left < right) {
            swap(nums[left], nums[right]);
            ++left;
            --right;
        }

        // 字符串转数字
        long ans = str2long(nums);

        return ans > INT_MAX ? -1 : ans;
    }

private:
    inline string uint2str(uint32_t num) {
        if (num == 0) {
            return "0";
        }

        char buff[11] = {'\0'};
        int iterator = 0;

        uint32_t tmp = num;
        while (tmp) {
            buff[iterator++] = '0' + char(tmp % 10);
            tmp /= 10;
        }

        // 反转 buff 数组
        char tmpCh;
        int i = 0, j = iterator - 1;
        while (i < j) {
            tmpCh = buff[i];
            buff[i] = buff[j];
            buff[j] = tmpCh;
            ++i;
            --j;
        }
        buff[iterator] = '\0';
        return string(buff);
    }

    inline long str2long(std::string& str) {
        long num = 0, chNum;
        int lenS = str.length();
        if (lenS == 0 || lenS > 11) {
            return 0;
        }

        for (int i = 0; i < lenS; ++i) {
            chNum = str[i] - '0';
            if (chNum < 0 || chNum > 9) {
                return 0;
            }
            num = num * 10 + chNum;
        }

        return num;
    }
};

int main(void) {
    Solution solution;
    int n1 = 12;
    int res1 = solution.nextGreaterElement(n1);
    cout << res1 << endl;

    int n2 = 21;
    int res2 = solution.nextGreaterElement(n2);
    cout << res2 << endl;

    int n3 = 1241321;
    int res3 = solution.nextGreaterElement(n3);
    cout << res3 << endl;

    return 0;
}
