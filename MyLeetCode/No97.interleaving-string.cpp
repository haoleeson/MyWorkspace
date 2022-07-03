#include <algorithm>
#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        int len1 = s1.length(), len2 = s2.length(), len3 = s3.length();
        if (len1 + len2 != len3) {
            return false;
        }

        // dpTab[i][j] 表示 s1[0:i] 与 s2[0:j] 能否交错构成 s3[0:i+j]
        vector<vector<bool>> dpTab = vector<vector<bool>>(len1 + 1, vector<bool>(len2 + 1, false));
        dpTab[0][0] = true;

        for (int i = 0; i <= len1; ++i) {
            for (int j = 0; j <= len2; ++j) {
                int k = i + j - 1;

                if (i > 0) {
                    dpTab[i][j] = dpTab[i][j] | (dpTab[i - 1][j] && s1[i - 1] == s3[k]);
                }
                if (j > 0) {
                    dpTab[i][j] = dpTab[i][j] | (dpTab[i][j - 1] && s2[j - 1] == s3[k]);
                }
            }
        }

        return dpTab[len1][len2];
    }
};

int main(void) {
    Solution solution;
    string sa1 = "aabcc";
    string sb1 = "dbbca";
    string sc1 = "aadbbcbcac";
    bool res1 = solution.isInterleave(sa1, sb1, sc1);
    cout << res1 << endl;

    string sa2 = "aabcc";
    string sb2 = "dbbca";
    string sc2 = "aadbbbaccc";
    bool res2 = solution.isInterleave(sa2, sb2, sc2);
    cout << res2 << endl;

    return 0;
}
