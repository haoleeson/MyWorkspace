#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

// 回溯 + 各ip数字的最低长度“加速”
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        lenS = s.size();
        if (lenS < 4 || lenS > 12) {
            return res;
        }

        ipNums.resize(4, "");
        backtrace(s, 0, 0);
        return res;
    }

private:
    vector<string> ipNums;
    vector<string> res;
    const string DOT_STR = ".";
    int lenS;

    void backtrace(const string& s, int startI, int ipNumIndex) {
        if (ipNumIndex == 4 || startI > lenS - 1) {
            if (ipNumIndex == 4 && startI == lenS) {
                string ipStr = ipNums[0] + DOT_STR + ipNums[1] + DOT_STR + ipNums[2] + DOT_STR + ipNums[3];
                res.push_back(ipStr);
            }
        }

        // 最小长度
        int minLen = lenS - startI - (3 - ipNumIndex) * 3;
        int minEndI = startI + max(0, minLen - 1);
        int maxEndI = min(startI + 2, lenS - 1);
        // 数字结尾位置
        for (int endI = minEndI; endI <= maxEndI; ++endI) {
            // 若校验合法，添加到 ipNums 暂存
            if (validCheck(s, startI, endI)) {
                string tmp = s.substr(startI, endI - startI + 1);
                ipNums[ipNumIndex] = tmp;
                backtrace(s, endI + 1, ipNumIndex + 1);
            }
        }
    }

    // 校验 ip 数字
    inline bool validCheck(const string& s, int startI, int endI) {
        // 长度检查
        if (endI > startI + 2) {
            return false;
        }

        // 数字字符检查
        for (int i = startI; i <= endI; ++i) {
            if (s[i] < '0' || s[i] > '9') {
                return false;
            }
        }

        // 前导零检查
        if (s[startI] == '0' && endI > startI) {
            return false;
        }

        // str2int 数字范围检查
        int num = 0;
        for (int i = startI; i <= endI; ++i) {
            num = num * 10 + s[i] - '0';
        }
        if (num > 255) {
            return false;
        }

        return true;
    }
};

int main(void) {
    Solution solution1;
    string s1 = "25525511135";
    vector<string> res1 = solution1.restoreIpAddresses(s1);
    MyTools::printVec(res1);

    Solution solution2;
    string s2 = "0000";
    vector<string> res2 = solution2.restoreIpAddresses(s2);
    MyTools::printVec(res2);

    Solution solution3;
    string s3 = "101023";
    vector<string> res3 = solution3.restoreIpAddresses(s3);
    MyTools::printVec(res3);

    return 0;
}
