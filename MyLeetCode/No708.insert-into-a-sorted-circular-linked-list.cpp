//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = nullptr;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};


class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        Node* node = new Node(insertVal);
        if (!head) {
            node->next = node;
            return node;
        }

        // find max element
        int maxVal = INT_MIN;
        Node *slow = head, *fast = head, *maxPtr = nullptr;
        do {
            if (slow->val >= maxVal) {
                maxVal = slow->val;
                maxPtr = slow;
            } else {
                break;
            }
            slow = slow->next;
            fast = fast->next->next;
        } while (slow != fast);

        // find insert ptr
        Node* insertPtr = maxPtr;
        while (maxVal > insertVal && insertPtr->next->val < insertVal) {
            insertPtr = insertPtr->next;
        }

        // insert node
        node->next = insertPtr->next;
        insertPtr->next = node;

        return head;
    }
};



int main(void) {
    Solution solution;

    Node* head = new Node(3);
    head->next = new Node(4);
    head->next->next = new Node(1);
    head->next->next->next = head;

    Node* res = solution.insert(head, 2);

    Node* head2 = nullptr;
    Node* res2 = solution.insert(head2, 1);

    Node* head3 = new Node(1);
    head3->next = head3;
    Node* res3 = solution.insert(head3, 0);

    return 0;
}