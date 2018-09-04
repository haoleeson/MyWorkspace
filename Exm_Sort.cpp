#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

#define ElementType int
#define MAXK 1e5 //函数最大重复调用次数
#define TempArrayNumber 6 //待排序数组　元素个数

// 用于测试的接口函数
void Test_Sort_Function( string showBuf ,void (*SortFun)(ElementType Array[], int Number) );//测试排序算法是否有效
void showFunctionUsingTime( string showBuf, void (*fun)(ElementType Array[], int Number) );//计算函数运行时长

// 排序函数
void Bubble_Sort ( ElementType A[], int Number );    //冒泡排序（从小到大）
void Insertion_Sort ( ElementType A[], int Number ); //插入排序（从小到大）
void Shell_Sort ( ElementType A[], int Number );     //希尔排序（从小到大）
void Heap_Sort ( ElementType A[], int Number );      //堆排序:伪代码(未完)
void Merge_Sort ( ElementType A[], int Number );     //递归排序（从小到大）

int main (void) {
/*    Test_Sort_Function( "冒泡排序", Bubble_Sort );
    Test_Sort_Function( "插入排序", Insertion_Sort );
    Test_Sort_Function( "希尔排序", Shell_Sort );
    //Test_Sort_Function( "堆排序(未完)", Heap_Sort );
    Test_Sort_Function( "递归排序", Merge_Sort );
*/
    showFunctionUsingTime( "冒泡排序", Bubble_Sort );
    showFunctionUsingTime( "插入排序", Insertion_Sort);
    showFunctionUsingTime( "希尔排序", Shell_Sort);
    //showFunctionUsingTime( "堆排序（未完）", Heap_Sort);
    showFunctionUsingTime( "递归排序", Merge_Sort);
    return 0;
}

//测试排序算法是否有效
void Test_Sort_Function( string showBuf, void (*SortFun)(ElementType Array[], int Number) ) {
    ElementType A[TempArrayNumber] = {34, 8, 64, 51, 32, 21};
    cout << "显示原数组A[]: ";
    for (int i=0; i<TempArrayNumber; i++) {
        cout << " " << A[i];
    }
    (*SortFun)( A, TempArrayNumber );
    cout << endl << showBuf <<" 后的数组A[]: ";
    //展示排好的数组
    for (int i=0; i<TempArrayNumber; i++) {
        cout << " " << A[i];
    }
    cout << endl << endl;
}

//计算函数运行时长
void showFunctionUsingTime( string showBuf, void (*fun)(ElementType Array[], int Number) ) {
    clock_t start, stop1, stop2;
    double duration; //运行时间　变量
    cout << "计算 "<< showBuf << " 用时:" << endl;
    //计算Function用时
    start = clock();//记录时钟此刻打点数
    //重复调用多次函数
    for (int i=0; i<MAXK; i++) {
        ElementType A[TempArrayNumber] = {34, 8, 64, 51, 32, 21};
        (*fun)(A, TempArrayNumber);
    }
    stop1 = clock();//记录始终此时打点数

    //重复调用多次函数
    for (int i=0; i<MAXK; i++) {
        ElementType A[TempArrayNumber] = {34, 8, 64, 51, 32, 21};
        (*fun)(A, TempArrayNumber);
    }
    stop2 = clock();//记录始终此时打点数

    duration = ( (double) ( (stop1-start) - (stop2-stop1) ) )/CLOCKS_PER_SEC/MAXK;//计算实际用时
//    cout << "Ticks1 = " << (double)(stop1 - start) << endl;
//    cout << "Ticks2 = " << (double)(stop2 -stop1) << endl;
    cout << "Using time = " << duration << " s" << endl;
}

//冒泡排序（从小到大）
void Bubble_Sort ( ElementType A[], int Number ) {
    bool isSwapedFlag;
    ElementType temp;
    for ( int i = Number-1; i > 0; i--) {
        isSwapedFlag = false;
        for ( int j = 0; j < i; j++) {
            // >:从小到大； <:从大到小
            if ( A[j] > A[j+1] ) {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                isSwapedFlag = true;
            }
        }
        if ( !isSwapedFlag ) break; //没有发生一次交换，说明已经有序，退出
    }
}

//插入排序（从小到大）
void Insertion_Sort ( ElementType A[], int Number ) {
    ElementType temp;
    int i;
    //认为A[0]已经插入了
    for ( int P = 1; P < Number; P++ ) {
        temp = A[P];//取待插入排序元素到temp
        for ( i = P; i > 0 && A[i-1] > temp; i--) {
            //从后往前循环，大的元素往后挪，直到不小于temp处退出循环
            A[i] = A[i-1];
        }
        A[i] = temp;//此是i为不大于temp的下标，插入temp
    }
}

//希尔排序（从小到大）
void Shell_Sort( ElementType A[], int Number) {
    ElementType temp;
    int i;
    //Hibbard增量序列:Dk = 2^k - 1 (相邻元素互质)
    //猜想Hibbard时间复杂度: Tavg = O(N^1.25)、Tworst = O(N^1.5)

    //Sedgewick增量序列:{1,5,19,41,109,...}－－9x4^i - 9x2^i + 1 或　4^i - 3x2^i + 1
    //猜想Sedgewick时间复杂度: Tavg = O(N^1.167)、Tworst = O(N^1.33)

    //希尔原始增量序列D{Number/2、Number/4、...、1}　－－劣势：增量元素不互质，则小增量可能不起作用
    //猜想希尔原始增量序列时间复杂度: Tworst = O(N^2)
    for ( int D = Number/2; D > 0; D /=2 ) {
        //每次循环按增量序列进行“插入排序”(视为将插入排序中的'1'换成'D')
        for (int p = D; p < Number; p++) {
            temp = A[p];
            for (i = p; i>=D && A[i-D]>temp; i-=D) {
                A[i] = A[i-D];
            }
            A[i] = temp;//此是i为不大于temp的下标，插入temp
        }
    }
}

//堆向下过滤子函数:tree_position－－当前堆根节点、Number－－当前堆元素个数
void PercDown( ElementType A[], int tree_position, int Number) {

}
//将当前堆的最大元素与堆下标最大的元素互换：A－－当前堆根节点地址（最大）、B－－当前堆下标最大的节点
void Swap( ElementType *A, ElementType *B) {
    ElementType *temp;
    temp = A;
    A = B;
    B = temp;
}
//堆排序:伪代码(未完)
void Heap_Sort ( ElementType A[], int Number ) {
    //建立最大堆
    for (int i = Number/2; i>=0; i--) {
        PercDown( A, i, Number );//调整成最大堆
    }

    for (int i = Number-1; i>0; i--) {
        Swap( &A[0], &A[i] );/*将最大值元素根节点，换到当前堆最后一个元素位置上去*/
        PercDown( A, 0, i );
    }
}
/**************************************************************************************************************************/
//子列归并：有序子列归并。将有序序列A[]的左、右两相邻的'某部分'序列合并成一个新的有序序列，存于TempA
//参数说明：A[]－－原始待排序列A;   TempA[]－－待添加于A[]的临时序列，L－－A[]待归并的起始下标；R－－右边待归并序列起始下标；Right_End－－右边待归并序列终止下标
//假定A[]序列终止下标，正好是TempA[]起始下标的前一位
void Merge ( ElementType A[], ElementType TempA[], int L, int R, int Right_End ) {
    int temp, LeftEnd, NumOfElements;
    LeftEnd = R - 1; /* 左边终点下标与右边起始下标相邻  */
    temp = L; /*存放结果的数组初始位置*/
    NumOfElements = Right_End - L + 1;
    // 开始比较大小　存放
    while ( (L <= LeftEnd) && (R <= Right_End) ) {
    /*左右两序列都非空时执行*/
        if( A[L] < A[R] ) {
            TempA[temp++] = A[L++];
        } else {
            TempA[temp++] = A[R++];
        }
    }
    //左右两序列其一为空,下方两while只会执行一个(将余下的所有元素拷贝到TempA[])
    while ( L <= LeftEnd ) {
        TempA[temp++] = A[L++];
    }
    while ( R <= Right_End ) {
        TempA[temp++] = A[R++];
    }
    //将归并后的有序子列TempA存于A[]原来的位置
    for (int i=NumOfElements; i>0; i--, Right_End--) {
        A[Right_End] = TempA[Right_End];
    }
}
//递归算法
void M_Sort( ElementType A[], ElementType TempA[], int L, int Right_End) {
    int Center;
    //分而治之
    if ( L < Right_End ) {
        Center = ( L + Right_End ) / 2;
        M_Sort( A, TempA, L, Center); /*左半部分递归调用*/
        M_Sort( A, TempA, Center+1, Right_End); /*右半部分递归调用*/
        Merge( A, TempA, L, Center+1, Right_End );//调用归并排序
    }
}
//递归排序算法（统一接口）
void Merge_Sort ( ElementType A[], int Number ) {
    ElementType *TempA;
    TempA = new ElementType[Number];//申请内存空间
    if ( TempA != NULL ) {
        //上一步申请内存空间成功
        M_Sort( A, TempA, 0, Number-1 );// 调用递归算法排序
        delete []TempA; //释放内存空间
    } else {
        cout << "Error: 空间不足" << endl;
    }
}
