/*
类模板
正如我们定义函数模板一样，我们也可以定义类模板。泛型类声明的一般形式如下所示：
template <class type> class class-name {
.
}
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>
using namespace std;
template <class T>
class Stack {
    public:
        void push(T const&);// 入栈
        void pop();// 出栈
        T top() const;// 返回栈顶元素
        bool empty() const{// 如果为空则返回真。
            return elems.empty();
        }
    private:
        vector<T> elems;// 元素
};

template <class T>
void Stack<T>::push (T const& elem) { //入栈
    // 追加传入元素的副本
    elems.push_back(elem);
}
template <class T>
void Stack<T>::pop () { //出栈
    if (elems.empty()) {
        throw out_of_range("Stack<>::pop(): empty stack");//若为空，抛出异常
    }
    // 删除最后一个元素
    elems.pop_back();
}
template <class T>
T Stack<T>::top () const { //返回栈顶元素
    if (elems.empty()) {
        throw out_of_range("Stack<>::top(): empty stack"); //若为空，抛出异常
    }
    // 返回最后一个元素的副本
    return elems.back();
}

int main(void) {
    try {
        Stack<int> intStack;  // int 类型的栈
        Stack<string> stringStack;    // string 类型的栈
        // 操作 int 类型的栈
        intStack.push(7);
        cout << intStack.top() <<endl;
        // 操作 string 类型的栈
        stringStack.push("hello");
        cout << stringStack.top() << std::endl;
        stringStack.pop();
        stringStack.pop();
    } catch (exception const& ex) { //捕获异常
        cerr << "Exception: " << ex.what() <<endl;
        return -1;
    }
        return 0;
}
