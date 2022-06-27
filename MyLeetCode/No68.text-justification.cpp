#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int lenW = words.size();
        int startI = 0, endI;
        int tmpWidth, intervalCnt, spacesNeedCnt, baseInterval, moreSpacesCnt;

        while (startI < lenW) {
            endI = startI;
            tmpWidth = 0;

            // 逐行填充（贪心）
            while (endI < lenW && tmpWidth + words[endI].size() <= maxWidth) {
                tmpWidth += words[endI].size() + 1; // 预留 1 个空格位
                ++endI;
            }
            --endI;

            // 将 [startI, endI] 组装为一行
            string line = "";
            intervalCnt = endI - startI; // 单词间隔数
            spacesNeedCnt = maxWidth - (tmpWidth - (endI + 1 - startI));

            if (intervalCnt == 0) {
                line = words[startI] + nSpaces(maxWidth - words[startI].size());
            } else if (endI == lenW - 1) {
                // 若为最后一行，左对齐（中间间隔数为1，尾部补空格）
                for (int i = 0; i < intervalCnt; ++i) {
                    line += words[startI + i] + nSpaces(1);
                    --spacesNeedCnt;
                }
                line += words[endI] + nSpaces(spacesNeedCnt);
            } else {
                baseInterval = spacesNeedCnt / intervalCnt;  // 平均每个间隔需填充 x 个空格
                moreSpacesCnt = spacesNeedCnt % intervalCnt; // 左侧前几个需多补 1 个空格
                for (int i = 0; i < intervalCnt; ++i) {
                    if (i < moreSpacesCnt) {
                        line += words[startI + i] + nSpaces(baseInterval + 1);
                    } else {
                        line += words[startI + i] + nSpaces(baseInterval);
                    }
                }
                line += words[endI];
            }
            res.push_back(line);

            startI = endI + 1;
        }

        return res;
    }

private:
    inline string nSpaces(int n) {
        if (n <= 0) {
            return "";
        }

        char* buf = new char[n + 1];
        for (int i = 0; i < n; ++i) {
            buf[i] = ' ';
        }
        buf[n] = '\0';
        return string(buf);
    }
};

int main(void) {
    Solution solution;
    string arr1[] = {"This", "is", "an", "example", "of", "text", "justification."};
    vector<string> words1(arr1, arr1 + sizeof(arr1) / sizeof(string));
    int maxWidth1 = 16;
    vector<string> res1 = solution.fullJustify(words1, maxWidth1);
    MyTools::printVec(res1);

    string arr2[] = {"What", "must", "be", "acknowledgment", "shall", "be"};
    vector<string> words2(arr2, arr2 + sizeof(arr2) / sizeof(string));
    int maxWidth2 = 16;
    vector<string> res2 = solution.fullJustify(words2, maxWidth2);
    MyTools::printVec(res2);

    string arr3[] = {"Science", "is", "what",      "we",  "understand", "well",       "enough", "to", "explain",
                     "to",      "a",  "computer.", "Art", "is",         "everything", "else",   "we", "do"};
    vector<string> words3(arr3, arr3 + sizeof(arr3) / sizeof(string));
    int maxWidth3 = 20;
    vector<string> res3 = solution.fullJustify(words3, maxWidth3);
    MyTools::printVec(res3);

    string arr4[] = {"What", "must", "be", "acknowledgment", "shall", "be"};
    vector<string> words4(arr4, arr4 + sizeof(arr4) / sizeof(string));
    int maxWidth4 = 16;
    vector<string> res4 = solution.fullJustify(words4, maxWidth4);
    MyTools::printVec(res4);

    return 0;
}
