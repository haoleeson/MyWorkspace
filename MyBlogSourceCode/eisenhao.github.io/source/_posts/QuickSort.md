layout: post
title: QuickSort
date: 2018/10/23 14:45:30
updated: 2019/01/01 16:31:45
comments: true
tags:
- 算法
categories:
- 算法

---
<img src="../../../../uploads/QuickSort.jpg" class="full-image" />

# 1. 快速排序概念
快速排序（Quick Sort）由C. A. R. Hoare在1962年提出。它的基本思想是：通过一趟排序将要排序的数据分割成独立的两部分，其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
快速排序是不稳定的算法，时间复杂度在最坏情况下是O(N^2)，平均的时间复杂度是O(N*lgN)。
<!-- more -->
## 1.1. Quick Sort 实现思想
快速排序算法是一种基于交换的高效的排序算法，它采用了分治法的思想：
- 1、从数列中取出一个数作为基准数（枢轴，pivot）。 
- 2、将数组进行划分(partition)，将比基准数大的元素都移至枢轴右边，将小于等于基准数的元素都移至枢轴左边。
- 3、再对左右的子区间重复第2步的划分操作，直至每个子区间的元素个数不超过Cutoff（阈值）。
- 4、每个子区间内的元素执行插入排序（实践经验小于一定数量后插入排序快于快速排序），然后返回上一调用堆栈。

## 1.2. 快速排序.h完整代码
```c++ 文件名：QuickSort.h
#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <iostream>
#include <vector>
using namespace std;

#define ElementType int

//插入排序（从小到大）
void Insertion_Sort(ElementType* PtrA, long int Number){
    ElementType temp;
    long int i;
    //认为A[0]已经插入了
    for(long int P = 1; P < Number; P++){
        temp = *(PtrA + P);//取待插入排序元素到temp
        for(i = P; i > 0 && *(PtrA + i - 1) > temp; i--){
            //从后往前循环，大的元素往后挪，直到不小于temp处退出循环
            //A[i] = A[i-1];
            *(PtrA + i) = *(PtrA + i - 1);
        }
        *(PtrA + i) = temp;//此是i为不大于temp的下标，插入temp
    }
}

//Swap two elements of the Array
void Swap(ElementType *A, ElementType *B){
    ElementType temp;
    //三部曲
    temp = *A; // 存A
    *A = *B; //换A
    *B = temp; //换B
    //或利用异或性质原地交换
    //*B ^= *A;
    //*A ^= *B;
    //*B ^= *A;
}

//快速排序中生成pivot
ElementType Median3(vector<ElementType> &A, long int Left, long int Right){
    long int Center = (Left + Right)/ 2 ;
    if(A[Left] > A[Center]){
        Swap(&A[Left], &A[Center]);
    }
    if(A[Left] > A[Right]){
        Swap(&A[Left], &A[Right]);
    }
    if(A[Center] > A[Right]){
        Swap(&A[Center], &A[Right]);
    }
    //现在，左、中、右三个已经有序
    Swap(&A[Center], &A[Right-1]);
    //现在只需考虑　Left+1 ~ Right-2
    return A[Right-1];
}

//快速排序算法实现
#define Cutoff 5 //定义快速排序（递归）阈值，数组元素小于Cutoff直接插入排序
void Quicksort(vector<ElementType> &A, long int Left, long int Right){
    ElementType pivot;
    long int i, j;

    //是否进行快速排序，阈值判断
    if((Right - Left)>= Cutoff){
        //选主元pivot，藏于A[Right-1]
        pivot = Median3(A, Left, Right);
        i = Left ;
        j = Right - 1 ;
        //子集划分(pivot左边全小于pivot；pivot右边全大于pivot)
        for(; ;){
            while(A[++i] < pivot){} //找到A[i] > pivot, 跳出
            while(A[--j] > pivot){} //找到A[j] < pivot, 跳出
            if(i < j){
                //说明A[i]与A[j]之间还有其他元素，可交换
                Swap(&A[i], &A[j]);
            } else {
                break;
            }
        }
        Swap(&A[i], &A[Right-1]); //将pivot 放到中间，即i下标处
        Quicksort(A, Left, i-1);//递归处理左边
        Quicksort(A, i+1, Right);//递归处理右边
    } else {
        //低于阈值，直接调用插入排序
        //递归到最小一层用插入排序(每段的插入排序地址为：&A + Left(即：绝对地址A 加相对地址Left)
        //最小一层插入排序元素个数Number = Right-Left+1
        Insertion_Sort( &A[Left], Right-Left+1);
    }
}
//快速排序（统一接口，加壳）
void Quick_Sort(vector<ElementType> &A, long int Number){
    Quicksort(A, 0, Number-1);
}


//Prlong int the Array
void Print_Array(vector<ElementType> &A, long int Number){
    int NumberOfPreRows = 10;
    
    for(long int i=0; i<Number; i++){
        cout << " " << A[i];
        if(i%NumberOfPreRows == (NumberOfPreRows-1)){
        	cout << endl;
        }
    }
}
#endif
```

## 1.3. 快速排序.cpp范例代码
```c++ 文件名：QuickSort.cpp
#include "QuickSort.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x)(rand()%x)

int main(void)
{
    srand((int)time(0));
    long int Number = 100;
    //构造Number + 1大小的容器
    vector<ElementType> A(Number + 1); //build a vector to
    //产生Number个随机数并赋值
    for(long int i=0; i<Number; i++)
        A[i] = random(100);
    //Print A
    cout << "Creat 100 random Num:" << endl << endl;
    Print_Array(A, Number);

    cout << endl << "Execute Quick Sort" << endl;

    Quick_Sort(A, Number);
    cout << "Result:" << endl << endl;
    //Print A
    Print_Array(A, Number);

    return 0;
}
```

## 1.4. 延伸思考：
假设待排序的数列中有N个数。遍历一次的时间复杂度是O(N)，需要遍历多少次呢？

最多需要遍历N次，至少需要遍历lg(N+1)次。
- (1).为什么最少是lg(N+1)次？
快速排序是采用的分治法进行遍历的，我们将它看作一棵二叉树，它需要遍历的次数就是二叉树的深度，而根据完全二叉树的定义，它的深度至少是lg(N+1)。因此，快速排序的遍历次数最少是lg(N+1)次。
- (2).为什么最多是N次？
将快速排序看作一棵二叉树，它的深度最大是N。因此，快读排序的遍历次数最多是N次。
