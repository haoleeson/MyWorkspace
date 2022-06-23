#include <iostream>
#include <unordered_map>
#include <vector>

#include "myTools.h"
using namespace std;

// 滑动窗口 + 哈希表 O(n)
// （132ms, 16MB)
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        lenS = s.size();
        lenWords = words.size();
        lenW = words[0].size();
        lenSubStr = lenWords * lenW;

        if (lenS < lenSubStr) {
            return res;
        }

        // 统计目标子串所用到的各字符数量
        initNeed(words);

        // 滑动窗口，过滤出长度刚好且用到各字符数相同的子串，并校验，O(n)
        int left = 0, right = 0;
        int valid = 0;
        while (right < lenS) {
            char c = s[right];
            ++right;
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    ++valid;
                }
            }

            while (valid == lenNeed) {
                if (right - left == lenSubStr && isSubStr(s, left, words)) {
                    res.push_back(left);
                }
                char d = s[left];
                ++left;
                if (need.count(d)) {
                    if (window[d] == need[d]) {
                        --valid;
                    }
                    window[d]--;
                }
            }
        }

        return res;
    }

private:
    int lenS, lenWords, lenW, lenSubStr, lenNeed, lenWordMap;
    unordered_map<char, int> need, window;
    unordered_map<string, int> wordsMap;

    inline void initNeed(vector<string>& words) {
        for (int i = 0; i < lenWords; ++i) {
            for (int j = 0; j < lenW; ++j) {
                need[words[i][j]]++;
            }
        }
        lenNeed = need.size();

        for (string word : words) {
            wordsMap[word]++;
        }
        lenWordMap = wordsMap.size();
    }

    // 判断子串合法性
    inline bool isSubStr(string& s, int iS, vector<string>& words) {
        unordered_map<string, int> curMap;
        unordered_map<string, int>::iterator wordsMapIterator, curMapIterator;

        // 将 s 从下标 iS 开始分割为 lenWords 个单词，依次比较
        for (int i = 0; i < lenWords; ++i) {
            string tmpWord = s.substr(iS + i * lenW, lenW);
            curMap[tmpWord]++;

            wordsMapIterator = wordsMap.find(tmpWord);
            curMapIterator = curMap.find(tmpWord);

            // 不存在 或 单词用超了
            if (wordsMapIterator == wordsMap.end() || curMapIterator->second > wordsMapIterator->second) {
                return false;
            }
        }

        return curMap.size() == lenWordMap;
    }
};

// 滑动窗口 O(n)
// （600ms, 15.3MB）
class Solution0 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        lenS = s.size();
        lenWords = words.size();
        lenW = words[0].size();
        lenSubStr = lenWords * lenW;

        if (lenS < lenSubStr) {
            return res;
        }

        // 统计目标子串所用到的各字符数量
        initNeed(words);

        // 滑动窗口，过滤出长度刚好且用到各字符数相同的子串，并校验，O(n)
        int left = 0, right = 0;
        int valid = 0;
        while (right < lenS) {
            char c = s[right];
            ++right;
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    ++valid;
                }
            }

            while (valid == lenNeed) {
                if (right - left == lenSubStr && isSubStr(s, left, words)) {
                    res.push_back(left);
                }
                char d = s[left];
                ++left;
                if (need.count(d)) {
                    if (window[d] == need[d]) {
                        --valid;
                    }
                    window[d]--;
                }
            }
        }

        return res;
    }

private:
    int lenS, lenWords, lenW, lenSubStr, lenNeed;
    unordered_map<char, int> need, window;

    inline void initNeed(vector<string>& words) {
        for (int i = 0; i < lenWords; ++i) {
            for (int j = 0; j < lenW; ++j) {
                need[words[i][j]]++;
            }
        }
        lenNeed = need.size();
    }

    // 判断字符串 s 中以 iS 下标开头的后 lenW 长度的字符串是否为 words 的第 iW 个单词
    inline bool isSubWord(string& s, int iS, vector<string>& words, int iW) {
        for (int i = 0; i < lenW; ++i) {
            if (s[iS + i] != words[iW][i]) {
                return false;
            }
        }
        return true;
    }

    // 判断子串合法性
    inline bool isSubStr(string& s, int iS, vector<string>& words) {
        bool* wordUsedFlag = new bool[lenWords]{false};

        for (int i = 0; i < lenWords; ++i) {
            bool find = false;
            // 匹配 words 中的第几个单词
            for (int j = 0; j < lenWords; ++j) {
                if (wordUsedFlag[j]) {
                    continue;
                }
                // 若单词匹配
                if (isSubWord(s, iS + i * lenW, words, j)) {
                    wordUsedFlag[j] = true;
                    find = true;
                    break;
                }
            }
            if (!find) {
                return false;
            }
        }

        return true;
    }
};

int main(void) {
    Solution solution1;
    string s1 = "barfoothefoobarman";
    string arr1[] = {"foo", "bar"};
    vector<string> words1(arr1, arr1 + sizeof(arr1) / sizeof(string));
    vector<int> res1 = solution1.findSubstring(s1, words1);
    MyTools::printVec(res1);

    Solution solution2;
    string s2 = "wordgoodgoodgoodbestword";
    string arr2[] = {"word", "good", "best", "word"};
    vector<string> words2(arr2, arr2 + sizeof(arr2) / sizeof(string));
    vector<int> res2 = solution2.findSubstring(s2, words2);
    MyTools::printVec(res2);

    Solution solution3;
    string s3 = "barfoofoobarthefoobarman";
    string arr3[] = {"bar", "foo", "the"};
    vector<string> words3(arr3, arr3 + sizeof(arr3) / sizeof(string));
    vector<int> res3 = solution3.findSubstring(s3, words3);
    MyTools::printVec(res3);

    Solution solution4;
    string s4 = "abaababbaba";
    string arr4[] = {"ba", "ab", "ab"};
    vector<string> words4(arr4, arr4 + sizeof(arr4) / sizeof(string));
    vector<int> res4 = solution4.findSubstring(s4, words4);
    MyTools::printVec(res4);

    return 0;
}
