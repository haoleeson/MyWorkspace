/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：黎豪-软件工程-18101223769
 * */
#include "QuickSort.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define random(x) (rand()%x)


int main(void)
{
    srand((int)time(0));
    long int Number = 100;
    //构造Number + 1大小的容器
    vector<ElementType> A( Number + 1 ); //build a vector to
    //产生Number个随机数并赋值
    for(long int i=0; i<Number; i++)
        A[i] = random(100);
    //Print A
    cout << "Creat 100 random Num:" << endl << endl;
    Print_Array(A, Number);

    cout << endl << "Execute Quick Sort" << endl;

    Quick_Sort( A, Number );
    cout << "Result:" << endl << endl;
    //Print A
    Print_Array(A, Number);

    return 0;
}
