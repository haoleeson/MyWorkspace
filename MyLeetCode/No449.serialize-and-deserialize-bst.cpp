//
// Created by eisenhao on 2022/6/18.
//

#include<iostream>
//#include<strstream>
#include<list>
#include "myTools.h"
using namespace std;

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {
            return NULLPTR_STR;
        }

        return to_string(root->val) + DIMMER + serialize(root->left) + DIMMER + serialize(root->right);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        list<string> l = stringSplit(data, DIMMER[0]);
        return buildTree(l);
    }

private:
    string DIMMER = ",";
    string NULLPTR_STR = "X";

     list<string> stringSplit(const string& str, char delim) {
        size_t previous = 0;
        size_t current = str.find(delim);
        list<string> l;

        while (current != string::npos) {
            if (current > previous) {
                l.push_back(str.substr(previous, current - previous));
            }
            previous = current + 1;
            current = str.find(delim, previous);
        }

        if (previous != str.size()) {
            l.push_back(str.substr(previous));
        }
        return l;
    }

    TreeNode* buildTree(list<string>& l) {
        string rootVal = l.front();
        l.pop_front();
        if (rootVal == NULLPTR_STR) {
            return nullptr;
        }

        TreeNode* node = new TreeNode(stoi(rootVal));
        node->left = buildTree(l);
        node->right = buildTree(l);

        return node;
    }
};

int main(void) {
    TreeNode* tree1 = new TreeNode(2);
    tree1->left = new TreeNode(1);
    tree1->right = new TreeNode(3);

    Codec codec1;
    string data1 = codec1.serialize(tree1);
    cout << data1.c_str() << endl;
    TreeNode* tree_1 = codec1.deserialize(data1);
    MyTools::printTree(tree_1);

    Codec codec2;
    string data2 = codec2.serialize(nullptr);
    cout << data2.c_str() << endl;
    TreeNode* tree_2 = codec2.deserialize(data2);
    MyTools::printTree(tree_2);


    return 0;
}
