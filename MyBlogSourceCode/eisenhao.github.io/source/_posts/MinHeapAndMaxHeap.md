layout: post
title: 最小堆与最大堆
date: 2018/10/16 23:20:44
updated: 2018/10/16 23:45:45
comments: true
tags:
- 数据结构
categories:
- 技术

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/MinHeapAndMaxHeap.jpg" class="full-image" />

- 堆是一种经过排序的完全二叉树，对其中任一非终端节点，其数据值不大于（或不小于）其左右子节点的值。
- 最小堆(最大堆)堆能保证堆顶元素最小(最大)，相比于用数组存放数据，如果要查找所有数据中最小(最大)的数据时，数组的时间复杂度为O(n)，而最小堆(最大堆)的时间复杂度为O(1)。
- 而数据增删数据时，需要保证最小堆(最大堆)的动态可维护性仅需O(logN)。因此在特定的需求环境，最小堆(最大堆)这种数据结构非常高效。

<!-- more -->

# 1. 最小堆
## 1.1. 最小堆概念
最小堆，是一种经过排序的完全二叉树，其中任一非终端节点的数据值均不大于其左子节点和右子节点的值。堆内的所有数据中最小的元素始终在堆顶，而增删一个元素而动态维护最小堆性质的时间复杂度仅为O(logN)
## 1.2. 最小堆实现思路
将最小堆二叉树存储到数组内，非根节点元素的父节点下标为(i-1)/2，若子节点存在则下标为2*i+1。
- **插入操作**：每当插入一个元素，将元素插入到容器（数组）尾部，然后执行迭代的上升操作，将插入的元素与其父节点比较，若比父节点小则交换，然后再与交换后节点的父节点相互比较交换，直到放置到合适位置。（最坏递归到根节点终止迭代）
- **取出操作**：弹出最小值（即数组首地址元素a[0]）。先交换交换堆顶与堆末，再弹出堆末（最小值），然后再将现堆顶元素执行迭代的下降操作，若其子节点存在与其子节点比较，若比子节点小则交换，然后再与交换后的子节点相互比较交换，直到放置在合适位置。（最坏递归到叶子节点）

## 1.3. 最小堆C++实现完整代码
### 1.3.1. 最小堆.h文件
```c++ 文件名：MinHeap.h
#ifndef MINHEAP_H_
#define MINHEAP_H_

#include <iostream>
#include <vector>
using namespace std;
#define ElementType int

//构造小顶堆类
class MinHeap
{
private:
    vector<ElementType> a;
public:
    //构造小顶堆
    MinHeap(ElementType elements[], int number)
    {
        for (int i=0; i<number; i++)
        {
            a.push_back(elements[i]);
        }
        for (int i=a.size()/2-1; i>=0; i--)
        {
            down(i);
        }
    }
    //交换i,j下标对应元素
    void swap(int i, int j)
    {
        ElementType temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    //上升操作
    void up(int i)
    {
        int fa =(i-1)/2;//f表示父节点下标
        if (i>0 && a[i]<a[fa])
        {
            swap(i, fa);
            up(fa);//如果一直比父节点小，递归到根节点(下标0)
        }
    }
    //插入点
    void push(ElementType p)
    {
        a.push_back(p);
        up(a.size()-1);//上升操作 直到合适位置
    }
    //下降操作
    void down(int i)
    {
        int son = 2*i+1;//son表示子节点下标
        if (son < a.size())
        {
            if (son+1 < a.size() && a[son] > a[son+1])
            {
                son++; //取值两个子节点 值更小的节点下标
            }
            //若子节点小，交换
            if (a[i] > a[son])
            {
                swap(i, son);
            }
            down(son);//递归调用，直到叶子节点
        }
    }
    //弹出堆顶节点（最小）
    ElementType pop()
    {
        ElementType result = a[0];
        swap(0, a.size()-1);//交换堆顶与堆末
        a.pop_back();//弹出
        down(0);//再将原来的最末元素（现在的堆顶元素）下降操作，使之到合适位置
        return result;
    }
    //输出堆(顺序输出)
    void show()
    {
        for (int i = 0; i < a.size(); i++)
        {
            cout << " " << a[i];
        }
        cout << endl;
    }
};

#endif
```
### 1.3.2. 最小堆.cpp范例代码

```c++ 文件名：MinHeap.cpp
#include "MinHeap.h"
int main(void)
{
    int a[] = {13, 43, 84, 96, 22, 65, 70, 47};
    MinHeap* m = new MinHeap(a, 8);
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
```

# 2. 最大堆
## 2.1. 最大堆概念

最大堆，是一种经过排序的完全二叉树，其中任一非终端节点的数据值均不小于其左子节点和右子节点的值。

## 2.2. 最大堆实现思路
将最大堆二叉树存储到数组内，非根节点元素的父节点下标为(i-1)/2，若子节点存在则下标为2*i+1。

- **插入操作**：每当插入一个元素，将元素插入到容器（数组）尾部，然后执行迭代的上升操作，将插入的元素与其父节点比较，若比父节点大则交换，然后再与交换后节点的父节点相互比较交换，直到放置到合适位置。（最坏递归到根节点终止迭代）
- **取出操作**：弹出最大值（即数组首地址元素a[0]）。先交换交换堆顶与堆末，再弹出堆末（最大值），然后再将现堆顶元素执行迭代的下降操作，若其子节点存在与其子节点比较，若比子节点小则交换，然后再与交换后的子节点相互比较交换，直到放置在合适位置。（最坏递归到叶子节点）

## 2.3. 最大堆C++实现完整代码
### 2.3.1. 最大堆.h代码

```c++ 文件名：MaxHeap.h
#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include <iostream>
#include <vector>
using namespace std;
#define ElementType int

//构造大顶堆类
class MaxHeap
{
private:
    vector<ElementType> a;
public:
    //构造大顶堆
    MaxHeap(ElementType elements[], int number)
    {
        for (int i=0; i<number; i++)
        {
            a.push_back(elements[i]);
        }
        for (int i=a.size()/2-1; i>=0; i--)
        {
            down(i);
        }
    }
    //交换i,j下标对应元素
    void swap(int i, int j)
    {
        ElementType temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    //上升操作
    void up(int i)
    {
        int fa = (i-1)/2;//f表示父节点下标
        if (i>0 && a[i] > a[fa])
        {
            swap(i, fa);
            up(fa);//如果一直比父节点大，递归到根节点(下标0)
        }
    }
    //插入点
    void push(ElementType p)
    {
        a.push_back(p);
        up(a.size()-1);//上升操作 直到合适位置
    }
    //下降操作
    void down(int i)
    {
        int son = 2 * i + 1;//son表示子节点下标
        if (son < a.size())
        {
            if (son+1 < a.size() && a[son] < a[son+1])
            {
                son++; //取值两个子节点 值更大的节点下标
            }
            //若子节点大，交换
            if (a[i] < a[son])
            {
                swap(i, son);
            }
            down(son);//递归调用，直到叶子节点
        }
    }
    //弹出堆顶节点（最大）
    ElementType pop()
    {
        ElementType result = a[0];
        swap(0, a.size()-1);//交换堆顶与堆末
        a.pop_back();//弹出
        down(0);//再将原来的最末元素（现在的堆顶元素）下降操作，使之到合适位置
        return result;
    }
    //输出堆(顺序输出)
    void show() 
    {
        for (int i = 0; i < a.size(); i++){
            cout << " " << a[i];
        }
        cout << endl;
    }
};


#endif
```

### 2.3.2. 最大堆.cpp范例代码

```c++ 文件名：MaxHeap.cpp
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
```
