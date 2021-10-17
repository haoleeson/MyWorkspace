/** 题目描述：
 * 21. 合并两个有序链表
 * 将两个有序链表合并为一个新的有序链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。

示例：

输入：
[1,2,4]
[1,3,4]
输出：
[1, 1, 2, 3, 4, 4]

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190226
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Definition for singly-linked list
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

//默认链表从小到大排序
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        //特殊情况： 有一链表为空
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;
        //两链表都非空
        ListNode* head = (l1->val > l2->val) ? l2 : l1; //【第一次比较】记录头节点，返回用
        ListNode* Ptr = head; //用于操作返回链表的指针
        if (head == l1) {
            l1 = l1->next; //后移到下一【未使用节点】
        } else {
            l2 = l2->next; //后移到下一【未使用节点】
        }
        while (l1 != NULL && l2 != NULL) {
            // a. l2指向的值更小，将l2指向的当前这个节点夺取，插入到Ptr后方
            if (l1->val > l2->val) {
                Ptr->next = l2; //将l2当前节点插入Ptr
                l2 = l2->next; //l2 指针后移到下一【未使用节点】
                Ptr = Ptr->next; //Ptr 指针后移
            }
                // b. l1指向的值小于等于l2指向的值
            else {
                Ptr->next = l1; //将l1当前节点插入Ptr
                l1 = l1->next; //l1 指针后移到下一【未使用节点】
                Ptr = Ptr->next; //Ptr 指针后移
            }
        }
        // A. 若链表 l1 已排完，将 l2 尾部贴到 Ptr 尾部即可
        if (l1 == NULL) {
            Ptr->next = l2;
        }
            // B. 若链表 l2 已排完，将 l1 尾部贴到 Ptr 尾部即可
        else {
            Ptr->next = l1;
        }
        return head;
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

ListNode* stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode* dummyRoot = new ListNode(0);
    ListNode* ptr = dummyRoot;
    for(int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

string listNodeToString(ListNode* node) {
    if (node == nullptr) {
        return "[]";
    }

    string result;
    while (node) {
        result += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

int main() {
    string line;
    while (getline(cin, line)) {
        ListNode* l1 = stringToListNode(line);
        getline(cin, line);
        ListNode* l2 = stringToListNode(line);

        ListNode* ret = Solution().mergeTwoLists(l1, l2);

        string out = listNodeToString(ret);
        cout << out << endl;
    }
    return 0;
}
