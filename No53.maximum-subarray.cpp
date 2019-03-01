class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int sum = nums[0];
        int result = sum;
//        int iterator_star, iterator_end ;//记录连续字数组的起始下标
        for (int i=1; i<nums.size(); i++) {
            if (sum + nums[i] < nums[i]) {
                sum = nums[i];//更新子序列头元素
//                iterator_star = i; //更新子序列头元素下标
            } else {
                sum += nums[i];
            }
            if (sum > result) {
                result = sum;
//                iterator_end = i;//更新子序列尾元素下标
            }
        }
        //输出最大子数组的起始坐标
//        cout << "star:" << iterator_star << " , end:" << iterator_end << endl;
        return result;
    }
};
