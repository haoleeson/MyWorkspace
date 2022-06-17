#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int v) : val(v), next(nullptr) {}
};

void proderPrint(ListNode* head) {
    if (head == nullptr) {
        return;
    }

    proderPrint(head->next);
    cout << " " << head->val;
}

int main(void) {
    ListNode* head = new ListNode(1);
    head->next = new ListNode(2);
    head->next->next = new ListNode(3);
    head->next->next->next = new ListNode(4);

    proderPrint(head);
}