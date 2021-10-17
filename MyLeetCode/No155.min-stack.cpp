/** 题目描述：
 * 155. 最小栈
 * 设计一个支持 push，pop，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) -- 将元素 x 推入栈中。
pop() -- 删除栈顶的元素。
top() -- 获取栈顶元素。
getMin() -- 检索栈中的最小元素。
示例:

MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.

 *
 * Encoding：utf-8
 * Programming language：c++
 * Coder：eisenhao
 * 20190319
 * */
#include <iostream>
#include <vector>

using namespace std;

class MinStack {
public:
    /** initialize your data structure here. */
    vector<int> stack;
    int min_index = -1;
    //构造函数
    MinStack() {
    }

    //入栈
    void push(int x) {
        stack.push_back(x);
        if (min_index == -1 || stack[min_index] > x) {
            min_index = stack.size()-1;
        }
    }

    //删除栈顶元素
    void pop() {
        //栈为空，什么也不做
        if (stack.size() == 0) {
            return;
        }
        //若栈顶元素为最小值(下标相同)
        if (stack.size()-1 == min_index) {
            //重新计算最小下标，考虑当前栈内元素个数
            if (stack.size() < 3) {
                //若当前元素个数为：1，2，则弹出后分别剩余的元素：0，1，最小值下标：-1，0
                min_index = stack.size()-2;
            } else {
                int min = stack[0];
                min_index = 0;
                for (int i=1; i<stack.size()-1; i++) {
                    if (min > stack[i]) {
                        min = stack[i];
                        min_index = i;
                    }
                }
            }
        }
        stack.pop_back();
    }

    int top() {
        return stack[stack.size()-1];
    }

    int getMin() {
        return stack[min_index];
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack obj = new MinStack();
 * obj.push(x);
 * obj.pop();
 * int param_3 = obj.top();
 * int param_4 = obj.getMin();
 */

