#include <string.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "myTools.h"

using namespace std;

// 力扣评论：用邻接表表示图，dfs+bfs （通过）
// 链接：https://leetcode.cn/problems/word-ladder-ii/solution/by-tiger-million-xqfd/
class Solution {
public:
    unordered_map<string, unordered_set<string>> mmp;
    bool stop = false;
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> w(wordList.begin(), wordList.end());
        int Len = bfs(beginWord, endWord, w);
        if (!Len) return {};

        vector<vector<string>> ans;
        vector<string> board;
        board.push_back(beginWord);
        bt(ans, board, beginWord, endWord, 1, Len);
        return ans;
    }

    void bt(vector<vector<string>>& ans, vector<string>& board, string beginWord, string& endWord, int i, int len) {
        if (beginWord == endWord && i == len) {
            ans.push_back(board);
            return;
        }
        if (!mmp.count(beginWord) || i > len) {
            return;
        }
        for (string s : mmp[beginWord]) {
            board.push_back(s);
            bt(ans, board, s, endWord, i + 1, len);
            board.pop_back();
        }
    }

    int bfs(string beginWord, string endWord, unordered_set<string> w) {
        if (stop || w.find(endWord) == w.end()) return 0;
        if (beginWord == endWord) return 1;
        unordered_set<string> b{beginWord}, e{endWord};
        int len = beginWord.size(), num = 1;
        bool tag = true, isReverse = false;
        unordered_set<string> father, w1{beginWord}, w2{endWord};

        while (!b.empty() && tag) {
            ++num;
            unordered_set<string> temp;
            for (string s : b) w.erase(s);

            for (string s : b) {
                for (int i = 0; i < len; ++i) {
                    string t = s;
                    for (int j = 0; j < 26; ++j) {
                        t[i] = j + 97;

                        if (w.find(t) == w.end()) continue;

                        if (e.find(t) != e.end()) {
                            tag = false;
                            if (isReverse) {
                                father.insert(t);
                                mmp[t].insert(s);
                            } else {
                                father.insert(s);
                                mmp[s].insert(t);
                            }
                        }

                        temp.insert(t);
                    }
                }
            }

            for (string s : temp) {
                if (isReverse)
                    w2.insert(s);
                else
                    w1.insert(s);
            }

            if (temp.size() <= e.size()) {
                b = temp;
            } else {
                b = e;
                e = temp;
                isReverse = !isReverse;
            }
        }

        if (father.find(beginWord) != father.end())
            return num;
        else if (father.empty())
            stop = true;
        else {
            for (string f : father) {
                bfs(beginWord, f, w1);
                bfs(f, endWord, w2);
            }
        }
        return num;
    }
};

// 力扣旧解：双向 BFS 超时
class Solution6 {
public:
    unordered_map<string, vector<string>> tree; //构建图
    vector<vector<string>> answer;              //存放最终结果

    void DFS(vector<string>& current, string thisWord, string endWord) {
        if (thisWord == endWord) {
            answer.push_back(current);
            return;
        }
        for (string s : tree[thisWord]) {
            current.push_back(s);
            DFS(current, s, endWord);
            current.pop_back();
        }
    }

    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        if (wordList.size() == 0 || find(wordList.begin(), wordList.end(), endWord) == wordList.end()) return {};
        unordered_set<string> bfsFromBegin{beginWord};                //自顶向下的BFS队列
        unordered_set<string> bfsFromEnd{endWord};                    //自底向上的BFS队列
        unordered_set<string> dirc(wordList.begin(), wordList.end()); //初始化字典,记录未被访问过的字符串
        bool findFlag = false; // 判断标志：findFlag两队列是否存在相同的元素
        bool reverseFlag = false; // reverseflag时刻标记当前BFS遍历的方向（false为自顶向下，true为自底向上）

        while (!bfsFromBegin.empty()) {
            unordered_set<string> next;   //存放下一层需要遍历的节点
            for (string s : bfsFromBegin) //遍历过的节点从set中删除 避免成环
                dirc.erase(s);
            for (string s1 : bfsFromBegin) //扩展下一层的节点
            {
                // 模拟 s1[i] 的每一位字符变化
                for (int i = 0; i < s1.size(); ++i) {
                    string s2 = s1; // s2记录由s1扩展而来字符串
                    for (char c = 'a'; c <= 'z'; ++c) {
                        s2[i] = c;
                        if (dirc.count(s2) == 0) continue;
                        if (bfsFromEnd.count(s2)) {
                            findFlag = true; //找到双向BFS重合的字符串，BFS过程即可终止
                        } else {
                            next.insert(s2); //将字符串加入扩展队列
                        }
                        reverseFlag ? tree[s2].push_back(s1)
                                    : tree[s1].push_back(s2); //构建树，并始终保持方向从beginWord指向endWord
                    }
                }
            }
            bfsFromBegin = next; //更新队列
            if (bfsFromBegin.size() > bfsFromEnd.size()) {
                reverseFlag = !reverseFlag;     //取反
                swap(bfsFromBegin, bfsFromEnd); //交换BFS的队列 改变BFS的方向
            }
            if (findFlag) break; // 双向BFS交汇 BFS过程终止
        }

        vector<string> current = {beginWord};
        DFS(current, beginWord, endWord); //遍历形成的树，得到起点到终点的路径
        return answer;
    }
};

// 力扣评论：用邻接表表示图，dfs+bfs （超时）
// 链接：https://leetcode.cn/problems/word-ladder-ii/solution/by-tiger-million-xqfd/
class Solution5 {
    void dfs(const string& beginWord, string& endWord, vector<string>& path, vector<vector<string>>& res,
             unordered_map<string, unordered_set<string>>& mp) {
        // 无需记录当前递归的层数，因为建出来的图就是到最短路径的终点处就截止了
        if (!path.empty() && path.back() == endWord) {
            res.emplace_back(path);
            return;
        }
        for (auto& next : mp[beginWord]) {
            path.emplace_back(next);
            dfs(next, endWord, path, res, mp);
            path.pop_back();
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int n = wordList.size(), len = beginWord.size();
        vector<vector<string>> res;
        unordered_set<string> words;
        unordered_map<string, unordered_set<string>> mp;
        unordered_map<string, int> layers;
        unordered_set<string> vis;

        // 记录每个单词，便于后续查找
        for (auto& w : wordList) words.insert(w);
        if (words.count(endWord) == 0) return res;

        // 将beginword也记录在集合中
        words.insert(beginWord);
        wordList.emplace_back(beginWord);

        // bfs找最短深度,由于需要记录图中每个节点的层数，所以只能将构建图的操作放到bfs中进行
        queue<string> q;
        q.push(beginWord);
        layers[beginWord] = 1; // 层数从1开始，用于区别mp新建元素时默认的val=0
        vis.insert(beginWord); // 需要vis，否则会记录重复
        int depth = 1, found = 0;
        while (!q.empty()) {
            int cnt = q.size();
            ++depth;
            for (int i = 0; i < cnt; ++i) {
                string cur = move(q.front());
                q.pop();
                string tmp = cur;
                // 若找到了最短的终点，可以返回，图也就在此处截止
                if (cur == endWord) {
                    found = 1;
                    break;
                }
                for (int i = 0; i < len; ++i) {
                    char c = tmp[i];
                    for (char j = 'a'; j <= 'z'; ++j) {
                        if (j != c) {
                            tmp[i] = j;
                            // 若新单词不存在集合中，直接遍历下一个
                            if (!words.count(tmp)) continue;
                            // 如果当前节点已被访问过，且层数与当前节点在同一层，那么同层之间的边不记录
                            if (layers[tmp] == layers[cur]) continue;
                            // 因为有的节点可能有两个及以上的前驱节点，第一个节点访问后会造成vis为true，但是第二个前驱节点又需要与
                            // 其建边，此时判断在cur节点的下一层时，需要记录
                            if (layers[tmp] == depth) mp[cur].insert(tmp);
                            if (vis.count(tmp)) continue;
                            q.push(tmp);
                            layers[tmp] = depth;
                            mp[cur].insert(tmp);
                            vis.insert(tmp);
                        }
                    }
                    tmp[i] = c;
                }
            }
            if (found) break;
        }
        // dfs找路径
        vector<string> path;
        path.emplace_back(beginWord);
        dfs(beginWord, endWord, path, res, mp);
        return res;
    }
};

// 力扣评论：双向BFS（超时，通过用例 34/35）
// 保存遍历的字符串的索引作为路径，最后还原成字符串
// 链接：https://leetcode.cn/problems/word-ladder-ii/solution/xiang-xi-tong-su-de-si-lu-fen-xi-duo-jie-fa-by-3-3/
class Solution4 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> words;
        for (int i = 0; i < wordList.size(); ++i) {
            words[wordList[i]] = i;
        }

        if (words.find(endWord) == words.end()) {
            return vector<vector<string>>();
        }

        if (words.find(beginWord) == words.end()) {
            words[beginWord] = wordList.size();
            wordList.push_back(beginWord);
        }

        int beginIndex = words[beginWord];
        int endIndex = words[endWord];
        int size = beginWord.size();

        vector<bool> used(wordList.size());
        unordered_map<int, vector<vector<int>>> frontList;
        frontList[beginIndex] = {{beginIndex}};
        unordered_map<int, vector<vector<int>>> backList;
        backList[endIndex] = {{endIndex}};
        vector<vector<int>> ansIndex;
        bool frontIsBegin = true;
        while (ansIndex.empty() && frontList.empty() == false) {
            for (auto& i : frontList) {
                used[i.first] = true;
            }

            unordered_map<int, vector<vector<int>>> next;
            for (auto& i : frontList) {
                for (int j = 0; j < size; ++j) {
                    string ts = wordList[i.first];
                    for (char k = 'a'; k <= 'z'; ++k) {
                        ts[j] = k;
                        if (words.find(ts) == words.end() || used[words[ts]]) {
                            continue;
                        }

                        int cur = words[ts];
                        if (backList.find(cur) == backList.end()) {
                            for (vector<int> l : i.second) {
                                l.push_back(cur);
                                next[cur].push_back(move(l));
                            }
                        } else {
                            if (frontIsBegin) {
                                for (auto& l : i.second) {
                                    for (auto& m : backList[cur]) {
                                        auto route = l;
                                        for (auto n = m.rbegin(); n != m.rend(); ++n) {
                                            route.push_back(*n);
                                        }

                                        ansIndex.push_back(move(route));
                                    }
                                }
                            } else {
                                for (auto& l : backList[cur]) {
                                    for (auto& m : i.second) {
                                        auto route = l;
                                        for (auto n = m.rbegin(); n != m.rend(); ++n) {
                                            route.push_back(*n);
                                        }

                                        ansIndex.push_back(move(route));
                                    }
                                }
                            }
                        }
                    }
                }
            }

            if (next.size() >= backList.size()) {
                frontIsBegin = !frontIsBegin;
                frontList = move(backList);
                backList = move(next);
            } else {
                frontList = move(next);
            }
        }

        vector<vector<string>> ans;
        for (auto& i : ansIndex) {
            vector<string> route;
            for (auto& j : i) {
                route.push_back(wordList[j]);
            }

            ans.push_back(move(route));
        }

        return ans;
    }
};

// 力扣评论思路：双向BFS （超时， 通过用例 34/35）
// 链接：https://leetcode.cn/problems/word-ladder-ii/solution/2chong-jie-fa-jian-ji-dai-ma-qing-xi-jie-3sjt/
class Solution3 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> res; //用来保存所有路径
        unordered_set<string> dict(wordList.begin(), wordList.end()), head{beginWord}, tail{endWord};
        if (!dict.count(endWord)) return res;       //如果没找到end，直接返回空。
        dict.erase(beginWord), dict.erase(endWord); //移除掉开头和结尾单词
        unordered_map<string, vector<string>> next; // key为这个节点，value为下一个变化一个字母的节点
        bool reversed = false, found = false;       // reversed判断正向，还是反向，found为是否找到。
        while (!head.empty()) {                     //验证一下是否需要判断tail为空
            unordered_set<string> temp;             //保存已转化过的string
            for (const auto& w : head) {
                string s = w; //在之后要不断变换s的每一位，并去已有数据中查找是否存在
                for (size_t i = 0; i < s.size(); ++i) {
                    /*
                    与int固定四个字节不同有所不同,
                    size_t的取值range是目标平台下最大可能的数组尺寸,
                    一些平台下size_t的范围小于int的正数范围,又或者大于unsigned int.
                    使用Int既有可能浪费，又有可能范围不够大。
                    */
                    char c = s[i]; //保存变换之前的字符
                    for (char j = 'a'; j <= 'z'; ++j) {
                        s[i] = j;
                        if (tail.count(s)) {
                            //判断是否存在于对向列表，如果存在，证明双向在中间交汇了
                            reversed ? next[s].push_back(w) : next[w].push_back(s);
                            //如果是正向的，则这个节点作为父节点，下个节点作为子节点，如果是反向的，则相反。
                            found = true;
                        }
                        if (dict.count(s)) {
                            reversed ? next[s].push_back(w) : next[w].push_back(s); //同上
                            temp.insert(s);
                        }
                    }
                    s[i] = c; //恢复原样
                }
            }
            if (found) break;
            for (const auto& w : temp) dict.erase(w); //删除已经加入树的string
            if (temp.size() <= tail.size())
                head = temp; //判断双向两边谁的节点多，从少的开始。
            else {
                reversed = !reversed;
                head = tail;
                tail = temp;
            }
        }
        //以上，bfs就算完成了，也为dfs建立了基础，生成了一颗节点树。
        if (found) {
            vector<string> path = {beginWord};                 //创建一条路径
            backtracking(beginWord, endWord, next, path, res); //回溯
        }
        return res;
    }

private:
    void backtracking(const string& src, const string& dst, unordered_map<string, vector<string>>& next,
                      vector<string>& path, vector<vector<string>>& res) {
        if (src == dst) res.push_back(path);
        for (const auto& w : next[src]) {
            path.push_back(w);
            backtracking(w, dst, next, path, res);
            path.pop_back();
        }
    }
};

// 力扣评论思路：单向(自上而下) BFS
// 链接：https://leetcode.cn/problems/word-ladder-ii/solution/2chong-jie-fa-jian-ji-dai-ma-qing-xi-jie-3sjt/
class Solution2 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> search(wordList.begin(), wordList.end()); // hash 提高转换(查找)效率
        vector<vector<string>> res;
        deque<vector<string>> worker;  // 层节点容器
        worker.push_back({beginWord}); // beginWord 作为起始的根节点
        while (!worker.empty()) {
            unordered_set<string> visited;            // 一层内已转化过的 string 容器。set避免重复保存
            for (int i = worker.size(); i > 0; --i) { // 层遍历
                auto sub = worker.front();
                worker.pop_front();     // 获取单个节点
                auto tail = sub.back(); // 获取单个节点内的最后一个 string 元素
                if (tail == endWord) {  // 是在到达是转换的终点
                    res.push_back(sub);
                    continue;
                }
                for (int j = 0; j < tail.size(); ++j) { // 回溯试探 下层 节点的元素的可能性
                    char temp = tail[j];                // 单个 string 回溯保存状态
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == temp) continue; // 忽略原始状态
                        tail[j] = c;
                        if (!search.count(tail)) continue; // 未找到转换序
                        visited.insert(tail);              // 找到转换序，保存 已使用 转换
                        sub.push_back(tail);               // 节点 回溯
                        worker.push_back(sub);             // 向容器内保存 子节点
                        sub.pop_back();                    // 回溯恢复
                    }
                    tail[j] = temp; // string 回溯恢复状态
                }
            }
            if (res.size()) return res;              // 第一次到达 树底，也就是得到最小转换序
            for (auto& w : visited) search.erase(w); // 删除已使用的转换序
        }
        return {};
    }
};

// 思路：Dfs 回溯，优化，仍超时 （通过用例：21 / 35）
class Solution1 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        _lenL = wordList.size();
        _lenW = beginWord.length();

        // 转全局变量
        _beginWord = beginWord;
        _targetWord = endWord;
        _wordList = vector<string>(wordList);

        // 字典中单词使用记录
        _accessFlag = new bool[_lenL]{false};
        // dfs 访问下标记录
        _indexList = new int[_lenL]{0};

        // 先统计各个单词相差为 1 的单词下标
        _canAccessIndex = vector<unordered_set<int>>(_lenL, unordered_set<int>{});
        for (int i = 0; i < _lenL; ++i) {
            for (int j = i + 1; j < _lenL; ++j) {
                if (onlyOneChDiff(wordList[i], wordList[j])) {
                    // 双向添加能访问
                    _canAccessIndex[i].insert(j);
                    _canAccessIndex[j].insert(i);
                }
            }
        }

        backTrace(beginWord, -1, 0);

        return res;
    }

private:
    int _lenL, _lenW;
    bool* _accessFlag;
    string _beginWord, _targetWord;
    vector<string> _wordList;
    vector<unordered_set<int>> _canAccessIndex;
    int* _indexList;
    int _minLen = INT_MAX;
    vector<vector<string>> res;

    void backTrace(string& curWord, int curWordIndex, int iterator) {
        // 结束条件
        if (curWord == _targetWord) {
            if (iterator <= _minLen) {
                // 组装可行转换序列
                vector<string> tmp(iterator + 1);
                tmp[0] = _beginWord;
                for (int i = 0; i < iterator; ++i) {
                    tmp[i + 1] = _wordList[_indexList[i]];
                }

                // 更短转换序列
                if (iterator < _minLen) {
                    res.clear();
                    vector<vector<string>> emptyV;
                    res.swap(emptyV);
                    _minLen = iterator;
                }
                res.push_back(tmp);
            }

            return;
        } else if (iterator >= _minLen) {
            // 由于找最短序列，故深度超过已知可行序列的深度时，不必再下探了
            return;
        }

        // 遍历所有可能解
        if (curWordIndex != -1) {
            unordered_set<int>::iterator it;
            for (it = _canAccessIndex[curWordIndex].begin(); it != _canAccessIndex[curWordIndex].end(); ++it) {
                int i = *it;
                // 单词已用过，跳过
                if (_accessFlag[i]) {
                    continue;
                }

                _indexList[iterator] = i;
                _accessFlag[i] = true;
                backTrace(_wordList[i], i, iterator + 1);
                _accessFlag[i] = false;
            }

        } else {
            for (int i = 0; i < _lenL; ++i) {
                // 单词已用过，跳过
                if (_accessFlag[i]) {
                    continue;
                }

                // 不满足相邻仅一字符差异，跳过
                if (!onlyOneChDiff(curWord, _wordList[i])) {
                    continue;
                }

                _indexList[iterator] = i;
                _accessFlag[i] = true;
                backTrace(_wordList[i], i, iterator + 1);
                _accessFlag[i] = false;
            }
        }
    }

    inline bool onlyOneChDiff(string& a, string& b) {
        bool hasDiffCh = false;
        for (int i = 0; i < _lenW; ++i) {
            if (a[i] != b[i]) {
                if (hasDiffCh) {
                    // 第二个相异字符
                    return false;
                } else {
                    // 第一个相异字符
                    hasDiffCh = true;
                }
            }
        }
        return hasDiffCh;
    }
};

// 思路：Dfs 回溯，超时 （通过用例：19 / 35）
class Solution0 {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        _lenL = wordList.size();
        _lenW = beginWord.length();

        // 转全局变量
        _beginWord = beginWord;
        _targetWord = endWord;
        _wordList = vector<string>(wordList);

        // 字典中单词使用记录
        _accessFlag = new bool[_lenL]{false};
        // dfs 访问下标记录
        _indexList = new int[_lenL]{0};

        backTrace(beginWord, 0);

        return res;
    }

private:
    int _lenL, _lenW;
    bool* _accessFlag;
    string _beginWord, _targetWord;
    vector<string> _wordList;
    int* _indexList;
    int _minLen = INT_MAX;
    vector<vector<string>> res;

    void backTrace(string& curWord, int iterator) {
        // 结束条件
        if (curWord == _targetWord) {
            if (iterator <= _minLen) {
                // 组装可行转换序列
                vector<string> tmp(iterator + 1);
                tmp[0] = _beginWord;
                for (int i = 0; i < iterator; ++i) {
                    tmp[i + 1] = _wordList[_indexList[i]];
                }

                // 更短转换序列
                if (iterator < _minLen) {
                    res.clear();
                    vector<vector<string>> emptyV;
                    res.swap(emptyV);
                    _minLen = iterator;
                }
                res.push_back(tmp);
            }

            return;
        } else if (iterator >= _lenL) {
            return;
        }

        // 遍历所有可能解
        for (int i = 0; i < _lenL; ++i) {
            // 单词已用过，跳过
            if (_accessFlag[i]) {
                continue;
            }

            // 不满足相邻仅一字符差异，跳过
            if (!onlyOneChDiff(curWord, _wordList[i])) {
                continue;
            }

            _indexList[iterator] = i;
            _accessFlag[i] = true;
            backTrace(_wordList[i], iterator + 1);
            _accessFlag[i] = false;
        }
    }

    inline bool onlyOneChDiff(string& a, string& b) {
        bool hasDiffCh = false;
        for (int i = 0; i < _lenW; ++i) {
            if (a[i] != b[i]) {
                if (hasDiffCh) {
                    // 第二个相异字符
                    return false;
                } else {
                    // 第一个相异字符
                    hasDiffCh = true;
                }
            }
        }
        return hasDiffCh;
    }
};

int main(void) {
    Solution solution1;
    string beginWord1 = "hit";
    string endWord1 = "cog";
    string arr1[] = {"hot", "dot", "dog", "lot", "log", "cog"};
    int lenL1 = sizeof(arr1) / sizeof(string);
    vector<string> wordList1(lenL1);
    for (int i = 0; i < lenL1; ++i) {
        wordList1[i] = arr1[i];
    }
    vector<vector<string>> res1 = solution1.findLadders(beginWord1, endWord1, wordList1);
    MyTools::printVec2D(res1);

    Solution solution2;
    string beginWord2 = "hit";
    string endWord2 = "cog";
    string arr2[] = {"hot", "dot", "dog", "lot", "log"};
    int lenL2 = sizeof(arr2) / sizeof(string);
    vector<string> wordList2(lenL2);
    for (int i = 0; i < lenL2; ++i) {
        wordList2[i] = arr2[i];
    }
    vector<vector<string>> res2 = solution2.findLadders(beginWord2, endWord2, wordList2);
    MyTools::printVec2D(res2);

    return 0;
}
