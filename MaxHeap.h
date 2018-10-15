#ifndef MAXHEAP_H_
#define MAXHEAP_H_

#include <iostream>
#include <vector>
using namespace std;
#define ElementType int

//构造大顶堆类
class MaxHeap {
private:
    vector<ElementType> a;
public:
    //构造大顶堆
    MaxHeap ( ElementType elements[], int number ) {
        for ( int i=0; i<number; i++ ) {
            a.push_back( elements[i] );
        }
        for ( int i=a.size()/2-1; i>=0; i-- ) {
            down(i);
        }
    }
    //交换i,j下标对应元素
    void swap ( int i, int j ) {
        ElementType temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
    //上升操作
    void up ( int i ) {
        int fa = (i-1)/2;//f表示父节点下标
        if ( i>0 && a[i] > a[fa]) {
            swap(i, fa);
            up(fa);//如果一直比父节点大，递归到根节点(下标0)
        }
    }
    //插入点
    void push ( ElementType p ) {
        a.push_back(p);
        up(a.size()-1);//上升操作 直到合适位置
    }
    //下降操作
    void down ( int i ) {
        int son = 2*i+1;//son表示子节点下标
        if ( son < a.size() ) {
            if ( son+1 < a.size() && a[son] < a[son+1] ) {
                son++; //取值两个子节点 值更大的节点下标
            }
            //若子节点大，交换
            if ( a[i] < a[son] ) {
                swap(i, son);
            }
            down( son );//递归调用，直到叶子节点
        }
    }
    //弹出堆顶节点（最大）
    ElementType pop () {
        ElementType result = a[0];
        swap( 0, a.size()-1 );//交换堆顶与堆末
        a.pop_back();//弹出
        down(0);//再将原来的最末元素（现在的堆顶元素）下降操作，使之到合适位置
        return result;
    }
    //输出堆(顺序输出)
    void show () {
        for ( int i = 0; i < a.size(); i++ ) {
            cout << " " << a[i];
        }
        cout << endl;
    }
};


#endif
