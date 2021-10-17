#include<iostream>
using namespace std;

#define ElementType int

void Merge (ElementType A[], ElementType TempA[], int L, int R, int RightEnd);//子列归并：有序子列归并。将有序序列A[]的左、右两相邻的'某部分'序列合并成一个新的有序序列，存于TempA
void printf_Array(ElementType A[], int NumOfElements); //打印数组

int main (void) {
    ElementType Array[10] = {1, 5, 9, 13, 19, 57, 4, 8, 10, 24};
    ElementType Temp[10];//缓存子列归并中间交换部分的有序序列（虽然没啥用）
    cout << "打印原数组Array[]:" << endl;
    printf_Array( Array, 10);
//子列归并
    Merge( Array, Temp, 0, 6, 9);
    cout << "打印子列归并序列(1,5)与序列(6,9)后的数组Array[]:" << endl;
    printf_Array( Array, 10);
//显示子列归并中间数组TempA
    cout << "打印中间缓存的数组TempA[]:" << endl;
    printf_Array( Temp, 10);

    return 0;
}

//子列归并：有序子列归并。将有序序列A[]的左、右两相邻的'某部分'序列合并成一个新的有序序列，存于TempA
//参数说明：A[]－－原始待排序列A;   TempA[]－－待添加于A[]的临时序列，L－－A[]待归并的起始下标；R－－右边待归并序列起始下标；RightEnd－－右边待归并序列终止下标
//假定A[]序列终止下标，正好是TempA[]起始下标的前一位
void Merge (ElementType A[], ElementType TempA[], int L, int R, int RightEnd) {
    int temp, LeftEnd, NumOfElements;
    LeftEnd = R - 1; /* 左边终点下标与右边起始下标相邻  */
    temp = L; /*存放结果的数组初始位置*/
    NumOfElements = RightEnd - L + 1;
    // 开始比较大小　存放
    while ( (L <= LeftEnd) && (R <= RightEnd) ) {/*左右两序列都非空时执行*/
        if( A[L] < A[R] ) {
            TempA[temp++] = A[L++];
        } else {
            TempA[temp++] = A[R++];
        }
    }
    //左右两序列其一为空
    while ( L <= LeftEnd ) {
        TempA[temp++] = A[L++];
    }
    while ( R <= RightEnd ) {
        TempA[temp++] = A[R++];
    }
    //将归并后的有序子列TempA存于A[]原来的位置
    for (int i=NumOfElements; i>0; i--, RightEnd--) {
        A[RightEnd] = TempA[RightEnd];
    }
}
//打印数组
void printf_Array(ElementType A[], int NumOfElements) {
    int i = 0;
    while( i < NumOfElements ) {
        cout << A[i++] << " ";
    }
    cout << endl;
}
