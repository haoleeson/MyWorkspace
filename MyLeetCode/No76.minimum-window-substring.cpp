//
// Created by eisenhao on 2022/6/16.
//

#include<iostream>
#include<unordered_map>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        int len_s = s.length();
        unordered_map<char, int> window, need;
        for (char ch: t) {
            need[ch]++;
        }

        int left = 0, right = 0;
        int valid = 0, len_need = need.size();
        int start = 0, len = INT_MAX;

        while (right < len_s) {
            char c = s[right];
            right++;
            if (need.count(c)) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;
                }
            }

            while (valid == len_need) {
                if ((right - left) < len) {
                    len = right - left;
                    start = left;
                }
                char d = s[left];
                left++;
                if (need.count(d)) {
                    if(window[d] == need[d]) {
                        valid--;
                    }
                    window[d]--;
                }
            }
        }

        return len == INT_MAX ? "" : s.substr(start, len);
    }
};


int main() {
    Solution solution;
    cout << "\"" << solution.minWindow("ADOBECODEBANC", "ABC") << "\"" <<  endl;
    cout << "\"" <<  solution.minWindow("a", "a") << "\"" <<  endl;
    cout << "\"" <<  solution.minWindow("a", "aa") << "\"" <<  endl;
    return 0;
}