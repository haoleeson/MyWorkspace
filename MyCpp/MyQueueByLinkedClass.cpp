//OOT第2次作业-EisenHao
#include <iostream>
#include "MyQueueByLinkedClass.h"

using namespace std;

int main(void)
{
    cout << endl << endl << "**************************************** No.1 char 类型队列 ****************************************" << endl;
    MyQueue<char>* charQueue;
    receiveData<char> charReceive;
    cout << "== 创建MyQueue对象1 ==" << endl;
    charQueue = new MyQueue<char>();
    cout << "此时队列长度为：" << charQueue->count() <<endl;

    cout << "== 入队操作 ==" << endl;
    for (char ch = 'A'; ch <= 'E'; ch++)
    {
        cout << "将 " << ch << " 入队" << endl;
        charQueue->push(ch);
    }
    cout << "此时队列长度为：" << charQueue->count() <<endl;

    cout << "== 查看队首元素数据 ==" << endl;
    charReceive = charQueue->top();
    if (charReceive.isSuccessReceived == false)
    {
        cout << "返回队首元素失败， 因为队列为空" << endl;
    }
    else
    {
        cout << "队首元素数据为：" << charQueue->top().snodeData << endl;
    }
    //弹出队列所有元素
    cout << "== 出队操作 ==" << endl;
    while (1)
    {
        charReceive = charQueue->pop();
        if(charReceive.isSuccessReceived)
        {
            cout << charReceive.snodeData << endl;
        }
        else
        {
            break;
        }
    }
    //判断队列是否存在元素
    if (charQueue->count() == 0)
    {
        cout << "所有元素已出队" << endl;
    }


    cout << endl << endl <<"**************************************** No.2 int 类型队列 ****************************************" << endl;
    MyQueue<int>* intQueue;
    receiveData<int> intReceive;
    cout << "== 创建MyQueue对象2 ==" << endl;
    intQueue = new MyQueue<int>();
    cout << "此时队列长度为：" << intQueue->count() <<endl;

    cout << "== 入队操作 ==" << endl;
    for (int num = 1; num <= 5; num++)
    {
        cout << "将 " << num << " 入队" << endl;
        intQueue->push(num);
    }
    cout << "此时队列长度为：" << intQueue->count() <<endl;

    cout << "== 查看队首元素数据 ==" << endl;
    intReceive = intQueue->top();
    if (intReceive.isSuccessReceived == false)
    {
        cout << "返回队首元素失败， 因为队列为空" << endl;
    }
    else
    {
        cout << "队首元素数据为：" << intQueue->top().snodeData << endl;
    }
    //弹出队列所有元素
    cout << "== 出队操作 ==" << endl;
    while (1)
    {
        intReceive = intQueue->pop();
        if(intReceive.isSuccessReceived)
        {
            cout << intReceive.snodeData << endl;
        }
        else
        {
            break;
        }
    }
    //判断队列是否存在元素
    if (intQueue->count() == 0)
    {
        cout << "所有元素已出队" << endl;
    }
    return 0;
}