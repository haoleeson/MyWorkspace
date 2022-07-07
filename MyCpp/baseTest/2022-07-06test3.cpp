// 树型父子目录，删除指定目录（及其子目录），剩余目录集合

/*
输入：
5
8 6
10 8
6 0
20 8
2 6
8
输出：
2 6
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    int n, curNode, fatherNode, delNodeID;
    cin >> n;

    // 记录 当前目录 和其 父目录 的映射关系
    unordered_map<int, int> child2Father;
    // 记录 父目录下 的 所有子目录 信息
    unordered_map<int, unordered_set<int>> father2Childs;
    // 所有目录
    unordered_set<int> allNode;

    for (int i = 0; i < n; ++i) {
        cin >> curNode >> fatherNode;

        // 记录所有目录
        allNode.insert(curNode);
        allNode.insert(fatherNode);

        // 添加 子目录与父目录映射
        child2Father[curNode] = fatherNode;

        // 添加当前目录的子目录信息（即其自己）
        unordered_set<int> s;
        s.insert(curNode);
        father2Childs[curNode] = s;

        // 添加父目录的子目录映射
        if (fatherNode != 0 && !father2Childs.count(fatherNode)) {
            unordered_set<int> s;
            s.insert(fatherNode);
            father2Childs[fatherNode] = s;
        }

        // 逐层向上维护中间父目录的所有子目录（包括其自身）
        int fa = fatherNode;
        while (fa != 0 && father2Childs.count(fa)) {
            father2Childs[fa].insert(curNode);
            if (!child2Father.count(fa)) {
                break;
            }
            // 跳到其父目录
            fa = child2Father[fa];
        }
    }

    cin >> delNodeID;

    // 删除根目录，所有目录均删除
    if (delNodeID == 0) {
        //        cout << endl;
        return 0;
    }

    // 要删除目录
    unordered_set<int> delNodeSets = father2Childs[delNodeID];

    vector<int> res;

    // 遍历所有目录，删除指定目录集合，和根目录 0
    unordered_set<int>::iterator it;
    for (it = allNode.begin(); it != allNode.end(); ++it) {
        int node = *it;
        if (node == 0 || delNodeSets.count(node)) {
            continue;
        }
        res.push_back(node);
    }

    int lenRes = res.size();
    if (lenRes == 0) {
        //        cout << endl;
        return 0;
    }

    sort(res.begin(), res.end());
    if (lenRes == 1) {
        cout << res[0] << endl;
    } else {
        cout << res[0];
        for (int i = 1; i < lenRes; ++i) {
            cout << " " << res[i];
        }
        cout << endl;
    }
}
