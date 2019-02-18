/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：黎豪-软件工程-18101223769
 * */
#include "DenseMatrixGraph.h"

int main(int argc, const char * argv[]) {
    //定义一个稠密图实例
    DenseMatrixGraph *graph = new DenseMatrixGraph(5, true);//顶点数：16，有向图：true
    //添加边的信息
    graph->addEdge(0, 1, -1);
    graph->addEdge(0, 2, 3);
    graph->addEdge(1, 2, 3);
    graph->addEdge(1, 3, 2);
    graph->addEdge(1, 4, 2);
    graph->addEdge(3, 1, 1);
    graph->addEdge(3, 2, 5);
    graph->addEdge(4, 3, -3);

    graph->Dijkstra(0);
//    graph->showMatrixGraph(); //显示邻接矩阵
    return 0;
}
