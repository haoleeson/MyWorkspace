#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> v;
        stringSplit(v, path, DELIM[0]);
        int iterator = 0;

        // 精简路径
        vector<string> pathElems(v.size(), EMPTY_STR);
        for (vector<string>::iterator it = v.begin(); it != v.end(); ++it) {
            string& element = *it;

            if (element == DOT_STR || element == EMPTY_STR) {
                continue;
            } else if (element == DOUBLE_DOT_STR) {
                iterator = max(0, iterator - 1);
            } else {
                pathElems[iterator++] = element;
            }
        }

        if (iterator == 0) {
            return DELIM;
        }

        // 组装路径
        string res = EMPTY_STR;
        for (int i = 0; i < iterator; ++i) {
            res += DELIM + pathElems[i];
        }

        return res;
    }

private:
    const string DELIM = "/";
    const string EMPTY_STR = "";
    const string DOT_STR = ".";
    const string DOUBLE_DOT_STR = "..";
    inline void stringSplit(vector<string>& v, const string& str, char delim) {
        size_t previous = 0;
        size_t current = str.find(delim);

        while (current != string::npos) {
            if (current > previous) {
                v.push_back(str.substr(previous, current - previous));
            }
            previous = current + 1;
            current = str.find(delim, previous);
        }

        if (previous != str.size()) {
            v.push_back(str.substr(previous));
        }
    }
};

int main(void) {
    Solution solution;
    string path1 = solution.simplifyPath("/home/");
    cout << path1 << endl;
    string path2 = solution.simplifyPath("/../");
    cout << path2 << endl;
    string path3 = solution.simplifyPath("/home//foo/");
    cout << path3 << endl;
    string path4 = solution.simplifyPath("/a/./b/../../c/");
    cout << path4 << endl;

    return 0;
}
