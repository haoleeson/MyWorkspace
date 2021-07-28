/**
 * Encoding：utf-8
 * Programming language：c++
 * Coder：EisenHao
 * */
#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <iostream>
#include <vector>
using namespace std;

#define ElementType int

//插入排序（从小到大）
void Insertion_Sort ( ElementType* PtrA, long int Number ) {
    ElementType temp;
    long int i;
    //认为A[0]已经插入了
    for ( long int P = 1; P < Number; P++ ) {
        temp = *( PtrA + P ) ;//取待插入排序元素到temp
        for ( i = P; i > 0 && *(PtrA + i - 1) > temp; i--) {
            //从后往前循环，大的元素往后挪，直到不小于temp处退出循环
            //A[i] = A[i-1];
            *(PtrA + i) = *(PtrA + i - 1);
        }
        *(PtrA + i) = temp;//此是i为不大于temp的下标，插入temp
    }
}

//Swap two elements of the Array
void Swap( ElementType *A, ElementType *B ) {
    ElementType temp;
    //三部曲
    temp = *A; // 存A
    *A = *B; //换A
    *B = temp; //换B
}

//快速排序中生成pivot
ElementType Median3( vector<ElementType> &A, long int Left, long int Right ) {
    long int Center = (Left + Right) / 2 ;
    if ( A[Left] > A[Center] ) {
        Swap( &A[Left], &A[Center] );
    }
    if ( A[Left] > A[Right] ) {
        Swap( &A[Left], &A[Right] );
    }
    if ( A[Center] > A[Right]) {
        Swap( &A[Center], &A[Right] );
    }
    //现在，左、中、右三个已经有序
    Swap( &A[Center], &A[Right-1] );
    //现在只需考虑　Left+1 ~ Right-2
    return A[Right-1];
}

//快速排序算法实现
#define Cutoff 5 //定义快速排序（递归）阈值，数组元素小于Cutoff直接插入排序
void Quicksort( vector<ElementType> &A, long int Left, long int Right ) {
    ElementType pivot;
    long int i, j;
    //是否进行快速排序，阈值判断
    if ( (Right - Left) >= Cutoff ) {
        //选主元pivot，藏于A[Right-1]
        pivot = Median3 ( A, Left, Right );
        i = Left ;
        j = Right - 1 ;
        //子集划分(pivot左边全小于pivot；pivot右边全大于pivot)
        for ( ; ; ) {
            while ( A[++i] < pivot ) {} //找到A[i] > pivot, 跳出
            while ( A[--j] > pivot ) {} //找到A[j] < pivot, 跳出
            if ( i < j ) {
                //说明A[i]与A[j]之间还有其他元素，可交换
                Swap( &A[i], &A[j] );
            } else {
                break;
            }
        }
        Swap( &A[i], &A[Right-1] ); //将pivot 放到中间，即i下标处
        Quicksort( A, Left, i-1 );//递归处理左边
        Quicksort( A, i+1, Right );//递归处理右边
    } else {
        //低于阈值，直接调用插入排序
        //递归到最小一层用插入排序(每段的插入排序地址为：&A + Left (即：绝对地址A 加相对地址Left)
        //最小一层插入排序元素个数Number = Right-Left+1
        Insertion_Sort (  &A[Left], Right-Left+1 );
    }
}
//快速排序（统一接口，加壳）
void Quick_Sort ( vector<ElementType> &A, long int Number ) {
    Quicksort ( A, 0, Number-1 );
}



//Prlong int the Array
void Print_Array ( vector<ElementType> &A, long int Number ) {
    int NumberOfPreRows = 10;
    
    for ( long int i=0; i<Number; i++) {
        cout << " " << A[i];
        if(i%NumberOfPreRows == (NumberOfPreRows-1)){
        	cout << endl;
        }
    }
}



#endif
