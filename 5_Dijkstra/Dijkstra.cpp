/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#include "DenseMatrixGraph.h"

int main(int argc, const char * argv[]) {
    //定义一个稠密图实例
    DenseMatrixGraph *graph = new DenseMatrixGraph(16, false);//顶点数：16，有向图：false
    //添加边的信息
    graph->addEdge(0, 1, 5);
    graph->addEdge(0, 2, 3);
    graph->addEdge(1, 3, 1);
    graph->addEdge(1, 4, 3);
    graph->addEdge(1, 5, 6);
    graph->addEdge(2, 4, 8);
    graph->addEdge(2, 5, 7);
    graph->addEdge(2, 6, 6);
    graph->addEdge(3, 7, 6);
    graph->addEdge(3, 8, 8);
    graph->addEdge(4, 7, 3);
    graph->addEdge(4, 8, 5);
    graph->addEdge(5, 8, 3);
    graph->addEdge(5, 9, 3);
    graph->addEdge(6, 8, 8);
    graph->addEdge(6, 9, 4);
    graph->addEdge(7, 10, 2);
    graph->addEdge(7, 11, 2);
    graph->addEdge(8, 11, 1);
    graph->addEdge(8, 12, 2);
    graph->addEdge(9, 11, 3);
    graph->addEdge(9, 12, 3);
    graph->addEdge(10, 13, 3);
    graph->addEdge(10, 14, 5);
    graph->addEdge(11, 13, 5);
    graph->addEdge(11, 14, 2);
    graph->addEdge(12, 13, 6);
    graph->addEdge(12, 14, 6);
    graph->addEdge(13, 15, 4);
    graph->addEdge(14, 15, 3);

    int shorstedtDistance = graph->Dijkstra(0, 15);
//    graph->showMatrixGraph(); //显示邻接矩阵
    return 0;
}
