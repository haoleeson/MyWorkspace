#include <iostream>
using namespace std;

#define MaxArraySize 1000

struct OutPutMaxSum {
    int Maxsum;
    long int No_start;
    long int No_end;
};

void Print_Array ( int A[], int Number );//打印数组
struct OutPutMaxSum MaxSubseqSum1( int A[], long int Number );//最大子列和　求解１：暴力 时间复杂度O(N^3)
struct OutPutMaxSum MaxSubseqSum2( int A[], long int Number );//最大子列和　求解2：略暴力 时间复杂度O(N^2)
struct OutPutMaxSum MaxSubseqSum4( int A[], long int Number );//最大子列和　求解4：最快 时间复杂度O(N)

int main (void) {
    int N;
    int A[MaxArraySize];
    int B[6] = {-2, 11, -4, 13, -5, -2};
    struct OutPutMaxSum out;
//    cin >> N;
//    cout << "N= " << N << endl;
//    for(long int i=0; i<N; i++) {
//        cin >> A[i];
//    }
//    Print_Array( A, N );
    out = MaxSubseqSum4( B, 6 );
    cout << "Maxsum = " << out.Maxsum ;
    cout << " " << out.No_start ;
    cout << " " << out.No_end ;
    return 0;
}
//打印数组
void Print_Array ( int A[], int Number ) {
    cout << "Print A[]" << endl;
    for ( int i=0; i<Number; i++ ) {
        cout << A[i] << " " ;
        if (i%5 == 4) cout << endl;
    }
    cout << endl;
}
//最大子列和　求解１：暴力 时间复杂度O(N^3)
struct OutPutMaxSum MaxSubseqSum1( int A[], long int Number ){
    int ThisSum;
    int i, j, k;
    struct OutPutMaxSum out;
    out.Maxsum = 0;

    for ( i=0; i<Number; i++) {
        for ( j=i; j<Number; j++ ) {
            ThisSum = 0;
            for ( k=i; k<=j; k++) {
                ThisSum += A[k];
            }
            if ( ThisSum > out.Maxsum ) {
                out.Maxsum = ThisSum;
                out.No_start = i;
                out.No_end = j;
            }
        }
    }
    return out;
}
//最大子列和　求解2：略暴力 时间复杂度O(N^2)
struct OutPutMaxSum MaxSubseqSum2( int A[], long int Number ){
    int ThisSum;
    int i, j;
    struct OutPutMaxSum out;
    out.Maxsum = 0;

    for ( i=0; i<Number; i++) {
        ThisSum = 0;
        for ( j=i; j<Number; j++ ) {
            ThisSum += A[j];
            if ( ThisSum > out.Maxsum ) {
                out.Maxsum = ThisSum;
                out.No_start = i;
                out.No_end = j;
            }
        }
    }
    return out;
}
//最大子列和　求解3：分而治之 时间复杂度O( N x log(N) )
struct OutPutMaxSum MaxSubseqSum3( int A[], long int Number ){

}
//最大子列和　求解4：最快 时间复杂度O(N)
struct OutPutMaxSum MaxSubseqSum4( int A[], long int Number ){
    int ThisSum = 0;

    struct OutPutMaxSum out;
    out.Maxsum = 0;
    out.No_start = 0;

    for ( long int i=0; i<Number; i++ ) {
        ThisSum += A[i];
        if ( ThisSum > out.Maxsum ) {
            out.Maxsum = ThisSum;
            out.No_end = i;
        } else if ( ThisSum < 0 ){
            ThisSum = 0;
            out.No_start = i + 1 ;
        }
    }
    return out;
}
