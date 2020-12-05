layout: post
title: 算法分析与设计练习
date: 2019/01/03 21:05:44
updated: 2019/3/17 20:36:45
comments: true
tags:
- 算法
categories:
- 算法

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/AnalysisOfAlgorithmsLesson.jpg" class="full-image" />
# 算法分析与设计练习
完整源代码已在本文尾部给出
## No1. 优先级队列（大小顶堆）
堆是一种经过排序的完全二叉树，其中任一非终端节点的数据值均不大于（或不小于）其左子节点和右子节点的值。最小(大)堆能保证堆顶元素最小(大)，相比于用数组存放数据，如果要查找所有数据中最小(大)的数据时，数组的时间复杂度为O(n)，而最小(大)堆的时间复杂度为O(1)。而数据增删数据时，需要保证最小(大)堆的动态可维护性仅需O(logN)。因此对于特定的需求环境，最小(大)堆这种数据结构非常高效。
<!-- more -->
### 最大堆概念
最大堆，是一种经过排序的完全二叉树，其中任一非终端节点的数据值均不小于其左子节点和右子节点的值。
#### 最大堆实现思路
将最大堆二叉树存储到数组内，非根节点元素的父节点下标为(i-1)/2，若子节点存在则下标为2*i+1。
**插入操作**：每当插入一个元素，将元素插入到容器（数组）尾部，然后执行迭代的上升操作，将插入的元素与其父节点比较，若比父节点大则交换，然后再与交换后节点的父节点相互比较交换，直到放置到合适位置。（最坏递归到根节点终止迭代）
**弹出操作**：弹出最大值（即数组首地址元素a[0]）。先交换交换堆顶与堆末，再弹出堆末（最大值），然后再将现堆顶元素执行迭代的下降操作，若其子节点存在与其子节点比较，若比子节点小则交换，然后再与交换后的子节点相互比较交换，直到放置在合适位置。（最坏递归到叶子节点）
**最大堆运行结果**
![1_Max_Heap](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/AnalysisOfAlgorithmsLesson_Max_Heap.png)

### 最小堆概念

最小堆，是一种经过排序的完全二叉树，其中任一非终端节点的数据值均不大于其左子节点和右子节点的值。堆内的所有数据中最小的元素始终在堆顶，而增删一个元素而动态维护最小堆性质的时间复杂度仅为O(logN)
#### 最小堆实现思路
将最小堆二叉树存储到数组内，非根节点元素的父节点下标为(i-1)/2，若子节点存在则下标为2*i+1。

**插入操作**：每当插入一个元素，将元素插入到容器（数组）尾部，然后执行迭代的上升操作，将插入的元素与其父节点比较，若比父节点小则交换，然后再与交换后节点的父节点相互比较交换，直到放置到合适位置。（最坏递归到根节点终止迭代）

**弹出操作**：弹出最小值（即数组首地址元素a[0]）。先交换交换堆顶与堆末，再弹出堆末（最小值），然后再将现堆顶元素执行迭代的下降操作，若其子节点存在与其子节点比较，若比子节点小则交换，然后再与交换后的子节点相互比较交换，直到放置在合适位置。（最坏递归到叶子节点）


最小堆运行结果
![1_Min_Heap](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/AnalysisOfAlgorithmsLesson_Min_Heap.png)


## No2. Quicksort
快速排序（Quick Sort）由C. A. R. Hoare在1962年提出。它的基本思想是：通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
快速排序是不稳定的算法，时间复杂度在最坏情况下是O(N^2)，平均的时间复杂度是O(N*lgN)。

### Quick Sort 实现思想
快速排序算法是一种基于交换的高效的排序算法，它采用了分治法的思想：
* 1、从数列中取出一个数作为基准数（枢轴，pivot）。 
* 2、将数组进行划分(partition)，将比基准数大的元素都移至枢轴右边，将小于等于基准数的元素都移至枢轴左边。
* 3、再对左右的子区间重复第二步的划分操作，直至每个子区间只有Cutoff（阈值）个元素。
* 4、对Cutoff（阈值）个元素进行插入排序（实践经验小于一定数量后插入排序快于快速排序），然后返回上一调用堆栈。

### 实现Quicksort核心代码

```c++
//快速排序算法实现
#define Cutoff 5 //定义快速排序（递归）阈值，数组元素小于Cutoff直接插入排序

void Quicksort( vector<ElementType> &A, long int Left, long int Right ) {
    ElementType pivot;
    long int i, j;
    //是否进行快速排序，阈值判断
    if ( (Right - Left) >= Cutoff ) {
        //选主元pivot，藏于A[Right-1]
        pivot = Median3 ( A, Left, Right );//让这段元素的左、中、右三个有序，并且将中间与这段元素的最右边-1个元素互换，然后返回这段元素的最右边元素-1的下标
        i = Left ;
        j = Right - 1 ;
        //子集划分(pivot左边全小于pivot；pivot右边全大于pivot)
        for ( ; ; ) {
            while ( A[++i] < pivot ) {} //找到A[i] > pivot, 跳出
            while ( A[--j] > pivot ) {} //找到A[j] < pivot, 跳出
            if ( i < j ) {
                //说明A[i]与A[j]之间还有其他元素，可交换
                Swap( &A[i], &A[j] );
            } else {
                break;
            }
        }
        Swap( &A[i], &A[Right-1] ); //将pivot 放到中间，即i下标处
        Quicksort( A, Left, i-1 );//递归处理左边
        Quicksort( A, i+1, Right );//递归处理右边
    } else {
        //低于阈值，直接调用插入排序
        //递归到最小一层用插入排序(每段的插入排序地址为：&A + Left (即：绝对地址A 加相对地址Left)
        //最小一层插入排序元素个数Number = Right-Left+1
        Insertion_Sort (  &A[Left], Right-Left+1 );
    }
}
//快速排序（统一接口，加壳）
void Quick_Sort ( vector<ElementType> &A, long int Number ) {
    Quicksort ( A, 0, Number-1 );
}
```
### Quick Sort 运行结果
![2_QuickSort](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/AnalysisOfAlgorithmsLesson_QuickSort.png)

### 延伸思考🤔:
#### (1)Quick sort会在n个具有相同的值的元素列表中进行多少次比较？
答：N(lgN-1)-lgN次比较。
归纳得：子数组长度大于1时，每层的对比次数是上一层元素个数-上一层子数组个数。由于子数组长度大于1时才有比较，所以有比较的层次数是 1(顶层)+lgN-1(底层)=lgN。顶层有对比，但未减少元素。底层没有对比。倒数第二层的减少元素数与倒数第三层相关，那么有减少元素个数的层数有lgN-1(底层)-1(倒数第二层)=lgN-2。归纳总结后：总的对比次数=N*对比层数 - 各层的元素减少数之和 = N*lgN - 各层的元素减少数之和。而第n层的减少元素个数 = 2^n-1，各层的减少元素个数和累加为 = N-lgN。故总的比较次数为：N(lgN-1)-lgN

#### (2)Quick sort在n个元素列表上进行的最大和最小比较次数是多少，分别给出最大和最小情况的实例。
答：假设被排序的数列中有N个数。遍历一次的时间复杂度是O(N)，需要遍历多少次呢？
最多需要遍历N次，至少需要遍历lg(N+1)次。
* (1).为什么最少是lg(N+1)次？
快速排序是采用的分治法进行遍历的，我们将它看作一棵二叉树，它需要遍历的次数就是二叉树的深度，而根据完全二叉树的定义，它的深度至少是lg(N+1)。因此，快速排序的遍历次数最少是lg(N+1)次。
* (2).为什么最多是N次？
将快速排序看作一棵二叉树，它的深度最大是N。因此，快读排序的遍历次数最多是N次。

## No3．**Matrix-chain product**. The following are some instances
* a)<3, 5, 2, 1,10>  答：55， 计算次序为：2，1，3
* b)<2, 7, 3, 6, 10> 答：198， 计算次序为：1，2，3
* c)<10, 3, 15, 12, 7, 2>答：678， 计算次序为：4，2，3，1
* d)<7, 2, 4, 15, 20, 5>答：990，计算次序为：2，3，4，1

用备忘录解决：

```c++
#include <iostream>
#include <vector>
using namespace std;

//宏定义
#define length 5 //矩阵元素个数
#define numOfMatrix length-1 //矩阵个数 = length - 1

//全局变量
//定义规模为：矩阵链的个数^2 的二维数组,并赋初值无穷大WuQiongDa
vector<vector<int>> m(numOfMatrix); //numOfMatrix 矩阵个数 = length - 1

/**
 * 计算第i到j段的最小计算次数
 * 返回值<int>：第i到j段的最小运算次数
* */
#define WuQiongDa 69999999
int LookUp_Chain(int p[], int i, int j)
{
    //备忘录：若已计算，则返回已计算值
    if (m[i-1][j-1] != WuQiongDa){
        return m[i-1][j-1];
    }
    //若没计算
    //a.过小只有两个矩阵
    if(j == i+1){
        return p[i-1] * p[i] * p[j];
    }
    //b.有可分性
    else {
        //计算从 k 处划分(k取值：i到j-1)，后的两边的值 + 两边相乘的值
        for (int k=i; k<=j-1; k++) {
            //中间值q
            int q = LookUp_Chain(p, i, k) + LookUp_Chain(p, k+1, j)
                    + p[i-1] * p[k] * p[j];
            //记录从k处划分的m[i][j]最小值
            if(q < m[i-1][j-1]){
                cout << "k = " <<  k << endl;
                m[i-1][j-1] = q;
            }
        }
        return m[i-1][j-1];
    }
}


/* *
 * 备忘录，矩阵链最小计算次数
 * 传入参数：矩阵链容器，存储顺序的矩阵相乘下标
 * 如：<3, 5, 2, 1, 10> 即为：(3, 5) x (5, 2) x (2, 1) x (1, 10)
 * */
int Memory_Matrix_Chain(int p[])
{
    int result = 0;
    for(int i=0; i<numOfMatrix; i++)
    {
        for(int j=0; j<numOfMatrix; j++)
        {
            if(i == j){
                m[i].push_back(0);
            }else{
                m[i].push_back(WuQiongDa);
            }
        }
    }
    result = LookUp_Chain(p, 1, numOfMatrix);//下标
    return result;
}

int main(void)
{
    int a[5] = {3, 5, 2, 1, 10};//答：55, 计算次序为：2，1，3
    int b[5] = {2, 7, 3, 6, 10};//答：198， 计算次序为：1，2，3
    int c[6] = {10, 3, 15, 12, 7, 2};//答：654038
    int d[6] = {7, 2, 4, 15, 20, 5};
    int result = Memory_Matrix_Chain(a);
    cout << "Min Calc times = " << result << endl;
    return 0;
}

```

## No4．**最长公共子序列**（LCS）
实例输入：
* a)X: xzyzzyx   Y: zxyyzxz
* b)X:MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCALLAAQANKESSSESFISRLLAIVAD               
Y:MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCTLLAAQANKENSNESFISRLLAIVAG

### 求解思路
因为，我们需要找到X 和 Y中最长的那个公共子序列。而要找X 和 Y的LCS，首先考虑X的最后一个元素和Y的最后一个元素。最长公共子序列的递归式如下：
![最长公共子序列的递归式](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/AnalysisOfAlgorithmsLesson_LCS_Formula.png)

### C++编程实现LCS
```c++
#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int MaxNum(int firstNum, int secondNum){
    return firstNum > secondNum ? firstNum : secondNum;
}

//定义数组结构体
struct matrix{
    int num;
    int direct;
};

typedef matrix Matrix;

int LCS(char *strA, char *strB, int lengthA, int lengthB, Matrix *resultMatrix[]){
    //若i = 0 或 j = 0， 返回 0
    if (lengthA == 0 || lengthB == 0) {
        return 0;
    }
    //初始化存储数组
    for (int i = 0; i <= lengthA; i++) {
        for (int j = 0; j <= lengthB; j++) {
            resultMatrix[i][j].num = 0; //设置所有默认的最长为0
            resultMatrix[i][j].direct = 1; //所有默认方向变成上 0斜上，1上，-1左
        }
    }
    for(int j=0; j<=lengthB; j++){
        resultMatrix[0][j].direct = -1;
    }
    for (int i = 0; i < lengthA; i++) {
        for (int j = 0; j < lengthB; j++) {
            //若字符串A，字符串B 末尾元素相同
            if (strA[i] == strB[j]) {
                resultMatrix[i+1][j+1].num = resultMatrix[i][j].num + 1;
                resultMatrix[i+1][j+1].direct = 0;
            }
            //否则，分别计算子问题求最大
            else{
                resultMatrix[i+1][j+1].num = MaxNum(resultMatrix[i+1][j].num, resultMatrix[i][j+1].num);
                resultMatrix[i+1][j+1].direct = resultMatrix[i+1][j].num > resultMatrix[i][j+1].num ? (-1) : 1;
            }
        }
    }
    return resultMatrix[lengthA][lengthB].num;
}

int main(int argc, const char * argv[]) {
    char strA[] = {"xzyzzyx"};
    char strB[] = {"zxyyzxz"};
    int lengthA = (int)strlen(strA);
    int lengthB = (int)strlen(strB);
    Matrix *resultMatrix[lengthA+1];
    for (int i = 0; i <= lengthA; i++) {
        resultMatrix[i] = (Matrix*)malloc(sizeof(struct matrix)* (lengthB+1));
    }
    int max = LCS(strA, strB, lengthA, lengthB, resultMatrix);
    cout << "max = " << max << endl;
    vector<char> result_LCS;
    //便利二维数组，求解最长公共子序列
    //所有默认方向变成上 0斜上，1上，-1左
    int i=lengthA, j=lengthB;
    while(true){
        int k = resultMatrix[i][j].direct;
        switch (k){
            case 0:
                result_LCS.push_back(strA[i-1]);
                i--;
                j--;
                break;
            case -1:
                j--;
                break;
            case 1:
                i--;
                break;
            default:
                cout << "something Error!!!" << endl;
                break;
        }
        if(i==0 || j==0) break;
    }
    //输出结果
    for(int i=result_LCS.size()-1; i>=0; i--){
        cout <<result_LCS[i];
    }
    return 0;
}
```
### 程序运行结果：
* a)X: xzyzzyx   Y: zxyyzxz
```c++
max = 4
xyzz
```
* b)X:MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCALLAAQANKESSSESFISRLLAIVAD               
Y:MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCTLLAAQANKENSNESFISRLLAIVAG
```c++
max = 56
MAEEEVAKLEKHLMLLRQEYVKLQKKLAETEKRCLLAAQANKESESFISRLLAIVA
```

## No5. 多级图中的最短路径
**多级图是图(1)G=(V,E),其中V被划分为K>=2个不相交的子集,使得如果(a,b)在E中,则a在Vi中,并且b在Vi+1对于分区中的某些子集中;和(2)|V1|=|Vk|=1.**
![Shortest_path_in_multistage_graphs](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/AnalysisOfAlgorithmsLesson_SPIMG.png)
### 求解思路
Dijkstra算法。以起始点为中心向外层层扩展，直到扩展到终点为止。
### Dijkstra算法实现：
```c++
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
```
### 运行结果：
```c++
The shortest path Length of (0->15) = 18
Path: 0 -> 1 -> 4 -> 7 -> 11 -> 14 -> 15
```

## No6. 简单的**调度问题**
我们给出了作业j1，j2 ... jn，它们分别具有已知的运行时间t1，t2 ... tn。 我们有一个处理器。安排这些工作以最小化平均完成时间的最佳方法是什么。假设它是非抢先式调度：一旦作业启动，它必须运行完成。 以下是一些实例：

a)(j1, j2, j3, j4) : (15，8，3，10)

### 解题思路
将工作时长做为贪心算法的参数，贪工作时长最小的工作，时长越短，安排越前。

### 简单贪心实现
```c++
#include <iostream>
#include <vector>
using namespace std;
//用贪心求工作时序安排
void schedulGreedy(int jobs[], int num){
    vector<int> jobSchedule(num, 0);
    for(int i=0; i<num; i++){
        jobSchedule[i] = i+1;
    }
    for(int i=0; i<num-1; i++){
        for(int j=i; j<num; j++){
            if(jobs[i] > jobs[j]){
                int temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
                temp = jobSchedule[i];
                jobSchedule[i] = jobSchedule[j];
                jobSchedule[j] = temp;
            }
        }
    }
    cout << "job schedule is:" << endl;
    for(int i=0; i<num; i++){
        cout << "j" << jobSchedule[i];
        if(i!=num-1){
            cout << " -> ";
        }
    }
}
int main(void) {
    int jobs[4] = {15, 8, 3, 10};
    schedulGreedy(jobs, 4);
    return 0;
}
```
### 运行结果为：
```c++
job schedule is:
j3 -> j2 -> j4 -> j1
```

## No7. 单源最短路径
以下是邻接矩阵，顶点A是源。
	A	B	C	D	E
A		-1   3
B			3    2    2
C       
D		1   5
E				-3

### 分析
手动绘制单向图如下所示：
![single source graph](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/AnalysisOfAlgorithmsLesson_single_source_graph.jpg)
由图可知，图中节点A只有出度，节点C只有入度，其他不得而知，且题目给的较为模糊，不知是(1)求解从节点A->节点C的最短路径，或是（2）求解从节点A出发到任意节点中路径最短的一条。姑且按（2）求解
### 解题思路：
与求解第5题类似，参数是否为有向图为:true，仍采用Dijkstra算法。以起始点为中心向外层层扩展，直到扩展到终点为止，可以得到从起始节点到所有节点的最短距离。

### 核心代码
代码与第五题代码部分有所区别。
```c++
/**
 * Dijkstra算法实现
 * 参数：起始节点 v
 * */
void Dijkstra(int v){
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

    //输出起始节点到所有节点的距离，顺便找出最短的距离
    int recordTheShortestPath;
    int temp = WuQiongDa;
    for(int i=1; i<this->n; i++){
        cout << "[dist] A->" << (char)(i+'A') << " = " << setw(2) << dist[i] << ";  ";
        showPathFrom0To(i, path);
        if(dist[i] < temp){
            temp = dist[i];
            recordTheShortestPath = i;
        }
    }
    //显示从起始节点出发到各节点的最短路径
    cout << "The shortest Path is [dist] A->" << (char)(recordTheShortestPath+'A') << " = " << setw(2) << dist[recordTheShortestPath] << ";  ";
    showPathFrom0To(recordTheShortestPath, path);

}

//显示从起始节点0， 到第w个节点的路径（通过传入的前驱节点path数组显示）
void showPathFrom0To(int w, vector<int>& path){
    cout << "Path from (A->" << (char)(w+'A') << "): ";
    int from = w;
    vector<int> OutPath;
    OutPath.push_back(w);
    while(path[from]!=0){
        OutPath.push_back(path[from]);
        from = path[from];
    }
    OutPath.push_back(0);
    for(int i=OutPath.size()-1; i>=0; i--){
        cout << (char)(OutPath[i]+'A');
        if(i!=0){
            cout << " -> ";
        }
    }
    cout << endl;
}
```
### 运行结果
```c++
[dist] A->B = -1;  Path from (A->B): A -> B
[dist] A->C =  2;  Path from (A->C): A -> B -> C
[dist] A->D = -2;  Path from (A->D): A -> B -> E -> D
[dist] A->E =  1;  Path from (A->E): A -> B -> E
The shortest Path is [dist] A->D = -2;  Path from (A->D): A -> B -> E -> D
```
可知
* (1)求解从节点A->节点C的最短路径
[dist] A->C =  2;  Path from (A->C): A -> B -> C
* (2)求解从节点A出发到任意节点中路径最短的一条。
The shortest Path is [dist] A->D = -2;  Path from (A->D): A -> B -> E -> D

## No8．回溯算法（8皇后问题）
### 回溯算法
回溯算法实际上一个类似枚举的搜索尝试过程，主要是在搜索尝试过程中寻找问题的解，当发现已不满足求解条件时，就“回溯”返回，尝试别的路径。回溯法是一种选优搜索法，按选优条件向前搜索，以达到目标。但当探索到某一步时，发现原先选择并不优或达不到目标，就退回一步重新选择，这种走不通就退回再走的技术为回溯法，而满足回溯条件的某个状态的点称为“回溯点”。许多复杂的，规模较大的问题都可以使用回溯法，有“通用解题方法”的美称。
### 回溯算法在N皇后问题求解算发中实现（核心代码）

```c++
//用回溯算法求解8皇后问题
void NQueensByBackTracking(int n){
    int k=0;//k:表示行数，从第0行开始
    vector<int> x(n, -1);//创建int x[n]容器，x[k]用于存储第k行皇后放置的列数
    while (k>=0){
        x[k]++;//第k行皇后放置位置右移，初次正好到0； 回溯时在上一次失败尝试下右移
        //试探右移找到不冲突的列
        while(x[k]<n && !PLACE(k, x)){
            x[k]++;//列右移
        }
        //【判断】上一步退出while的原因（是否找到不冲突的列）
        //一、若已找到不冲突的列
        if (x[k] < n){
            //【判断】：是否所有行均找到结果
            //1.所有行结果均已找到：输出结果
            if(k == n-1){
                showResult(x);//显示n皇后结果
                return;
            }
            //2.k行后面行还没找到结果
            else{
                k++;//行数后移
                x[k] = -1;//初始值
            }
        }
        //二、（未找到不冲突的列）当前行k的所有结果均冲突时，回溯，行数k-1
        else{
            k--;
        }
    }
    if(k<0){
        cout << n << " queens problem has no answer" << endl;
    }
}
```
### 运行结果
```c++
The answer of 8 queens problem is:   0  4  7  5  2  6  1  3
============= Draw =============
   0  1  2  3  4  5  6  7
0  Q  -  -  -  -  -  -  -
1  -  -  -  -  Q  -  -  -
2  -  -  -  -  -  -  -  Q
3  -  -  -  -  -  Q  -  -
4  -  -  Q  -  -  -  -  -
5  -  -  -  -  -  -  Q  -
6  -  Q  -  -  -  -  -  -
7  -  -  -  Q  -  -  -  -
```

# 需注意点
* 在求解No3时：边界条件的判断、容器vector的使用、中间选择过程的记录；
* 在求解最长公共子序列时，对Dp中间求解的过程变量存储，选取的(i,j+1)还是（i+1,j）的细节判断，及后续逆便利中间过程记录二维矩阵时的走向与方向的细节执行；
* Dijkstra算法实现过程中的问题，图节点的遍历，及根据中间记录的选择过程逆向遍历得到最短路径；
* 回溯算法中什么时候k++,什么时候k--，以及x[k]的初值问题；
* 及各类算法编程实现的通用问题，算法实现、边界条件、状态转换、初值等等。


{% note success %}
**备注**
**运行平台**：Arch Linux
**运行环境**：C++
**所有实验题目完整源代码**：[AnalysisOfAlgorithmsLesson_code.zip](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/AnalysisOfAlgorithmsLesson_code.zip)
{% endnote %}
