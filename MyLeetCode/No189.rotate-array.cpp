/**
 * 189. 旋转数组
 * 给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。

 示例 1:
输入: [1,2,3,4,5,6,7] 和 k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右旋转 1 步: [7,1,2,3,4,5,6]
向右旋转 2 步: [6,7,1,2,3,4,5]
向右旋转 3 步: [5,6,7,1,2,3,4]

 示例 2:
输入: [-1,-100,3,99] 和 k = 2
输出: [3,99,-1,-100]
解释:
向右旋转 1 步: [99,-1,-100,3]
向右旋转 2 步: [3,99,-1,-100]

 说明:
尽可能想出更多的解决方案，至少有三种不同的方法可以解决这个问题。
要求使用空间复杂度为 O(1) 的原地算法。

 * coder:eisenhao
 * 20190325
 * */

#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class Solution {
public:
    /**【方法1：Leetcode 超出时间限制】时间复杂度 O(kn), 空间复杂度O(1)*/
    void rotate1(vector<int>& nums, int k) {
        //移动次数，最小化
        k = k % nums.size();
        if (k < nums.size()>>1) {
            //向右移动的次数小于数组的一半，向右移动 k 次, 每次移动1步
            for (int i=0; i<k; i++){
                //每次将数组向右移动 1 ，共移动 k 次
                for (int j=nums.size()-1; j>0; j--) {
                    //交换 nums[j] 与 nums[j-1]
                    nums[j] = nums[j-1] ^ nums[j];
                    nums[j-1] = nums[j-1] ^ nums[j];
                    nums[j] = nums[j-1] ^ nums[j];
                }
            }
        } else {
            //向右移动的次数大于等于数组的一半，向左移动 n-k 次, 每次移动1步
            k = nums.size() - k;
            for (int i=0; i<k; i++) {
                //每次将数组向左移动 1 ，共移动 n-k 次
                for (int j=0; j<nums.size()-1; j++) {
                    //交换 nums[j] 与 nums[j-1]
                    nums[j+1] = nums[j] ^ nums[j+1];
                    nums[j] = nums[j] ^ nums[j+1];
                    nums[j+1] = nums[j] ^ nums[j+1];
                }
            }
        }
    }
    /**【方法2：Leetcode 28ms】时间复杂度 O(n), 空间复杂度O(k)*/
    void rotate2(vector<int>& nums, int k) {
        //移动次数，最小化
        k = k % nums.size();
        if (k < nums.size()>>1) {
            //向右移动的次数小于数组的一半，向右移动 k
            //1。保存最右边的k个元素
            vector<int> tmp(k, 0);
            for (int i=0, j=nums.size()-k; i<k; i++,j++) {
                tmp[i] = nums[j];
            }
            //2。将数组前0～n-k个元素向后移动k位
            for (int i=nums.size()-1; i>k-1; i--) {
                nums[i] = nums[i-k];
            }
            //3。恢复保存的最右边的k个元素到最左边
            for (int i=0; i<k; i++) {
                nums[i] = tmp[i];
            }
        } else {
            //向右移动的次数大于等于数组的一半，向左移动 n-k
            k = nums.size() - k; //更新k为 n-k
            //1。保存最左边的 k 个元素
            vector<int> tmp(k, 0);
            for (int i=0; i<k; i++) {
                tmp[i] = nums[i];
            }
            //2。将数组的后 k～n个元素向左移动k位
            for (int i=0; i<nums.size()-k; i++) {
                nums[i] = nums[i+k];
            }
            //3。恢复保存的最左边的k个元素到最右边
            for (int i=0, j=nums.size()-k; i<k; i++, j++) {
                nums[j] = tmp[i];
            }
        }
    }

    /**【方法3: Leetcode 48ms】时间复杂度 O(n), 空间复杂度O(1)
     * 在数组规定范围内右移或左移 k 位
     * 参数：
     * - nums           ：待移动的数组
     * - index_start    ：开始下标
     * - index_end      ：结束下标
     * - k              ：移动步数 （限制： k <  范围的一半)   ）
     * - moveDir        ：移动方向 ：true 右移动、 false 左移动
     * */
    void subRotate(vector<int>& nums, int index_start, int index_end, int k, bool moveDir) {
        /**若k == 1 直接移动*/
        if (k == 1) {
            //判断方向：直接右移 1
            if (moveDir) {
                int tmp = nums[index_end];
                for (int i=index_end; i>index_start; i--){
                    nums[i] = nums[i-1];
                }
                nums[index_start] = tmp;
            }
            //判断方向：直接左移 1
            else {
                int tmp = nums[index_start];
                for (int i=index_start; i<index_end; i++){
                    nums[i] = nums[i+1];
                }
                nums[index_end] = tmp;
            }
        }
        /**若k != 1 递归调用交换，每次左右移动部分元素到正确位置，范围不断缩减*/
        else {
            //判断方向：右移 k
            if (moveDir) {
                //1。从右边开始，每次交换 次k个 元素与 最右k个 元素。eg. 交换nums[iterator-k+1]~nums[iterator] 与 nums[iterator+1]~nums[iterator+k]
                int iterator = index_end;
                while (iterator-2*k+1 >= index_start) {
                    //每次交换一个块（大小为k）
                    for (int i=0; i<k; i++) {
                        //交换nums[iterator] 与 nums[iterator+k]
                        nums[iterator] = nums[iterator-k] ^ nums[iterator];
                        nums[iterator-k] = nums[iterator-k] ^ nums[iterator];
                        nums[iterator] = nums[iterator-k] ^ nums[iterator];
                        iterator--;
                    }
                }
                //判断是否有剩余部分还需要移动
                if (iterator-k+1 > index_start){
                    //2。处理剩下左侧下标为 0~iterator+k 右移 k 位。由于 iterator < k-1+index_start，故剩下部分应该左移 （iterator-index_star+1）位
                    subRotate(nums, index_start, iterator, iterator-index_start+1-k, false);/**递归调用：左移*/
                }
            }
            //判断方向：左移 k
            else {
                //1。从左边开始，每次交换 次k个 元素与 最左k个 元素。eg. 交换nums[iterator-k+1]~nums[iterator] 与 nums[iterator+1]~nums[iterator+k]
                int iterator = index_start;
                while (iterator+2*k-1 <= index_end) {
                    //每次交换一个块（大小为k）
                    for (int i=0; i<k; i++) {
                        //交换nums[iterator] 与 nums[iterator+k]
                        nums[iterator+k] = nums[iterator] ^ nums[iterator+k];
                        nums[iterator] = nums[iterator] ^ nums[iterator+k];
                        nums[iterator+k] = nums[iterator] ^ nums[iterator+k];
                        iterator++;
                    }
                }
                //判断是否有剩余部分还需要移动
                if (iterator+k-1 < index_end){
                    //处理剩下的右侧下标为 iterator-k+1~index_end 左移k位。由于iterator > index_end-nums_size，故剩下部分应该右移(index_end-iterator+1)
                    subRotate(nums, iterator, index_end, index_end-iterator+1-k, true);/**递归调用：右移*/
                }
            }
        }
    }
    /** 方法3加壳
     * 将数组 nums 所有元素逻辑右移k位
     * 核心：迭代调用 subRotate
     * 加壳，统一接口
     * */
    void rotate3(vector<int>& nums, int k) {
        //移动次数，最小化
        k = k % nums.size();
        if (k>0) {
            //判断左移还是右移
            if (k <= nums.size()/2) {
                subRotate(nums, 0, nums.size()-1, k, true);/**右移k位*/
            } else {
                subRotate(nums, 0, nums.size()-1, nums.size()-k, false);/**左移k位*/
            }
        }
    }

    /**【方法3-2：Leetcode 28ms 优化：改递归为迭代】
     * 将数组 nums 所有元素逻辑右移k位
     * */
    void rotate(vector<int>& nums, int k) {
        int index_start = 0, index_end = nums.size() - 1;
        bool moveDir = true; //初始值为右移

        //移动次数最小化
        k %= nums.size();
        //第一次移动时判断 ： 左移 or 右移
        if (k > nums.size()/2) {
            /**更改初始参数为：左移 n - k 位*/
            moveDir = false;
            k = nums.size() - k;
        }

        /**迭代移位*/
        while (k>0) {

            /**若k == 1 直接移动*/
            if (k == 1) {
                if (moveDir) {
                    //判断方向：直接右移 1
                    int tmp = nums[index_end];
                    for (int i=index_end; i>index_start; i--){
                        nums[i] = nums[i-1];
                    }
                    nums[index_start] = tmp;
                } else {
                    //判断方向：直接左移 1
                    int tmp = nums[index_start];
                    for (int i=index_start; i<index_end; i++){
                        nums[i] = nums[i+1];
                    }
                    nums[index_end] = tmp;
                }
                k=0;/** 退出迭代 */
            }
            /**若k > 1 递归调用 交换，每次左右移动部分元素到正确位置，范围不断缩减*/
            else {
                //判断方向：右移 k
                if (moveDir) {
                    //1。从右边开始，每次交换 次k个 元素与 最右k个 元素。eg. 交换nums[iterator-k+1]~nums[iterator] 与 nums[iterator+1]~nums[iterator+k]
                    int iterator = index_end;
                    while (iterator-2*k+1 >= index_start) {
                        //每次交换一个块（大小为k）
                        for (int i=0; i<k; i++) {
                            //交换nums[iterator] 与 nums[iterator+k]
                            nums[iterator] = nums[iterator-k] ^ nums[iterator];
                            nums[iterator-k] = nums[iterator-k] ^ nums[iterator];
                            nums[iterator] = nums[iterator-k] ^ nums[iterator];
                            iterator--;
                        }
                    }
                    //判断是否有剩余部分还需要移动
                    if (iterator-k+1 > index_start) {
                        //2。处理剩下左侧下标为 0~iterator+k 右移 k 位。由于 iterator < k-1+index_start，故剩下部分应该左移 （iterator-index_star+1）位
                        /**配置迭代 左移参数*/
                        index_end = iterator;
                        k = iterator - index_start + 1 - k;
                        moveDir = false;
                    } else {
                        k=0;/** 退出迭代 */
                    }
                }
                //判断方向：左移 k
                else {
                    //1。从左边开始，每次交换 次k个 元素与 最左k个 元素。eg. 交换nums[iterator-k+1]~nums[iterator] 与 nums[iterator+1]~nums[iterator+k]
                    int iterator = index_start;
                    while (iterator+2*k-1 <= index_end) {
                        //每次交换一个块（大小为k）
                        for (int i=0; i<k; i++) {
                            //交换nums[iterator] 与 nums[iterator+k]
                            nums[iterator+k] = nums[iterator] ^ nums[iterator+k];
                            nums[iterator] = nums[iterator] ^ nums[iterator+k];
                            nums[iterator+k] = nums[iterator] ^ nums[iterator+k];
                            iterator++;
                        }
                    }
                    //判断是否有剩余部分还需要移动
                    if (iterator+k-1 < index_end){
                        //处理剩下的右侧下标为 iterator-k+1~index_end 左移k位。由于iterator > index_end-nums_size，故剩下部分应该右移(index_end-iterator+1)
                        /**配置迭代 右移参数*/
                        index_start = iterator;
                        k = index_end - iterator + 1 - k;
                        moveDir = true;
                    } else {
                        k=0;/** 退出迭代 */
                    }
                }
            }

        }
    }
    

    //打印数组
    void printArray(string str, vector<int>& Input){
        cout << str << endl << "[";
        for (int i=0; i<Input.size(); i++) {
            cout << Input[i] << " ";
        }
        cout << "]" << endl << endl;
    }
};

int main(void) {
    Solution s;
    vector<int> Input = {1,2,3,4,5,6,7};
    s.printArray("Start: " ,Input);
    //旋转
    s.rotate(Input, 3);
    s.printArray("After: " ,Input);
    return 0;
}
