//
// Created by EisenHao on 2020/9/16.
//

#ifndef __MYTOOLS_H_
#define __MYTOOLS_H_
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class MyTools {
public:
    // 去除字符串前后空格
    static void trim(std::string& str);

    // 构造链表
    template<typename T>
    static ListNode* genList(std::vector<T>& vec);

    // 释放链表
    static void delList(ListNode* head);

    // 打印链表
    static void printList(ListNode* head);

    // 打印二叉树
    static void printTree(TreeNode* root);

    // 打印数组
    template<typename T>
    static void printVec(std::vector<T>& vec);
    template<typename T>
    static void printVec2D(std::vector<std::vector<T>>& vec2D);

    // 二叉树的 前序遍历 (根 左 右) (迭代)
    static std::vector<int> preorderTraversal(TreeNode* root);

    // 二叉树的 中序遍历 (左 根 右) (迭代)
    static std::vector<int> inorderTraversal(TreeNode* root);

    // 二叉树的 后序遍历 (左 右 根)（迭代）
    static std::vector<int> postorderTraversal(TreeNode* root);
};

void MyTools::trim(std::string& str) {
    if (!str.empty()) {
        str.erase(0, str.find_first_not_of(' '));
        str.erase(str.find_last_not_of(' ') + 1);
    }
}

template<typename T>
ListNode* MyTools::genList(std::vector<T>& vec) {
    int size = vec.size(), i = 0;
    if (size == 0) {
        return nullptr;
    }
    ListNode* head = new ListNode(vec[i++]);
    ListNode* curNode = head;
    while (i < size) {
        curNode->next = new ListNode(vec[i++]);
        curNode = curNode->next;
    }
    return head;
}

void MyTools::delList(ListNode* head) {
    ListNode* nextNode;
    while (head) {
        nextNode = head->next;
        head->next = nullptr;
        delete head;
        head = nextNode;
    }
}

void MyTools::printList(ListNode* head) {
    if (head) {
        ListNode* ptr = head;
        while (ptr->next != nullptr) {
            std::cout << ptr->val << "->";
            ptr = ptr->next;
        }
        std::cout << ptr->val;
    }
    std::cout << std::endl;
}

void MyTools::printTree(TreeNode* root) {
    std::queue<TreeNode*> que;
    TreeNode* ptr;
    que.push(root);
    std::cout << "[";
    while (!que.empty()) {
        ptr = que.front();// 先读取队列的首元素
        que.pop();// 弹出队列的首元素
        if (ptr != nullptr) {
            // 若子节点均为空，则不必入队列
            if (ptr->left != nullptr || ptr->right != nullptr) {
                que.push(ptr->left);
                que.push(ptr->right);
            }
            if (!que.empty()) {
                std::cout << ptr->val << ", ";
            } else {
                std::cout << ptr->val;
            }
        } else {
            if (!que.empty()) {
                std::cout << "null, ";
            } else {
                std::cout << "null";
            }
        }
    }
    std::cout << "]" << std::endl;
}

template<typename T>
void MyTools::printVec(std::vector<T>& vec) {
    int size = vec.size();
    std::cout << "[";
    if (size > 0) {
        std::cout << vec[0];
        for (int i = 1; i < size; ++i) {
            std::cout << ", " << vec[i];
        }
    }
    std::cout << "]" << std::endl;
}

template<typename T>
void MyTools::printVec2D(std::vector<std::vector<T>>& vec2D) {
    int size = vec2D.size(), size2;
    std::cout << "[" << std::endl;
    if (size > 0) {
        size2 = vec2D[0].size();
        std::cout << "  [";
        if (size2 > 0) {
            std::cout << vec2D[0][0];
            for (int j = 1; j < size2; ++j) {
                std::cout << "\t," << vec2D[0][j];
            }
        }
        std::cout << "]";

        for (int i = 1; i < size; ++i) {
            size2 = vec2D[i].size();
            std::cout << "," << std::endl << "  [";
            if (size2 > 0) {
                std::cout << vec2D[i][0];
                for (int j = 1; j < size2; ++j) {
                    std::cout << "\t," << vec2D[i][j];
                }
            }
            std::cout << "]";
        }
    }
    std::cout << std::endl << "]" << std::endl;
}

std::vector<int> MyTools::preorderTraversal(TreeNode* root) {
    std::vector<int> ans;
    std::stack<TreeNode* > s;
    while (root != nullptr || !s.empty()) {
        if (root != nullptr) {
            // 输出 根
            ans.push_back(root->val);
            // 栈存 右
            if (root->right) {
                s.push(root->right);
            }
            // 遍历 左
            root = root->left;
        } else {
            root = s.top();
            s.pop();
        }
    }
    return ans;
}

std::vector<int> MyTools::inorderTraversal(TreeNode* root) {
    std::vector<int> ans;
    std::stack<TreeNode*> s;
    while (root != nullptr || !s.empty()) {
        // 先遍历左节点，根节点入栈
        while (root != nullptr) {
            // 栈存 根
            s.push(root);
            // 遍历 左
            root = root->left;
        }
        root = s.top();
        s.pop();
        // 输出根
        ans.push_back(root->val);
        // 遍历 右
        root = root->right;
    }
    return ans;
}

std::vector<int> MyTools::postorderTraversal(TreeNode* root) {
    std::vector<int> ans;
    std::stack<TreeNode*> s;
    while (root != nullptr || !s.empty()) {
        if (root != nullptr) {
            // 头插 根
            ans.insert(ans.begin(), root->val);
            // 栈存 左
            if (root->left) {
                s.push(root->left);
            }
            // 遍历 右
            root = root->right;
        } else {
            root = s.top();
            s.pop();
        }
    }
    return ans;
}

#endif //__MYTOOLS_H_
