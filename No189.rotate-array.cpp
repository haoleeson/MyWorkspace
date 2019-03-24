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
 * 20190324
 * */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    //【方法1：超出时间限制】时间复杂度 O(kn), 空间复杂度O(1)
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
    //【方法2：Leetcode 28ms】时间复杂度 O(n), 空间复杂度O(k)
    void rotate(vector<int>& nums, int k) {
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
};

int main(void) {
    Solution s;
    vector<int> Input = {1,2,3,4,5,6,7};
    cout << "Input = [";
    for (int i=0; i<Input.size(); i++) {
        cout << Input[i] << " ";
    }
    cout << "]" << endl;
    //旋转
    s.rotate(Input, 3);
    cout << "After = [";
    for (int i=0; i<Input.size(); i++) {
        cout << Input[i] << " ";
    }
    cout << "]" << endl;
    return 0;
}
