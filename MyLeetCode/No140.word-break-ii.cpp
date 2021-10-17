/**
 * No140. 单词拆分 II
 * 给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，在字符串中增加空格来构建一个句子，使得句子中所有的单词都在词典中。返回所有这些可能的句子。

说明：
分隔时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。

示例 1：
输入:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
输出:
[
 "cats and dog",
 "cat sand dog"
]

示例 2：
输入:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
输出:
[
 "pine apple pen apple",
 "pineapple pen apple",
 "pine applepen apple"
]
解释: 注意你可以重复使用字典中的单词。

示例3：
输入:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
输出:
[]

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-break-ii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string.h>
#include "myTools.h"
using namespace std;

/**
 * 力扣路人：动态规划
 * 思路
动态规划
前面先算是否可以全部拆分
跟 139.单词拆分 一样
实际上我也是直接把那个代码原封不动加进来了
如果不先验证能否拆分，直接求字符串，某用例给我把内存爆到 10 个 g

如果可以拆分，接下来组合字符串
定义 vector<vector<string>> dp(s.size() + 1, vector<string>())
假设从开始到第 i - 1 个字符是与字典匹配的一个词，那么第 i 个字符是一个新词的开头字母
把这个词添加到 dp[i] 中
从第 i 个字符如果再匹配到一个词，把 dp[i] 中的每个词加个空格再加上新词，添加到后面的 dp[j] 中
dp[i] 表示第 i 个字符前，所有的拆分情况
所以，答案应该为 dp.back()

作者：ikaruga
链接：https://leetcode-cn.com/problems/word-break-ii/solution/140-by-ikaruga/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 */
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        if (!wordBreak_139(s, wordDict)) return {};

        size_t validEnd = 0;
        vector<vector<string>> dp(s.size() + 1, vector<string>());

        for (size_t i = 0; i < s.size(); i++) {
            if (i == validEnd + 1) return {};
            if (i != 0 && dp[i].empty()) continue;
            for (auto& word : wordDict) {
                size_t newEnd = i + word.size();
                if (newEnd > s.size()) continue;
                if (memcmp(&s[i], &word[0], word.size()) != 0) continue;
                validEnd = max(validEnd, newEnd);
                if (i == 0) {
                    dp[newEnd].push_back(word);
                    continue;
                }
                for (auto& d : dp[i]) {
                    dp[newEnd].push_back(d + " " + word);
                }
            }
        }

        return dp.back();
    }

    bool wordBreak_139(string& s, vector<string>& wordDict) {
        size_t validEnd = 0;
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (size_t i = 0; i < s.size(); i++) {
            if (i == validEnd + 1) return false;
            if (!dp[i]) continue;
            for (auto& word : wordDict) {
                size_t newEnd = i + word.size();
                if (newEnd > s.size()) continue;
                if (memcmp(&s[i], &word[0], word.size()) == 0) {
                    dp[newEnd] = true;
                    validEnd = max(validEnd, newEnd);
                }
            }
        }
        return dp.back();
    }
};

/**
 * dfs + 加备忘录：仍然超时
 */
class Solution2 {
    vector<vector<string>> memo;// 备忘录
    string m_s;
    int len;
    // 判断：从字符串指定下标后方是否紧跟着 str
    bool startWithWorld(int startIndex, string& str) {
        if (startIndex + str.length() > len) {
            return false;
        }
        for (char ch : str) {
            if (m_s[startIndex++] != ch) {
                return false;
            }
        }
        return true;
    }

    /**
     * dfs
     * @param startIndex
     * @param wordDict
     * @return true -- 从startIndex起的字符串的能被完整拆分
     */
    void dfs(int startIndex, vector<string>& wordDict) {
        if (startIndex >= len) {
            return;
        }
        for (string str : wordDict) {
            if (startWithWorld(startIndex, str)) {
                int nextIndex = startIndex + str.length();
                if (nextIndex == len) {
                    memo[startIndex].push_back(str);
                    continue;
                }
                // 若备忘录非空，优先读备忘录
                if (memo[nextIndex].empty()) {
                    dfs(nextIndex, wordDict);
                }
                for (string memo_str : memo[nextIndex]) {
                    memo[startIndex].push_back(str + " " + memo_str);
                }
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        m_s = s;
        len = s.length();
        memo.resize(len + 1);
        dfs(0, wordDict);
        return memo[0];
    }
};

/**
 * 暴力 dfs ：超时
 */
class Solution1 {
    vector<string> ans;
    vector<string> wordsArr;
    string m_s;
    int len;
    // 判断：从字符串指定下标后方是否紧跟着 str
    bool startWithWorld(int startIndex, string& str) {
        if (startIndex + str.length() > len) {
            return false;
        }
        for (char ch : str) {
            if (m_s[startIndex++] != ch) {
                return false;
            }
        }
        return true;
    }
    void dfs(int startIndex, vector<string>& wordDict) {
        if (startIndex == len) {
            // 拼接字符串
            string tmpStr = "";
            int wordsArrSize = wordsArr.size();
            if (wordsArrSize > 0) {
                tmpStr += wordsArr[0];
                for (int i = 1; i < wordsArrSize; ++i) {
                    tmpStr += " " + wordsArr[i];
                }
            }
            ans.push_back(tmpStr);
            return;
        }
        for (string str : wordDict) {
            if (startWithWorld(startIndex,  str)) {
                wordsArr.push_back(str);
                dfs(startIndex + str.length(), wordDict);
                wordsArr.pop_back();
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        m_s = s;
        len = s.length();
        dfs(0, wordDict);
        return ans;
    }
};

int main() {
    Solution solution;
    string s = "catsanddog";
    string strs[] = {"cat", "cats", "and", "sand", "dog"};
    vector<string> wordDict(strs, strs + 5);
    vector<string>result = solution.wordBreak(s, wordDict);
    MyTools::printVec(result);
    return 0;
}
