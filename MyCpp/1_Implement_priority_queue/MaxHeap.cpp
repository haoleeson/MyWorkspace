/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#include "MaxHeap.h"
int main(void)
{
    int a[] = {13,43,84,96,22,65,70,47};
    MaxHeap* m = new MaxHeap(a, 8);
    //测试
    cout << "显示当前最大堆:" << endl;
    m->show();
    cout << "弹出最大堆顶的元素:" << m->pop() << endl;
    cout << "显示当前最大堆:" << endl;
    m->show();
    cout << "插入一个节点90:" << endl;
    m->push(90);
    cout << "显示当前最大堆:" << endl;
    m->show();
    return 0;
}
