/**
 * 697. 数组的度
 * 给定一个非空且只包含非负数的整数数组 nums, 数组的度的定义是指数组里任一元素出现频数的最大值。

你的任务是找到与 nums 拥有相同大小的度的最短连续子数组，返回其长度。

示例 1:

输入: [1, 2, 2, 3, 1]
输出: 2
解释:
输入数组的度是2，因为元素1和2的出现频数最大，均为2.
连续子数组里面拥有相同度的有如下所示:
[1, 2, 2, 3, 1], [1, 2, 2, 3], [2, 2, 3, 1], [1, 2, 2], [2, 2, 3], [2, 2]
最短连续子数组[2, 2]的长度为2，所以返回2.
示例 2:

输入: [1,2,2,3,1,4,2]
输出: 6
注意:

nums.length 在1到50,000区间范围内。
nums[i] 是一个在0到49,999范围内的整数。

 * coder:eisenhao
 * 20190329
 * */

#include <iostream>
#include <vector>
#include<map>

using namespace std;

//常规思路
//0. 统计频次
//1. 迭代器遍历，找出现的最大频次
//2.找最大频次的数（可能有多个）
//3.求最大频次数对应度的长度（可能多个）
//4.找最小度的长度

class Solution {
public:
    /** 自己实现：Leetcode 212ms*/
    int findShortestSubArray(vector<int>& nums) {
        int len=nums.size(), maxTimes=1, minDuLen;//数组长度, 最大频次, 最小度的长度
        map<int, int >EmergeTime; //s是一个映射 <数组中的元素， 出现次数>
        vector<int> theMaxValueArray;//最大频次的数
        vector<int> theDuLen;//最大频次的数对应度的长度

        //0. 统计频次
        for (int i=0; i<len; i++) {
            EmergeTime[nums[i]]++; //统计元素出现次数
        }
        //1. 迭代器遍历，找出现的最大频次
        for (map<int, int>::iterator iter = EmergeTime.begin(); iter != EmergeTime.end(); ++iter) {
            if (iter->second > maxTimes) {
                maxTimes = iter->second;
            }
        }
        //2.找最大频次的数（可能多个）
        for (map<int, int>::iterator iter = EmergeTime.begin(); iter != EmergeTime.end(); ++iter) {
            if (iter->second == maxTimes) {
                theMaxValueArray.push_back(iter->first);
            }
        }
        //3.求最大频次数对应度的长度（可能多个）
        for (int i=0; i<theMaxValueArray.size(); i++) {
            int star=0, end=len-1;
            //找到出现最大频次数字的 的最早下标 和 最晚下标 --> 求该数字对应度长度
            while (nums[star++] != theMaxValueArray[i]) {}
            while (nums[end--] != theMaxValueArray[i]) {}
            theDuLen.push_back(end - star + 3);
        }
        //4.找最小度的长度
        minDuLen = theDuLen[0];
        for (int i=1; i<theDuLen.size(); i++) {
            if (minDuLen > theDuLen[i]) {
                minDuLen = theDuLen[i];
            }
        }
        return minDuLen;
    }

    /** Leetcode大神实现 12ms */
    int findShortestSubArray2(vector<int>& nums) {
        int m[2][50000]={0};
        int max_cnt=0,min_len=1;
        for(int i=0;i<nums.size();++i)
        {
            int num=nums[i];
            ++m[0][num];
            if(m[0][num]==1)
            {
                m[1][num]=i;
            }
            else if(m[0][num]>max_cnt)
            {
                max_cnt=m[0][num];
                min_len=i-m[1][num]+1;
            }
            else if(m[0][num]==max_cnt)
            {
                min_len=min(min_len,i-m[1][num]+1);
            }
        }
        return min_len;
    }
};


int main(void) {
    Solution s;
    vector<int> Input = {1,2,2,3,1,4,2};
    cout <<  s.findShortestSubArray(Input);
    return 0;
}