// 字符串加密

/*
输入：
1
password__a12345678_timeout_100
 */

/*
输出：
password_******_timeout_100
 */

/*
输入：
2
aaa_password_"a12_45678"_timeout__100_""_
输出：
aaa_password_******_timeout_100_""
 */

// 加密段 "******"
// 删除前后多余下划线
// 无索引返回 "ERROR"

// 本题为考试单行多行输入输出规范示例，无需提交，不计分。
#include <iostream>
#include <vector>
using namespace std;

string encodeStr(string& s, int index) {
    int len = s.length(), pos;

    // 暂存各命令行字符串
    vector<string> v;

    // 去掉前置下划线
    int i = 0;
    while (i < len && s[i] == '_') {
        ++i;
    }

    pos = i;
    while (i < len) {
        // 若为引号开头
        if (s[i] == '"') {
            ++i;
            while (i < len && s[i] != '"') {
                ++i;
            }
            string tmp = s.substr(pos, i - pos + 1);
            v.push_back(tmp);
        } else {
            while (i < len && s[i] != '_') {
                ++i;
            }
            string tmp = s.substr(pos, i - pos);
            v.push_back(tmp);
        }
        ++i;

        // 去掉多余下划线
        while (i < len && s[i] == '_') {
            ++i;
        }
        pos = i;
    }

    // 索引超出范围
    int vSize = v.size();
    if (index >= vSize) {
        return "ERROR";
    }

    // 加密替换
    v[index] = "******";

    string res = "";

    if (vSize == 1) {
        res = v[0];
    } else {
        res = v[0];
        for (int j = 1; j < vSize; ++j) {
            res += "_" + v[j];
        }
    }

    return res;
}

int main() {
    int index;
    string s;
    cin >> index;
    cin >> s;

    //    index = 1;
    //    s = "__password__a12345678_timeout_100__";
    //    index = 2;
    //    s = "aaa_password_\"a12_45678\"_timeout__100_\"\"_";

    string res = encodeStr(s, index);
    cout << res << endl;
}
