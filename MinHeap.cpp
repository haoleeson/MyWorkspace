#include "MinHeap.h"

int main (void) {
    int a[] = {13,43,84,96,22,65,70,47};
    MinHeap* m = new MinHeap ( a, 8 );
    //测试
    cout << "显示当前最小堆:" << endl;
    m->show();
    cout << "弹出最小堆顶的元素:" << m->pop() << endl;
    cout << "显示当前最小堆:" << endl;
    m->show();
    cout << "插入一个节点30:" << endl;
    m->push(30);
    cout << "显示当前最小堆:" << endl;
    m->show();
    return 0;
}
