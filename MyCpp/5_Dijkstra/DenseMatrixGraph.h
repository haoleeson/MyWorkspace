/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#ifndef _DENSEMATRIXGRAPH_H
#define _DENSEMATRIXGRAPH_H
#include <cassert>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

#define MAX_VAL 999

// 构建稠密图类，使用邻接矩阵法表示
class DenseMatrixGraph {
private:
    int n;                 // n为图的顶点数量
    int m;                 // m为边的数量
    bool directed;         // 是否为有向图
    vector<vector<int>> g; // 二维邻接矩阵，存储各边的权值<int>

public:
    // 构造函数
    DenseMatrixGraph(int n, bool directed);

    // 析构函数
    ~DenseMatrixGraph() {}

    // 返回图中的顶点数量
    int getV() { return this->n; }

    // 返回图中的边数量
    int getE() { return this->m; }

    // 判断节点 v 到节点 w 之间是否已经存在边
    bool hasEdge(int v, int w);

    // 添加边
    void addEdge(int v, int w, int value);

    // 显示节点路径
    void printPath(int v, int w, vector<int>& prePath);

    // 显示邻接矩阵
    void showMatrixGraph();

    /**
     * Dijkstra算法实现
     * 参数：起始节点 v， 终止节点 w
     * */
    int Dijkstra(int v, int w);
};

/**
 * 构造函数
 * @param n 图的顶点数
 * @param directed 是否为有向图
 */
DenseMatrixGraph::DenseMatrixGraph(int n, bool directed) : n(n), m(0), directed(directed) {
    // 初始化邻接矩阵的关系全部为无穷大，即各节点之间都不连接
    for (int i = 0; i < n; i++) {
        g.push_back(vector<int>(n, MAX_VAL));
    }

    // 节点自己到自己距离为 0
    for (int i = 0; i < n; i++) {
        g[i][i] = 0;
    }
}

/**
 * 判断两节点之间是否有边
 * @param v 节点 v
 * @param w 节点 w
 * @return
 */
bool DenseMatrixGraph::hasEdge(int v, int w) {
    // 断言，防止越界
    assert(v >= 0 && v < n && w >= 0 && w < n);

    return g[v][w] < MAX_VAL;
}

/**
 * 连接两节点，在两节点之间添加边
 * @param v 节点 v
 * @param w 节点 w
 * @param value 权重
 */
void DenseMatrixGraph::addEdge(int v, int w, int value) {
    // 断言，防止越界
    assert(v >= 0 && v < n && w >= 0 && w < n);

    // 若为有向图，只增加这一条边；若为无向图，对称增加权重
    if (directed) {
        g[v][w] = value;
    } else {
        g[v][w] = value;
        g[w][v] = value;
    }

    // 增加边的数量
    ++m;
}

/**
 * 显示邻接矩阵
 */
void DenseMatrixGraph::showMatrixGraph() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(6) << g[i][j];
        }
        cout << endl;
    }

    cout << endl;
}

/**
 * 显示最短途经路径
 * @param v 节点 v
 * @param w 节点 w
 * @param prePath 各节点的前置路径
 */
void DenseMatrixGraph::printPath(int v, int w, vector<int>& prePath) {
    cout << "The shortest path: " << endl;

    // 最短路径
    vector<int> shortestPath;
    // 填充目标节点
    shortestPath.push_back(w);

    // 逆序遍历前置路径 prePath，得到逆序最短路径
    for (int from = this->n - 1; prePath[from] != v; from = prePath[from]) {
        shortestPath.push_back(prePath[from]);
    }

    // 填充起始节点
    shortestPath.push_back(v);

    // 逆序输出，得到正向最短路径
    for (int i = shortestPath.size() - 1; i >= 0; i--) {
        cout << shortestPath[i];
        if (i != 0) {
            cout << " -> ";
        }
    }

    cout << endl;
}

/**
 * Dijkstra 算法实现，返回节点 v 到节点 w 的距离
 * @param v 起始节点 v
 * @param w 终止节点 w
 * @return -1 -- 不可达；dist -- 最短距离
 */
int DenseMatrixGraph::Dijkstra(int v, int w) {
    // 节点 v 到其他所有节点的距离
    vector<int> dist(this->n, MAX_VAL);
    dist[v] = 0; // 节点到自身的距离为0

    // 记录节点 v 到节点 w 的最短路径
    vector<int> prePath(this->n, -1);
    prePath[v] = v; // 起始节点的前驱节点为其自身

    // 每个结点都尝试做中间节点 k
    for (int k = 0; k < this->n; k++) {
        // 临时的目的节点(j)： 从 v 到 j： v->k、k->j
        for (int j = 0; j < this->n; j++) {
            // 若从 v -> k -> j 距离更短，则更新 v -> j 距离
            if (dist[k] != MAX_VAL && g[k][j] != MAX_VAL && (dist[j] > dist[k] + g[k][j])) {
                dist[j] = dist[k] + g[k][j];
                // 记录前驱节点 k
                prePath[j] = k;
            }
        }
    }

    // 打印途径的节点路径
    printPath(v, w, prePath);

    return dist[w];
}

#endif
