
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class MagicDictionary {
public:
    MagicDictionary() {}

    void buildDict(vector<string> dictionary) {
        // 将字典内所有单词添加到 map <单词长度，单词set>
        for (string& str : dictionary) {
            int len = str.length();
            if (!_m.count(len)) {
                unordered_set<string> s;
                s.insert(str);
                _m[len] = s;
            } else {
                _m[len].insert(str);
            }
        }
    }

    bool search(string searchWord) {
        int len = searchWord.length();
        if (!_m.count(len)) {
            return false;
        }

        unordered_set<string>& s = _m[len];
        for (unordered_set<string>::iterator it = s.begin(); it != s.end(); ++it) {
            // 逐一与 set 中的各个单词对比
            int diffCnt = 0;
            for (int i = 0; i < len; ++i) {
                if (searchWord[i] != it->at(i)) {
                    ++diffCnt;
                    if (diffCnt == 2) {
                        break;
                    }
                }
            }
            if (diffCnt == 1) {
                return true;
            }
        }

        return false;
    }

private:
    unordered_map<int, unordered_set<string>> _m;
};

int main() {
    MagicDictionary magicDictionary;
    string arr1[] = {"hello", "leetcode"};
    vector<string> dictionary1(arr1, arr1 + sizeof(arr1) / sizeof(string));

    magicDictionary.buildDict(dictionary1);
    bool res1 = magicDictionary.search("hello");
    cout << res1 << endl;
    bool res2 = magicDictionary.search("hhllo");
    cout << res2 << endl;
    bool res3 = magicDictionary.search("hell");
    cout << res3 << endl;
    bool res4 = magicDictionary.search("leetcode");
    cout << res4 << endl;

    return 0;
}
