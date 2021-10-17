/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#ifndef _DENSEMATRIXGRAPH_H
#define _DENSEMATRIXGRAPH_H
#include <cassert>
#include <iostream>
#include <vector>
#include <iomanip>

#define WuQiongDa 999
using namespace std;

class DenseMatrixGraph{//构建稠密图类，使用邻接矩阵法表示
private:
    int n;//n为图的顶点数量
    int m;//m为边的数量
    bool directed;//是否为有向图
    /**
     * 构建二维邻接矩阵g，其存储各边的权值<int>, 默认值为无穷大WuQiongDa，即两节点无边
     * */
    vector<vector<int>> g;
public:
    /**构造函数
     * 定义图的顶点数，生成并初始化(顶点数 x 顶点数)规模的二维邻接矩阵g
     * 此时没插入边的信息，所有边的权值均为：（默认值）无穷大WuQiongDa
     * 传入参数：*/
    DenseMatrixGraph(int n, bool directed){
        this->n = n;//顶点数
        this->directed = directed;
        this->m = 0; //边数为0
        //初始化邻接矩阵的关系全部为WuQiongDa，即各节点之间都不连接
        for(int i=0; i<n; i++){
            g.push_back(vector<int>(n, WuQiongDa));
        }
        //节点自己到自己为0
        for(int i=0; i<n; i++){
            g[i][i] = 0;
        }
    }

    //析构函数
    ~DenseMatrixGraph(){
    }

    //返回图中的顶点数量
    int getV(){
        return this->n;
    }
    //返回图中的边数量
    int getE(){
        return this->m;
    }

    //判断节点v到节点w之间是否已经存在边
    bool hasEdge(int v, int w){
        bool result = false;
        assert(v>=0 && v<n);//防止越界
        assert(w>=0 && w<n);
        if(g[v][w] < WuQiongDa){
            result = true;//有边
        }
        return result;
    }

    /**在v节点和w节点之间建立连接关系(边)
     * 参数：节点v, 节点w, 两节点之间的权值
     * */
    void addEdge(int v, int w, int value){
        assert(v>=0 && v<n);
        assert(w>=0 && w<n);//防止数组越界访问
        g[v][w]= value;
        m++;//增加边的数量
        //如果为有向图，只增加这一条边
        if(directed){
            return;
        }
        //如果为无向图,则邻接图成对称关系，w节点到v节点之间也一定是存在连接的
        else{
            g[w][v]= value;
        }
    }

    //显示邻接矩阵
    void showMatrixGraph(){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cout <<setw(6)<< g[i][j];
            }
            cout << endl;
        }
    }

    /**
     * Dijkstra算法实现
     * 参数：起始节点 v， 终止节点 w
     * */
    int Dijkstra(int v, int w){
        /** 构建并初始化一维矩阵dist距离
         * 表示：起始节点v 到其他所有节点的距离
         * */
        vector<int> dist;
        for(int i=0; i<this->n; i++){
            dist.push_back(WuQiongDa);
        }
        dist[v] = 0;//节点到自身的距离为0
        //构建存储中间前驱节点变量的一维
        vector<int> path;
        for(int i=0; i<this->n; i++){
            path.push_back(-1);
        }
        path[v] = v;// 起始节点的前驱节点为其自身

        //每个结点都尝试做中间节点 k
        for(int k=0; k<this->n; k++){
            //临时的目的节点(j)： 从v到j： v->k、k->j
            for(int j=0; j<this->n; j++){
                if(dist[k]!=WuQiongDa && g[k][j]!=WuQiongDa && (dist[j] > dist[k]+g[k][j])){
                    dist[j] = dist[k]+g[k][j];//更新 v到j 距离
                    path[j] = k;// 记录前驱节点 k
                }
            }
        }
        //输出起始节点 v 到所有节点的 最短距离
//        cout << "dist = " << endl;
//        for(int i=0; i<this->n; i++){
//            cout << setw(6) << " 0->"<< i << "=" << dist[i];
//        }
//        cout << endl;
        //输出最短距离下每个节点的前驱节点
//        for(int i=0; i<this->n; i++){
//            cout << setw(6) << "Pre" << i << "=" << path[i];
//        }
//        cout << endl;
        cout << "The shortest path Length of ("<< v << "->" << w << ") = " << dist[w] << endl;
        cout << "Path: ";
        int from = this->n -1;
        vector<int> OutPath;
        OutPath.push_back(w);
        while(path[from]!=v){
            OutPath.push_back(path[from]);
            from = path[from];
        }
        OutPath.push_back(v);
        for(int i=OutPath.size()-1; i>=0; i--){
            cout << OutPath[i];
            if(i!=0){
                cout << " -> ";
            }
        }
        return dist[w];
    }
};

#endif
