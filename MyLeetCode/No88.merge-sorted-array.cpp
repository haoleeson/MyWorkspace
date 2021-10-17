/** 题目描述：
 * 88. 合并两个有序数组
 * 给定两个有序整数数组 nums1 和 nums2，将 nums2 合并到 nums1 中，使得 num1 成为一个有序数组。

说明:

初始化 nums1 和 nums2 的元素数量分别为 m 和 n。
你可以假设 nums1 有足够的空间（空间大小大于或等于 m + n）来保存 nums2 中的元素。
示例:

输入:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

输出: [1,2,2,3,5,6]

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190303
 * */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=m-1, j=n-1, iterator = m+n-1;
        while (i > -1 && j > -1) {
            if (nums1[i] > nums2[j]){
                nums1[iterator--] = nums1[i--];
            } else {
                nums1[iterator--] = nums2[j--];
            }
        }
        //nums1的元素已填完，其余填num2
        if (i == -1) {
            while (j > -1) {
                nums1[iterator--] = nums2[j--];
            }
        }
        //nums2的元素已填完，其余nums1内的元素不用填
    }
};

int main(int argc, const char * argv[]) {
    Solution solution;
    int m=3, n=3;
    vector<int> nums1 = {1,2,3,0,0,0};
    vector<int> nums2 = {2,5,6};
    cout << "num1 = [";
    for(int i=0; i<m-1; i++){
        cout << nums1[i] << ",";
    }
    cout << nums1[m-1] <<"]" << endl;
    cout << "num2 = [";
    for(int i=0; i<n-1; i++){
        cout << nums2[i] << ",";
    }
    cout << nums2[n-1] <<"]" << endl;

    solution.merge(nums1, m, nums2, n);

    cout << "After merge num1 = [";
    for(int i=0; i<m+n-1; i++){
        cout << nums1[i] << ",";
    }
    cout << nums1[m+n-1] <<"]" << endl;
}
