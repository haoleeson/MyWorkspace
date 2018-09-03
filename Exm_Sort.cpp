#include <iostream>
#include <time.h>
#include <math.h>
using namespace std;

#define ElementType int
#define MAXK 1e5 //函数最大重复调用次数

void showFunctionUsingTime(void (*fun)(ElementType Array[], int Number)); //计算函数运行时长
void Bubble_Sort (ElementType A[], int Number); //冒泡排序（从小到大）
void Insertion_Sort (ElementType A[], int Number); //插入排序（从小到大）
void Shell_sort(ElementType A[], int Number); //希尔排序

int main (void) {

    cout << "计算　冒泡排序　用时" << endl;
    showFunctionUsingTime(Bubble_Sort);
    //计算　插入排序　用时
    cout << "计算　插入排序　用时" << endl;
    showFunctionUsingTime(Insertion_Sort);
    //计算　希尔排序　用时
    cout << "计算　希尔排序　用时" << endl;
    showFunctionUsingTime(Shell_sort);




/*
    cout << "冒泡排序" << endl;
    ElementType A[6] = {34, 8, 64, 51, 32, 21};
    Bubble_Sort(A, 6);
    for (int i=0; i<6; i++) {
        cout << " " << A[i];
    }
    cout << endl;
    cout << "插入排序" << endl;
    ElementType B[6] = {34, 8, 64, 51, 32, 21};
    Insertion_Sort(B, 6);
    for (int i=0; i<6; i++) {
        cout << " " << B[i];
    }
    cout << endl;
    cout << "希尔排序" << endl;
    ElementType C[6] = {34, 8, 64, 51, 32, 21};
    Insertion_Sort(C, 6);
    for (int i=0; i<6; i++) {
        cout << " " << C[i];
    }
    cout << endl;

*/




    return 0;
}

//计算函数运行时长
void showFunctionUsingTime(void (*fun)(ElementType Array[], int Number)) {
    clock_t start1, stop1, start2, stop2;
    double duration; //运行时间　变量
    //计算Function用时
    start1 = clock();//记录时钟此刻打点数
    for (int i=0; i<MAXK ;i++) { //重复调用多次函数
        ElementType A[6] = {34, 8, 64, 51, 32, 21};
        (*fun)(A, 6);
    }
    stop1 = clock();//记录始终此时打点数

    start2 = clock();//记录时钟此刻打点数
    for (int i=0; i<MAXK ;i++) { //重复调用多次函数
        ElementType A[6] = {34, 8, 64, 51, 32, 21};
    }
    stop2 = clock();//记录始终此时打点数

    duration = ( (double)((stop1-start1) - (stop2-start2)) )/CLOCKS_PER_SEC/MAXK;//计算实际用时
    cout << "Ticks1 = " << (double)(stop1 - start1) << endl;
    cout << "Ticks2 = " << (double)(stop2 - start2) << endl;
    cout << "Using time = " << duration << " s" << endl;
}

//冒泡排序（从小到大）
void Bubble_Sort (ElementType A[], int Number ) {
    bool isSwapedFlag;
    ElementType temp;
    for (int i = Number-1; i > 0; i--) {
        isSwapedFlag = false;
        for (int j = 0; j < i; j++) {
            if ( A[j] > A[j+1] ) { // >:从小到大； <:从大到小
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
void Insertion_Sort (ElementType A[], int Number ) {
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

//希尔排序
void Shell_sort(ElementType A[], int Number) {
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

