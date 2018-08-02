#include <iostream>
using namespace std;
#define ElementType char
#define ElementType_Error 0
//单向链表结构体
struct node {
    ElementType Data;
    struct node *next;
};
//定义链表队列结构体
struct LinkQueue {
    node *rear;//保存队列尾节点地址
    node *front;//保存队列头节点地址
};

struct LinkQueue *creatLinkQueue(void);//建立队列
bool isEmptyQ(struct LinkQueue *PtrQ);//判断队列是否为空
void addQ(struct LinkQueue *PtrQ, ElementType item);//将数据元素添加到队列尾
ElementType deleteQ(struct LinkQueue *PtrQ);//将队列头数据出队，并删除

int main (void) {
    struct LinkQueue *p;
    p = creatLinkQueue();
    addQ(p, 'H');
    addQ(p, 'e');
    addQ(p, 'l');
    addQ(p, 'l');
    addQ(p, 'o');
    addQ(p, ' ');
    addQ(p, 'm');
    addQ(p, 'y');
    addQ(p, ' ');
    addQ(p, 'L');
    addQ(p, 'i');
    addQ(p, 'n');
    addQ(p, 'k');
    addQ(p, 'Q');
    addQ(p, 'u');
    addQ(p, 'e');
    addQ(p, 'u');
    addQ(p, 'e');
    addQ(p, ' ');
    addQ(p, ':');
    addQ(p, ')');
    cout << endl << "输出链表队列所有元素:";
    while(!isEmptyQ(p)) {
        cout << deleteQ(p);
    }
    delete []p;
    return 0;
}
//创建链表队列
struct LinkQueue *creatLinkQueue(void) {
    struct LinkQueue *PtrQ;
    PtrQ = new LinkQueue;
    PtrQ->front = NULL;
    PtrQ->rear = NULL;
    return PtrQ;
}
//判断队列是否为空
bool isEmptyQ(struct LinkQueue *PtrQ) {
    if (PtrQ->front == NULL) {
        return true;
    }
    return false;
}
//将数据元素添加到队列尾
void addQ(struct LinkQueue *PtrQ, ElementType item) {
    //空队列添加第一个节点
    if ( isEmptyQ(PtrQ) ) {
        PtrQ->rear = new node;
        PtrQ->rear->next = NULL;
        PtrQ->rear->Data = item;
        PtrQ->front = PtrQ->rear;
        return;
    }
    PtrQ->rear->next = new node;//分配新节点内存
    PtrQ->rear = PtrQ->rear->next;//指向队尾节点后移
    PtrQ->rear->next = NULL;
    PtrQ->rear->Data = item;
}
//将队列头数据出队，并删除
ElementType deleteQ(struct LinkQueue *PtrQ) {
    node *nodeTemp;
    ElementType Data;
    //队列为空
    if ( isEmptyQ(PtrQ) ) {
        cout << "Error: 队列为空" << endl;
        return ElementType_Error;
    }
    nodeTemp = PtrQ->front;//记录出队前　队列头节点地址
    //队列只剩一个节点
    if( PtrQ->front == PtrQ->rear ) {
        PtrQ->rear  = NULL;
        PtrQ->front = NULL;
    } else {
        PtrQ->front = PtrQ->front->next;//队列头节点下移
    }
    Data = nodeTemp->Data;
    delete []nodeTemp;
    return Data;
}
