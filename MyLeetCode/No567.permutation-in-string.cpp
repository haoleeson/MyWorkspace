//
// Created by eisenhao on 2022/6/16.
//

#include<iostream>
#include<unordered_map>
using namespace std;

class Solution {
public:
    bool checkInclusion(string t, string s) {
        int len_s = s.length(), len_t = t.length();
        unordered_map<char, int> window, need;
        for (char ch: t) {
            need[ch]++;
        }

        int left = 0, right = 0;
        int valid = 0, len_need = need.size();

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
                if (right - left == len_t) {
                    return true;
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

        return false;
    }
};


int main() {
    Solution solution;
    cout << solution.checkInclusion("ab", "eidbaooo") <<  endl;
    cout << solution.checkInclusion("ab", "eidboaoo") <<  endl;
    return 0;
}