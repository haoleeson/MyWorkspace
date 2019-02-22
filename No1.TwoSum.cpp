/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190222
* */
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        bool isFind = false;
        int nums_Size = nums.size();
        vector<int> index;
        for(int i=0; i<nums_Size-1; i++){
            int tmp = target - nums[i];
            for(int j=i+1; j<nums_Size; j++){
                if (nums[j] == tmp){
                    index.push_back(i);
                    index.push_back(j);
                    isFind = true;
                    break;
                }
            }
            if(isFind){
                break;
            }
        }
        return index;
    }
};

int main(int argc, const char * argv[]) {
    vector<int> nums = {2, 11, 7, 15};
    vector<int> result;
    int target =  9;
    Solution s;
    result = s.twoSum(nums, target);
    cout << "result = " <<  result[0] << ", " << result[1] << endl;
}
