#include<iostream>
#include<vector>
using namespace std;

//给你一个长度固定的整数数组 arr，请你将该数组中出现的每个零都复写一遍，并将其余的元素向右平移。
//注意：请不要在超过该数组长度的位置写入元素。
//要求：请对输入的数组 就地 进行上述修改，不要从函数返回任何东西。
//
//提示：
//    1 <= arr.length <= 10000
//    0 <= arr[i] <= 9
//
//示例 1：
//输入：[1,0,2,3,0,4,5,0]
//输出：null
//解释：调用函数后，输入的数组将被修改为：[1,0,0,2,3,0,0,4]
//
//
//示例 2：
//输入：[1,2,3]
//输出：null
//解释：调用函数后，输入的数组将被修改为：[1,2,3]

void printVec(vector<int>& arr) {
    int len_arr = arr.size();
    cout << endl;
    for (int i = 0; i < len_arr; ++i) {
        cout << " " << arr[i];
    }
}

class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int len_arr = arr.size();
        int index = -1, count = 0;
        int j = len_arr - 1;

        // monitoring write
        while (count < len_arr) {
            ++index;
            if (arr[index] == 0) {
                count += 2;
            } else {
                ++count;
            }
        }

        // 末尾 0 溢出
        if (arr[index] == 0 && count > len_arr) {
            arr[j--] = arr[index--];
        }
        while (j > index) {
            if (arr[index] == 0) {
                arr[j--] = 0;
            }
            arr[j--] = arr[index--];
        }
    }
};

int main(void) {
    Solution solution;
//    int a[] = {1,0,2,3,0,4,5,0};
//    int a[] = {1,0,2,3,0,4,5};
    int a[] = {1,0,2,3,0,4};
    int b[] = {1,2,3};
    vector<int> A = vector<int>(a, a + sizeof(a)/sizeof(int));
    vector<int> B = vector<int>(b, b + sizeof(b)/sizeof(int));

    printVec(A);
    solution.duplicateZeros(A);
    printVec(A);

    printVec(B);
    solution.duplicateZeros(B);
    printVec(B);

    return 0;
}