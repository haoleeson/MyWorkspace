#include <iostream>

#include "myTools.h"

using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int len = asteroids.size();
        int cntDestroy = 0;

        bool* destroyed = new bool[len]{false};

        for (int i = 0; i < len; ++i) {
            // 找到负数（向左行星）
            if (asteroids[i] > 0) {
                continue;
            }
            // 向左遍历模拟碰撞
            for (int j = i - 1; j >= 0; --j) {
                // 跳过 已标记为湮灭的行星 或 同向行星（终止）
                if (destroyed[j]) {
                    continue;
                } else if (asteroids[j] < 0) {
                    break;
                }

                if (asteroids[j] < -asteroids[i]) {
                    // 向右行星更小（湮灭），继续向左遍历
                    destroyed[j] = true;
                    ++cntDestroy;
                    continue;
                } else if (asteroids[j] > -asteroids[i]) {
                    // 向右行星更大，自身湮灭，模拟碰撞结束
                    destroyed[i] = true;
                    ++cntDestroy;
                    break;
                } else {
                    // 大小相同，双方湮灭，模拟碰撞结束
                    destroyed[j] = true;
                    destroyed[i] = true;
                    cntDestroy += 2;
                    break;
                }
            }
        }

        // 整理未湮灭的行星
        vector<int> res(len - cntDestroy);
        int iterator = 0;
        for (int i = 0; i < len; ++i) {
            if (!destroyed[i]) {
                res[iterator++] = asteroids[i];
            }
        }
        return res;
    }
};

int main(int argc, const char* argv[]) {
    Solution solution;

    int arr1[] = {5, 10, -5};
    vector<int> nums1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    vector<int> res1 = solution.asteroidCollision(nums1);
    MyTools::printVec(res1);

    int arr2[] = {8, -8};
    vector<int> nums2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    vector<int> res2 = solution.asteroidCollision(nums2);
    MyTools::printVec(res2);

    int arr3[] = {10, 2, -5};
    vector<int> nums3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    vector<int> res3 = solution.asteroidCollision(nums3);
    MyTools::printVec(res3);

    int arr4[] = {-2, -1, 1, 2};
    vector<int> nums4(arr4, arr4 + sizeof(arr4) / sizeof(int));
    vector<int> res4 = solution.asteroidCollision(nums4);
    MyTools::printVec(res4);

    return 0;
}
