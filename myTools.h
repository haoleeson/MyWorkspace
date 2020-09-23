//
// Created by EisenHao on 2020/9/16.
//

#ifndef __MYTOOLS_H_
#define __MYTOOLS_H_
#include <iostream>
#include <vector>
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
    /**
     * 打印链表
     */
    static void printList(ListNode* head) {
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

    /**
     * 打印二叉树
     */
    static void printTree(TreeNode* root) {
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

    /**
     * 打印数组
     */
    template<typename T>
    static void printVec(std::vector<T>& vec) {
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
    static void printVec2D(std::vector<std::vector<T>>& vec2D) {
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
};

#endif //__MYTOOLS_H_
