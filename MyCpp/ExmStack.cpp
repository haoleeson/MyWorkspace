#include <iostream>
using namespace std;
#define StackMaxSize 10 //定义堆栈最大空间
#define ElementType char //宏定义堆栈数据类型
#define ElementTypeError 0 //堆栈数据类型的错误标识
//堆栈结构体
struct stack {
    ElementType Data[StackMaxSize];//堆栈数组
    int Top;//记录数组下标即为栈顶所在Top，Top=-1表示堆栈为空
};
//创建堆栈
struct stack *creatStack(void) {
    struct stack *stack1;
    stack1 = new stack;
    stack1->Top = -1;
    return stack1;
}
//入栈
void Push(struct stack *PtrS, ElementType item) {
    if (PtrS->Top == StackMaxSize-1) {
        cout << "堆栈已满" << endl;
        return;
    } else {
        PtrS->Data[++(PtrS->Top)] = item ;
        return;
    }
}
//出栈
ElementType Pop(struct stack *PtrS) {
    if (PtrS->Top == -1) {
        cout << "Error: 堆栈为空" << endl;
        return ElementTypeError;
    } else {
        return (PtrS->Data[(PtrS->Top)--]);
    }
}
//判断堆栈是否为空
bool ifStackEmpty(struct stack *PtrS) {
    if (PtrS->Top == -1) {
        return true;
    }
    return false;
}
int main(void) {
    struct stack *p;
    p = creatStack();
    Push(p,'A');
    Push(p,'B');
    Push(p,'C');
    Push(p,'D');
    //堆栈全部出栈
    while( !ifStackEmpty(p) ) {
        cout << "输出堆栈元素 No." << p->Top << " " << Pop(p) << endl;
    }
    delete []p;
    return 0;
}
