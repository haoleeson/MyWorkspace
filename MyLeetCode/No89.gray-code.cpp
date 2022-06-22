#include<iostream>
#include<vector>
#include "myTools.h"
using namespace std;

// 官解：镜像倒序添加 O(2^n)
// 原理：n 阶的 G(n) 可通过 n-1 阶 G(n-1) 得到：G(n-1)首位补零构成前半部分，G(n-1)首位补1并倒序构成后半部分
class Solution {
public:
    vector<int> grayCode(int n) {
        int totalNums = 1 << n;
        vector<int> res(totalNums, 0);
        
        int head = 1;
        int index = 0;
        // 依次计算第 n 阶格雷码
        for (int i = 0; i < n; ++i) {
            // 倒序追加首部补1的 G(n-1)
            for (int j = index; j >= 0; --j) {
                res[++index] = head + res[j];
            }
            head <<= 1;
        }

        return res;
    }
};


// 格雷码公式计算 O(2^n)
// 原理：gray_code[i] = i xor (i >> 1)
class Solution1 {
public:
    vector<int> grayCode(int n) {
        int totalNums = 1 << n;
        vector<int> res(totalNums, 0);

        for (int i = 1; i < totalNums; ++i) {
            res[i] = calcGrayCode(i);
        }

        return res;
    }

private:
    // 第 i 个格雷码的计算公式：gray_code[i] = i xor (i >> 1)
    inline int calcGrayCode(int index) {
        return index ^ (index >> 1);
    }
};


// my 回溯 O(n * 2^n)
class Solution0 {
public:
    vector<int> grayCode(int n) {
        this->N = n;
        this->totalNums = 1 << n;

        // 标记用过的数字（[0, 2^n - 1]每个数字都会用到）
        this->numUsedFlag = new bool[totalNums]{false};
        numUsedFlag[0] = true;

        // 相邻数字之间第几位 bit 有差异（2^0, 2^1, 2^2, 2^3...2^(n-1)）
        this->chooseChg = new int[N]{0};
        for (int i = 0; i < N; ++i) {
            chooseChg[i] = 1 << i;
        }

        // 暂存 2^n 个数的数组
        this->tmpArr = new int[totalNums]{0};
        tmpArr[0] = 0;

        backtrack(1);
        return res;
    }

private:
    int N;
    int totalNums;
    bool* numUsedFlag;
    int* chooseChg;
    int* tmpArr;
    bool finish = false;
    vector<int> res;
    
    void backtrack(int index) {
        if (finish) {
            return;
        } else if (index == totalNums) {
            res = vector<int>(tmpArr, tmpArr + totalNums);
            finish = true;
            return;
        }

        // 选择第几位 bit 与前一数字不同
        for (int i = 0; i < N; ++i) {
            // 利用异或性质(0 ^ a = a, 1 ^ a = !a)，取前一数字在第几 bit 不一致的数
            int chooseNum = tmpArr[index - 1] ^ chooseChg[i];

            // 若数字已用过，则跳过
            if (numUsedFlag[chooseNum]) {
                continue;
            }

            tmpArr[index] = chooseNum;
            numUsedFlag[chooseNum] = true;
            backtrack(index + 1);
            if (finish) {
                return;
            }
            numUsedFlag[chooseNum] = false;
        }
    }
};

int main(void) {
    Solution solution1;
    vector<int> res1 = solution1.grayCode(2);
    MyTools::printVec(res1);

    Solution solution2;
    vector<int> res2 = solution2.grayCode(1);
    MyTools::printVec(res2);

    return 0;
}
