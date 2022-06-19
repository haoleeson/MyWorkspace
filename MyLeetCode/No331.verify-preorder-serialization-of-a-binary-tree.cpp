//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
#include<queue>
#include "myTools.h"
using namespace std;

class Solution {
public:
    bool isValidSerialization(string preorder) {
        queue<string> q = stringSplit(preorder, DIMMER[0]);
        bool ans = traverse(q, q.front() == NULLPTR_STR);
        return ans && q.empty();
    }

private:
    string DIMMER = ",";
    string NULLPTR_STR = "#";

    queue<string> stringSplit(const string& str, char delim) {
        size_t previous = 0;
        size_t current = str.find(delim);
        queue<string> q;

        while (current != string::npos) {
            if (current > previous) {
                q.push(str.substr(previous, current - previous));
            }
            previous = current + 1;
            current = str.find(delim, previous);
        }

        if (previous != str.size()) {
            q.push(str.substr(previous));
        }
        return q;
    }
    
    bool traverse(queue<string>& q, bool isFatherLeaf) {
        if (!isFatherLeaf && q.empty()) {
            return false;
        }

        string rootVal = q.front();
        q.pop();
        
        if (rootVal == NULLPTR_STR) {
            return true;
        } else if (isFatherLeaf) {
            return false;
        }

        return traverse(q, (rootVal == NULLPTR_STR)) && traverse(q, (rootVal == NULLPTR_STR));
    }
};

// 官方题解，维护（模拟剩余槽位的数量）计数器：空节点，消耗一个槽位；非空节点，消耗一个槽位再补充两个槽位。
class SolutionOfficial {
public:
    bool isValidSerialization(string preorder) {
        int n = preorder.length();
        int i = 0;

        // 模拟槽位
        int slots = 1;
        while (i < n) {
            // 槽位提前耗尽，返回false
            if (slots == 0) {
                return false;
            }

            if (preorder[i] == ',') {
                i++;
            } else if (preorder[i] == '#'){
                // 空节点，消耗一个槽位
                slots--;
                i++;
            } else {
                // 遍历完一个整数[0,100]
                while (i < n && preorder[i] != ',') {
                    i++;
                }
                slots++; // slots = slots - 1 + 2
            }
        }
        // 槽位恰好为空，则为前序遍历值
        return slots == 0;
    }
};

int main(void) {
    Solution solution;
    cout << solution.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#") << endl;
    cout << solution.isValidSerialization("1,#") << endl;
    cout << solution.isValidSerialization("9,#,#,1") << endl;

    return 0;
}
