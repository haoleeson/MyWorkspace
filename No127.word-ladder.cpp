/**
 * No127. 单词接龙 (BFS)
 * 给定两个单词（beginWord 和 endWord）和一个字典，找到从 beginWord 到 endWord 的最短转换序列的长度。转换需遵循如下规则：
 * 每次转换只能改变一个字母。转换过程中的中间单词必须是字典中的单词。

说明:
如果不存在这样的转换序列，返回 0。
所有单词具有相同的长度。
所有单词只由小写字母组成。
字典中不存在重复的单词。
你可以假设 beginWord 和 endWord 是非空的，且二者不相同。

示例 1:
输入:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]
输出: 5
解释: 一个最短转换序列是 "hit" -> "hot" -> "dot" -> "dog" -> "cog",
     返回它的长度 5。

示例 2:
输入:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]
输出: 0
解释: endWord "cog" 不在字典中，所以无法进行转换。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/word-ladder
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
    int m_len;
    bool canConvert(string& A, string& B) {
        int i = 0, diffChNum = 0;
        while (i < m_len && diffChNum < 2) {
            if (A[i] != B[i]) {
                ++diffChNum;
            }
            ++i;
        }
        return i == m_len && diffChNum < 2;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int ans = 0, nowSize = 0, nextSize = 0, endIndex = -1, tmpI, m_size, *tmp;
        m_len = beginWord.length();
        m_size = wordList.size();

        // 是否访问过标记
        bool* achieveFlag = new bool[m_size]{false};
        int* nowWordsIndex = new int[m_size]{0};
        int* nextWordsIndex = new int[m_size]{0};

        // 找到第一步能转换到的单词下标集合
        for (int i = 0; i < m_size; ++i) {
            // 顺带找 endWord 的下标
            if (wordList[i] == endWord) {
                endIndex = i;
            }
            if (canConvert(beginWord, wordList[i])) {
                if (i == endIndex) {
                    delete []achieveFlag;
                    delete []nowWordsIndex;
                    delete []nextWordsIndex;
                    return 2;
                }
                achieveFlag[i] = true;
                ans = 2;
                nowWordsIndex[nowSize++] = i;
            }
        }
        
        // bfs
        while (nowSize > 0) {
            // 对于每轮能访问的 wordList[tmpI]，
            for (int i = 0; i < nowSize; ++i) {
                tmpI = nowWordsIndex[i];
                // 查询其下一步能转换的(未访问过的) wordList[j]
                for (int j = 0; j < m_size; ++j) {
                    if (achieveFlag[j]) {
                        continue;
                    }
                    if (canConvert(wordList[tmpI], wordList[j])) {
                        if (j == endIndex) {
                            delete []achieveFlag;
                            delete []nowWordsIndex;
                            delete []nextWordsIndex;
                            return ans + 1;
                        }
                        achieveFlag[j] = true;
                        nextWordsIndex[nextSize++] = j;
                    }
                }
            }

            if (nextSize == 0) {
                break;
            }
            ++ans;
            nowSize = nextSize;
            nextSize = 0;
            tmp = nowWordsIndex;
            nowWordsIndex = nextWordsIndex;
            nextWordsIndex = tmp;
        }
        delete []achieveFlag;
        delete []nowWordsIndex;
        delete []nextWordsIndex;
        return 0;
    }
};

int main() {
    Solution solution;
    string beginWord = "hit";
    string endWord = "cog";
    string arr[] = {"hot","dot","dog","lot","log","cog"};
    vector<string> wordList(arr, arr + 6);
    cout << solution.ladderLength(beginWord, endWord, wordList);
    return 0;
}
