#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "myTools.h"

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        vector<vector<string>> res;

        for (string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());

            if (m.count(key) == 0) {
                vector<string> v(1, str);
                m[key] = v;
            } else {
                m[key].push_back(str);
            }
        }

        unordered_map<string, vector<string>>::iterator it = m.begin();
        while (it != m.end()) {
            res.push_back(it->second);
            ++it;
        }
        return res;
    }
};

int main(void) {
    Solution solution;
    string arr1[] = {"eat", "tea", "tan", "ate", "nat", "bat"};
    vector<string> strs1(arr1, arr1 + sizeof(arr1) / sizeof(string));
    vector<vector<string>> res1 = solution.groupAnagrams(strs1);
    MyTools::printVec2D(res1);

    vector<string> strs2;
    vector<vector<string>> res2 = solution.groupAnagrams(strs2);
    MyTools::printVec2D(res2);

    string arr3[] = {"a"};
    vector<string> strs3(arr3, arr3 + sizeof(arr3) / sizeof(string));
    vector<vector<string>> res3 = solution.groupAnagrams(strs3);
    MyTools::printVec2D(res3);

    return 0;
}
