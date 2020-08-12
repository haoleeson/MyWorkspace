#include <iostream>
#include <vector>
#include <map>
using namespace std;
/**
No.113 克隆图
给你无向连通图中一个节点的引用，请你返回该图的深拷贝（克隆）。

图中的每个节点都包含它的值 val（int） 和其邻居的列表（list[Node]）。

class Node {
public int val;
public List<Node> neighbors;
}

测试用例格式：

简单起见，每个节点的值都和它的索引相同。例如，第一个节点值为 1（val = 1），第二个节点值为 2（val = 2），以此类推。该图在测试用例中使用邻接列表表示。

邻接列表 是用于表示有限图的无序列表的集合。每个列表都描述了图中节点的邻居集。

给定节点将始终是图中的第一个节点（值为 1）。你必须将 给定节点的拷贝 作为对克隆图的引用返回。
*/

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }

    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }

    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    /**
     * 克隆图
     * @param node
     * @return
     */
    Node* cloneGraph(Node* node) {
        // 图是空的（不含任何节点），返回空
        if (node == NULL) {
            return NULL;
        }

        // 若已经创建过该节点，返回其地址
        map<int, Node*>::iterator hashtableIterator = m_nodeMap.find(node->val);
        if (hashtableIterator != m_nodeMap.end()) {
            return hashtableIterator->second;
        }

        // 若不存在该节点，则创建节点，返回其地址
        Node* newNode = new Node(node->val);
        m_nodeMap.insert(make_pair(node->val, newNode));

        // 填充其邻居地址
        for (int i=0; i < node->neighbors.size(); ++i) {
            Node* tmp = cloneGraph(node->neighbors[i]);
            newNode->neighbors.push_back(tmp);
        }
        return newNode;
    }

private:
    map<int, Node*> m_nodeMap;
};

int main() {
    Solution solutionl;

    Node* graphNode1 = new Node(1);
    Node* graphNode2 = new Node(2);
    Node* graphNode3 = new Node(3);

    graphNode1->neighbors.push_back(graphNode2);
    graphNode1->neighbors.push_back(graphNode3);

    Node* result = solutionl.cloneGraph(graphNode1);

    cout << "hello world!" << endl;

    return 0;
}
