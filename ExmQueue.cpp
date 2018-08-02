#include <iostream>
using namespace std;
#define ElementType char //宏定义数据类型
#define ElementType_Error 0 //宏定义数据类型错误标识
#define MaxSize 10 //宏定义队列大小

//循环队列，为方便判断是否已满，仅使用Maxsize-1个元素
struct Queue {
    ElementType Data[MaxSize];//数据区
    int rear;//队尾元素位置
    int front;//队头元素位置
};

struct Queue *creatQueue(void);//建立队列
bool isFullQ(struct Queue *PtrQ);//判断队列是否已满
bool isEmptyQ(struct Queue *PtrQ);//判断队列是否为空
void addQ(struct Queue *PtrQ, ElementType item);//将数据元素添加到队列尾
ElementType deleteQ(struct Queue *PtrQ);//将队列头数据出队，并删除

int main(void) {
    struct Queue *p;
    p = creatQueue();
    addQ(p, 'H');
    addQ(p, 'e');
    addQ(p, 'l');
    addQ(p, 'l');
    addQ(p, 'o');
    cout << endl << "输出队列所有元素:";
    while(!isEmptyQ(p)) {
        cout << deleteQ(p);
    }

    delete []p;//释放内存
    return 0;
}
//建立队列
struct Queue *creatQueue(void) {
    struct Queue *PtrQ;
    PtrQ = new Queue;
    PtrQ->rear = -1;
    PtrQ->front = -1;
    return PtrQ;
}
//判断队列是否为空
bool isEmptyQ(struct Queue *PtrQ) {
    if (PtrQ->rear == PtrQ->front) {
        return true;
    }
    return false;
}
//判断队列是否已满，队列只放 MaxSize-1 个元素
bool isFullQ(struct Queue *PtrQ) {
    if ( ((PtrQ->rear+1) % MaxSize) == PtrQ->front ) {
        return true;
    }
    return false;
}
//将数据元素添加到队列Q尾
void addQ(struct Queue *PtrQ, ElementType item) {
    if (isFullQ(PtrQ)) {
        cout << "Error: 队列已满" << endl;
        return;
    }
    PtrQ->rear = (PtrQ->rear+1) % MaxSize;//循环队列
    PtrQ->Data[PtrQ->rear] = item;
}
//将队列头数据出队，并删除
ElementType deleteQ(struct Queue *PtrQ) {
    if (isEmptyQ(PtrQ)) {
        cout << "Error: 队列为空" << endl;
        return ElementType_Error;//返回错误标示
    }
    PtrQ->front = (PtrQ->front+1) % MaxSize;//原front为-1, +1操作后正好为对列头下标
    return (PtrQ->Data[PtrQ->front]);
}

