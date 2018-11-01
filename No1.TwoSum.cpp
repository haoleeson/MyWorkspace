#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        bool isFindFlag = false;
        for (int i=0; i<nums.size(); i++)
        {
            int resultNum = target - nums[i];
            for (int j=0; j<nums.size(); j++)
            {
                if (j == i) continue;
                if (nums[j] == resultNum)
                {
                    if (i < j)
                    {
                        result.push_back(i);
                        result.push_back(j);
                    }
                    else
                    {
                        result.push_back(j);
                        result.push_back(i);
                    }
                    isFindFlag = true;
                    break;
                }
            }
            if(isFindFlag) break;
        }
        return  result;
    }
};

int main(void)
{
    vector<int> nums = {2, 11, 7, 15};
    vector<int> result;
    int target =  9;
    Solution s;
    result = s.twoSum(nums, target);
    cout << "result = " <<  result[0] << ", " << result[1] << endl;
}
