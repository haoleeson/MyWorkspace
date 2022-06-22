#include<iostream>
#include<vector>
#include "myTools.h"
using namespace std;

// 回溯 O(2^n)
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        this->len = nums.size();
        this->indexUsedFlag = new bool[len]{false};
        this->indexPath = new int[len]{0};
        backtrack(nums, 0);
        return res;
    }

private:
    int len;
    bool* indexUsedFlag;
    int* indexPath;
    vector<vector<int>> res;

    void backtrack(vector<int>& nums, int usedCnt) {
        // 若已排完 n 个数，装填到 res 中
        if (usedCnt == len) {
            vector<int> tmp(len);
            for (int i = 0; i < len; ++i) {
                tmp[i] = nums[indexPath[i]];
            }
            res.push_back(tmp);
        }

        for (int i = 0; i < len; ++i) {
            // 若数字已用过，则跳过
            if (indexUsedFlag[i]) {
                continue;
            }

            indexPath[usedCnt] = i;
            indexUsedFlag[i] = true;
            backtrack(nums, usedCnt + 1);
            indexUsedFlag[i] = false;
        }
    }
};

int main(void) {

    int arr1[] = {1,2,3};
    vector<int> nums1(arr1, arr1 + sizeof(arr1)/sizeof(int));
    Solution solution1;
    vector<vector<int>> res1 = solution1.permute(nums1);
    MyTools::printVec2D(res1);

    int arr2[] = {0,1};
    vector<int> nums2(arr2, arr2 + sizeof(arr2)/sizeof(int));
    Solution solution2;
    vector<vector<int>> res2 = solution2.permute(nums2);
    MyTools::printVec2D(res2);

    int arr3[] = {1};
    vector<int> nums3(arr3, arr3 + sizeof(arr3)/sizeof(int));
    Solution solution3;
    vector<vector<int>> res3 = solution3.permute(nums3);
    MyTools::printVec2D(res3);

    return 0;
}
