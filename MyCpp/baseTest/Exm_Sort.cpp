#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

#define ElementType int
#define MAXK 1e5 // 函数最大重复调用次数
#define TempArrayNumber 6 // 待排序数组　元素个数

void Swap( ElementType *A, ElementType *B );// 交换两元素

// 用于测试的接口函数
void Test_Sort_Function( string showBuf ,void (*SortFun)(ElementType Array[], int Number) );// 测试排序算法是否有效
void showFunctionUsingTime( string showBuf, void (*fun)(ElementType Array[], int Number) );// 计算函数运行时长

// 排序函数
void Bubble_Sort ( ElementType A[], int Number );    // 冒泡排序（从小到大）
void Insertion_Sort ( ElementType A[], int Number ); // 插入排序（从小到大）
void Shell_Sort ( ElementType A[], int Number );     // 希尔排序（从小到大）
void Heap_Sort ( ElementType A[], int Number );      // 堆排序（从小到大）
void Merge_Sort ( ElementType A[], int Number );     // 递归归并排序（从小到大）
void Merge_Sort2 ( ElementType A[], int Number );    // 非递归归并排序（从小到大）
void Quick_Sort ( ElementType A[], int Number );     // 快速排序（从小到大）

int main (void) {
/*
    Test_Sort_Function( "冒泡排序", Bubble_Sort );
    Test_Sort_Function( "插入排序", Insertion_Sort );
    Test_Sort_Function( "希尔排序", Shell_Sort );
    // Test_Sort_Function( "堆排序", Heap_Sort );
    Test_Sort_Function( "递归归并排序", Merge_Sort );
    Test_Sort_Function( "非递归归并排序", Merge_Sort2 );
    Test_Sort_Function( "快速排序", Quick_Sort );
*/
    showFunctionUsingTime( "冒泡排序", Bubble_Sort );
    showFunctionUsingTime( "插入排序", Insertion_Sort );
    showFunctionUsingTime( "希尔排序", Shell_Sort );
    showFunctionUsingTime( "堆排序", Heap_Sort );
    showFunctionUsingTime( "递归归并排序", Merge_Sort );
    showFunctionUsingTime( "非递归归并排序", Merge_Sort2 );
    showFunctionUsingTime( "快速排序", Quick_Sort);
    return 0;
}

void Print_Array ( string showBuf, ElementType A[], int Number ) {
    cout << showBuf ;
    for (int i=0; i<Number; i++) {
        cout << " " << A[i];
    }
    cout << endl;
}

// 测试排序算法是否有效
void Test_Sort_Function( string showBuf, void (*SortFun)(ElementType Array[], int Number) ) {
    ElementType A[TempArrayNumber] = {34, 8, 64, 51, 32, 21};
    Print_Array( "显示原数组A[]:", A, TempArrayNumber );
    (*SortFun)( A, TempArrayNumber );
    cout << showBuf ;
    Print_Array( " 后的数组A[]:", A, TempArrayNumber );
    cout << endl;
}

// 计算函数运行时长
void showFunctionUsingTime( string showBuf, void (*fun)(ElementType Array[], int Number) ) {
    clock_t start, stop1, stop2;
    double duration; // 运行时间　变量
    cout << "计算 "<< showBuf << " 用时:" << endl;
    // 计算Function用时
    start = clock();// 记录时钟此刻打点数
    // 重复调用多次函数
    for (int i=0; i<MAXK; i++) {
        ElementType A[TempArrayNumber] = {34, 8, 64, 51, 32, 21};
        (*fun)(A, TempArrayNumber);
    }
    stop1 = clock();// 记录始终此时打点数

    // 重复调用多次函数
    for (int i=0; i<MAXK; i++) {
        ElementType A[TempArrayNumber] = {34, 8, 64, 51, 32, 21};
        (*fun)(A, TempArrayNumber);
    }
    stop2 = clock();// 记录始终此时打点数

    duration = ( (double) ( (stop1-start) - (stop2-stop1) ) )/CLOCKS_PER_SEC/MAXK;// 计算实际用时
    cout << "Using time = " << duration << " s" << endl << endl;
}
void Swap( ElementType *A, ElementType *B ) {
    ElementType temp;
    // 三部曲
    temp = *A; // 存A
    *A = *B; // 换A
    *B = temp; // 换B
}
// 冒泡排序（从小到大）
void Bubble_Sort ( ElementType A[], int Number ) {
    bool isSwapedFlag;
    ElementType temp;
    for ( int i = Number-1; i > 0; i--) {
        isSwapedFlag = false;
        for ( int j = 0; j < i; j++) {
            // >:从小到大； <:从大到小
            if ( A[j] > A[j+1] ) {
                Swap( &A[j], &A[j+1] );
                /*
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                */
                isSwapedFlag = true;
            }
        }
        if ( !isSwapedFlag ) break; // 没有发生一次交换，说明已经有序，退出
    }
}

// 插入排序（从小到大）
void Insertion_Sort ( ElementType A[], int Number ) {
    ElementType temp;
    int i;
    // 认为A[0]已经插入了
    for ( int P = 1; P < Number; P++ ) {
        temp = A[P];// 取待插入排序元素到temp
        for ( i = P; i > 0 && A[i-1] > temp; i--) {
            // 从后往前循环，大的元素往后挪，直到不小于temp处退出循环
            A[i] = A[i-1];
        }
        A[i] = temp;// 此是i为不大于temp的下标，插入temp
    }
}

// 希尔排序（从小到大）
void Shell_Sort( ElementType A[], int Number) {
    ElementType temp;
    int i;
    // Hibbard增量序列:Dk = 2^k - 1 (相邻元素互质)
    // 猜想Hibbard时间复杂度: Tavg = O(N^1.25)、Tworst = O(N^1.5)

    // Sedgewick增量序列:{1,5,19,41,109,...}－－9x4^i - 9x2^i + 1 或　4^i - 3x2^i + 1
    // 猜想Sedgewick时间复杂度: Tavg = O(N^1.167)、Tworst = O(N^1.33)

    // 希尔原始增量序列D{Number/2、Number/4、...、1}　－－劣势：增量元素不互质，则小增量可能不起作用
    // 猜想希尔原始增量序列时间复杂度: Tworst = O(N^2)
    for ( int D = Number/2; D > 0; D /=2 ) {
        // 每次循环按增量序列进行“插入排序”(视为将插入排序中的'1'换成'D')
        for (int p = D; p < Number; p++) {
            temp = A[p];
            for (i = p; i>=D && A[i-D]>temp; i-=D) {
                A[i] = A[i-D];
            }
            A[i] = temp;// 此是i为不大于temp的下标，插入temp
        }
    }
}

// 堆向下过滤子函数:tree_position－－当前堆根节点、Number－－当前堆元素个数
void PercDown(ElementType A[], int fatherIndex, int maxIndex) {
    int sonIndex = 2 * fatherIndex + 1;// default left son
    if (sonIndex < maxIndex) {
        // choose the bigger son
        if (sonIndex + 1 < maxIndex && A[sonIndex + 1] > A[sonIndex])
            ++sonIndex;
        // if the bigger son is bigger than its father, then swap
        if (A[sonIndex] > A[fatherIndex])
            Swap(&A[sonIndex], &A[fatherIndex]);
        down(A, sonIndex, maxIndex);
    }
}
// 堆排序
void Heap_Sort ( ElementType A[], int Number ) {
    // 建立最大堆
    for (int i = Number / 2 - 1; i >= 0; --i) {
        PercDown( A, i, Number );// 调整成最大堆
    }

    for (int i = Number - 1; i >= 1; --i) {
        Swap(&A[0], &A[i]);/*将最大值元素根节点，换到当前堆最后一个元素位置上去*/
        PercDown(A, 0, i);
    }
}
/**************************************************************************************************************************/
// 子列归并：有序子列归并。将有序序列A[]的左、右两相邻的'某部分'序列合并成一个新的有序序列，存于TempA
// 参数说明：A[]－－原始待排序列A;   TempA[]－－待添加于A[]的临时序列，L－－A[]待归并的起始下标；R－－右边待归并序列起始下标；Right_End－－右边待归并序列终止下标
// 假定A[]序列终止下标，正好是TempA[]起始下标的前一位
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
    // 左右两序列其一为空,下方两while只会执行一个(将余下的所有元素拷贝到TempA[])
    while ( L <= LeftEnd ) {
        TempA[temp++] = A[L++];
    }
    while ( R <= Right_End ) {
        TempA[temp++] = A[R++];
    }
    // 将归并后的有序子列TempA存于A[]原来的位置
    for (int i=NumOfElements; i>0; i--, Right_End--) {
        A[Right_End] = TempA[Right_End];
    }
}
// Merge2为前面Merge函数拷贝，但省去结尾将TempA[]拷贝回A[]的步骤
void Merge2 ( ElementType A[], ElementType TempA[], int L, int R, int Right_End ) {
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
    // 左右两序列其一为空,下方两while只会执行一个(将余下的所有元素拷贝到TempA[])
    while ( L <= LeftEnd ) {
        TempA[temp++] = A[L++];
    }
    while ( R <= Right_End ) {
        TempA[temp++] = A[R++];
    }
}
// 递归算法
void M_Sort( ElementType A[], ElementType TempA[], int L, int Right_End) {
    int Center;
    // 分而治之
    if ( L < Right_End ) {
        Center = ( L + Right_End ) / 2;
        M_Sort( A, TempA, L, Center); /*左半部分递归调用*/
        M_Sort( A, TempA, Center+1, Right_End); /*右半部分递归调用*/
        Merge( A, TempA, L, Center+1, Right_End );// 调用归并排序
    }
}
// 递归归并排序算法（统一接口）
void Merge_Sort ( ElementType A[], int Number ) {
    ElementType *TempA;
    TempA = new ElementType[Number];// 申请内存空间
    if ( TempA != NULL ) {
        // 上一步申请内存空间成功
        M_Sort( A, TempA, 0, Number-1 );// 调用递归算法排序
        delete []TempA; // 释放内存空间
    } else {
        cout << "Error: 空间不足" << endl;
    }
}
// 非递归算法
// length 相当于当前子列长度
void Merge_pass( ElementType A[], ElementType TempA[], int Number, int length ) {
    int i;
    // Number - 2*length　————先处理数组长度内能被２整除的前部分，尾巴先不管
    for ( i=0; i <= Number - 2*length; i += 2*length ) {
        Merge2 ( A, TempA, i,  i+length, i + 2*length -1 );
    }
    // 处理尾巴:
    // 尾巴长度为　1.0~1.9 倍的length时[还剩2个子列]，归并((0~1)*length)、((1*length~末尾)两个子列
    if (i+length < Number) {
        Merge2 ( A, TempA, i, i+length, Number-1 );
    } else {
        // 否则，只剩下不到一个子列，原样拷贝
        for (int j = i; j < Number; j++) {
            TempA[j] = A[j];
        }
    }
}
// 非递归归并排序算法（统一接口）
void Merge_Sort2 ( ElementType A[], int Number ) {
    int length = 1;// 初始化子序列长度
    ElementType *TempA;
    TempA = new ElementType[Number];// 申请内存空间
    if ( TempA != NULL ) {
        // 上一步申请内存空间成功,则进行非递归归并排序，一次循环执行两次
        while ( length < Number ) {
            Merge_pass( A, TempA, Number, length );
            length *= 2;
            Merge_pass( TempA, A, Number, length );
            length *= 2;
        }
        delete []TempA; // 释放内存空间
    } else {
        cout << "Error: 空间不足" << endl;
    }
}

ElementType Median3( ElementType A[], int Left, int Right ) {
    int Center = (Left + Right) / 2 ;
    if ( A[Left] > A[Center] ) {
        Swap( &A[Left], &A[Center] );
    }
    if ( A[Left] > A[Right] ) {
        Swap( &A[Left], &A[Right] );
    }
    if ( A[Center] > A[Right]) {
        Swap( &A[Center], &A[Right] );
    }
    // 现在，左、中、右三个已经有序
    Swap( &A[Center], &A[Right-1] );
    // 现在只需考虑　Left+1 ~ Right-2
    return A[Right-1];
}
// 快速排序算法实现
#define Cutoff 5 // 定义快速排序（递归）阈值，数组元素小于Cutoff直接插入排序
void Quicksort(ElementType A[], int Left, int Right ) {
    ElementType pivot;
    int i, j;
    // 是否进行快速排序，阈值判断
    if ( (Right - Left) >= Cutoff ) {
        // 选主元pivot，藏于A[Right-1]
        pivot = Median3 ( A, Left, Right );
        i = Left ;
        j = Right - 1 ;
        // 子集划分(pivot左边全小于pivot；pivot右边全大于pivot)
        for ( ; ; ) {
            while ( A[++i] < pivot ) {} // 找到A[i] > pivot, 跳出
            while ( A[--j] > pivot ) {} // 找到A[j] < pivot, 跳出
            if ( i < j ) {
                // 说明A[i]与A[j]之间还有其他元素，可交换
                Swap( &A[i], &A[j] );
            } else {
                break;
            }
        }
        Swap( &A[i], &A[Right-1] ); // 将pivot 放到中间，即i下标处
        Quicksort( A, Left, i-1 );// 递归处理左边
        Quicksort( A, i+1, Right );// 递归处理右边
    } else {
        // 低于阈值，直接调用插入排序
        // 递归到最小一层用插入排序(每段的插入排序地址为：&A + Left (即：绝对地址A 加相对地址Left)
        // 最小一层插入排序元素个数Number = Right-Left+1
        Insertion_Sort ( A+Left, Right-Left+1 );
    }
}
// 快速排序（统一接口，加壳）
void Quick_Sort ( ElementType A[], int Number ) {
    Quicksort ( A, 0, Number-1 );
}

