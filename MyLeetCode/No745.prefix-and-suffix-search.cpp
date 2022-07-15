#include <iostream>
#include <unordered_map>

#include "myTools.h"

using namespace std;

// 限定条件：
// 1 <= words[i].length <= 7
// 1 <= pref.length, suff.length <= 7

// 思路： 字典树
// 链接：https://leetcode.cn/problems/prefix-and-suffix-search/solution/qian-zhui-he-hou-zhui-sou-suo-by-leetcod-i3ec/
struct Trie {
    unordered_map<string, Trie*> children;
    int weight; //
};

class WordFilter {
private:
    Trie* trie;

public:
    WordFilter(vector<string>& words) {
        trie = new Trie();

        // 对各单词构建字典树
        for (int i = 0; i < words.size(); ++i) {
            string word = words[i];
            Trie* cur = trie;

            // 对单词 word[i] 插入对应字典树的前后缀 key 对
            int m = word.size();
            for (int j = 0; j < m; ++j) {
                Trie* tmp = cur;
                // 插入前后缀对：前缀补足特殊字符
                for (int k = j; k < m; ++k) {
                    string key({word[k], '#'});
                    if (!tmp->children.count(key)) {
                        tmp->children[key] = new Trie();
                    }
                    tmp = tmp->children[key];
                    tmp->weight = i;
                }
                tmp = cur;
                // 插入前后缀对：后缀补足特殊字符
                for (int k = j; k < m; k++) {
                    string key({'#', word[m - k - 1]});
                    if (!tmp->children.count(key)) {
                        tmp->children[key] = new Trie();
                    }
                    tmp = tmp->children[key];
                    tmp->weight = i;
                }
                // 插入前后缀对
                string key({word[j], word[m - j - 1]});
                if (!cur->children.count(key)) {
                    cur->children[key] = new Trie();
                }
                cur = cur->children[key];
                cur->weight = i;
            }
        }
    }

    int f(string pref, string suff) {
        Trie* cur = trie;
        int m = max(pref.size(), suff.size());

        // 注意按前后缀对搜索 字典树
        for (int i = 0; i < m; i++) {
            // 逐一搜索前后缀对（不足补特殊字符）
            char c1 = i < pref.size() ? pref[i] : '#';
            char c2 = i < suff.size() ? suff[suff.size() - 1 - i] : '#';
            string key({c1, c2});
            // 中间未搜到，终止返回 -1
            if (!cur->children.count(key)) {
                return -1;
            }
            cur = cur->children[key];
        }

        return cur->weight;
    }
};

// 暴力思路：保存所有前缀后缀可能性
// 链接：https://leetcode.cn/problems/prefix-and-suffix-search/solution/qian-zhui-he-hou-zhui-sou-suo-by-leetcod-i3ec/
class WordFilter0 {
private:
    unordered_map<string, int> dict;

public:
    WordFilter0(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            int m = words[i].size();
            string word = words[i];
            for (int prefixLength = 1; prefixLength <= m; prefixLength++) {
                for (int suffixLength = 1; suffixLength <= m; suffixLength++) {
                    string key = word.substr(0, prefixLength) + '#' + word.substr(m - suffixLength);
                    dict[key] = i;
                }
            }
        }
    }

    int f(string pref, string suff) {
        string target = pref + '#' + suff;
        return dict.count(target) ? dict[target] : -1;
    }
};

int main(int argc, const char* argv[]) {
    string arr1[] = {"apple"};
    vector<string> words1(arr1, arr1 + sizeof(arr1) / sizeof(string));
    WordFilter wordFilter1(words1);
    string pref1 = "a";
    string suff1 = "e";
    int res1 = wordFilter1.f(pref1, suff1);
    cout << res1 << endl;

    return 0;
}
