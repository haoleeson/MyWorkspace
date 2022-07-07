#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    string replaceWords(vector<string>& dictionary, string sentence) {
        int lenD = dictionary.size(), lenS = sentence.length();

        sort(dictionary.begin(), dictionary.end());

        // 记录首字母，与词根 map（加速）
        unordered_map<char, vector<string>> m;
        for (int i = 0; i < lenD; ++i) {
            if (m.count(dictionary[i][0])) {
                m[dictionary[i][0]].push_back(dictionary[i]);
            } else {
                vector<string> v(1, dictionary[i]);
                m[dictionary[i][0]] = v;
            }
        }

        char* buff = new char[lenS + 1]{0};
        int iterator = 0;

        int i = 0, pos = 0;
        string str, findDictStr;

        while (i < lenS) {
            // 获取单词（截止至下一空格，或结尾）
            while (i < lenS && sentence[i] != ' ') {
                ++i;
            }
            str = sentence.substr(pos, i - pos);

            // 查询有无词根（有--填充词根； 无 -- 原封填充）
            if (m.count(str[0]) && findDict(str, m[str[0]], findDictStr)) {
                // 替换填充词根到 buff
                int len = findDictStr.length();
                for (int j = 0; j < len; ++j) {
                    buff[iterator++] = findDictStr[j];
                }
            } else {
                // 无词根，原封填充
                for (int j = pos; j < i; ++j) {
                    buff[iterator++] = sentence[j];
                }
            }

            // 填充单词间空格
            if (i != lenS) {
                buff[iterator++] = ' ';
            }

            ++i;
            pos = i;
        }

        buff[iterator] = '\0';

        return string(buff);
    }

private:
    // 从部分字典中查找词根
    // @Return true -- 已找到，且赋值给入参 findDictStr； false -- 未找到
    bool findDict(string& str, vector<string>& subDictList, string& findDictStr) {
        int lenS = str.length(), sizeP = subDictList.size();
        int maxMathLen = 0;

        // 逐个匹配前缀
        for (int i = 0, len; i < sizeP; ++i) {
            len = subDictList[i].length();
            if (len > lenS) {
                continue;
            }
            // 前缀匹配
            int j = 0;
            while (j < len && str[j] == subDictList[i][j]) {
                ++j;
                if (j > maxMathLen) {
                    maxMathLen = j;
                }
            }
            // 若匹配
            if (j == len) {
                findDictStr = subDictList[i];
                return true;
            }
            // 匹配长度减小，后续不必再匹配
            if (j < maxMathLen) {
                return false;
            }
        }

        return false;
    }
};

int main() {
    Solution solution;

    string arr1[] = {"cat", "bat", "rat"};
    string sentence1 = "the cattle was rattled by the battery";
    vector<string> dictionary1(arr1, arr1 + sizeof(arr1) / sizeof(string));
    string res1 = solution.replaceWords(dictionary1, sentence1);
    cout << res1 << endl;

    string arr2[] = {"a", "b", "c"};
    string sentence2 = "aadsfasf absbs bbab cadsfafs";
    vector<string> dictionary2(arr2, arr2 + sizeof(arr2) / sizeof(string));
    string res2 = solution.replaceWords(dictionary2, sentence2);
    cout << res2 << endl;

    return 0;
}
