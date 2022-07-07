// 字母统计加密

/*
输入：
xyxyXX
输出：
x:2;y:2;X:2;
 */

/*
输入：
abababb
输出：
b:4;a:3;
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct CharCntInfo {
    char ch;
    int cnt;
    CharCntInfo() {}
    CharCntInfo(char _ch, int _cnt) {
        ch = _ch;
        cnt = _cnt;
    }
};

bool cmpFunc(CharCntInfo a, CharCntInfo b) {
    if (a.cnt != b.cnt) {
        return a.cnt > b.cnt;
    }

    // 计数相同， 小写字母在前
    bool isASmallCh = (a.ch >= 'a' && a.ch <= 'z');
    bool isBSmallCh = (b.ch >= 'a' && b.ch <= 'z');

    // 若两者同为小写 或 大写
    if (!(isASmallCh ^ isBSmallCh)) {
        return a.ch < b.ch;
    }

    // 一个大写一个小写，小写在前
    return a.ch > b.ch;
}

string countCh(string& s) {
    int len = s.length();
    if (len == 0) {
        return ";";
    }

    // 记录各字符次数
    unordered_map<char, CharCntInfo> m;
    for (char ch : s) {
        if (m.count(ch) == 0) {
            CharCntInfo c(ch, 1);
            m[ch] = c;
        } else {
            m[ch].cnt++;
        }
    }

    vector<CharCntInfo> v;

    unordered_map<char, CharCntInfo>::iterator it;
    for (it = m.begin(); it != m.end(); ++it) {
        v.push_back(it->second);
    }

    sort(v.begin(), v.end(), cmpFunc);

    string res = "";
    int lenV = v.size();
    for (int i = 0; i < lenV; ++i) {
        string tmp = " :";
        tmp[0] = v[i].ch;
        res += tmp + to_string(v[i].cnt) + ";";
    }

    return res;
}

int main() {
    string s;
    cin >> s;

    //    s = "xyxyXX";
    //    s = "abababb";

    string res = countCh(s);
    cout << res << endl;
}
