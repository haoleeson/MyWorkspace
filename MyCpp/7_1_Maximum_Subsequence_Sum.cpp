#include <iostream>
#include <vector>
using namespace std;

struct OutPutMaxSum {
    int Maxsum;
    long int No_start;
    long int No_end;
};

struct OutPutMaxSum MaxSubseqSum1( vector<int> &A, long int Number );//最大子列和　求解１：暴力 时间复杂度O(N^3)
struct OutPutMaxSum MaxSubseqSum2( vector<int> &A, long int Number );//最大子列和　求解2：略暴力 时间复杂度O(N^2)
struct OutPutMaxSum MaxSubseqSum4( vector<int> &A, long int Number );//最大子列和　求解4：最快 时间复杂度O(N)

int main (void) {
    long int N;
    struct OutPutMaxSum out;
    cin >> N;
    if ( N<=0 || N>100000 ) {
        return 0;
    }
    vector<int> A(N);//创建一个N个元素的向量
    for(long int i=0; i<N; i++) {
        cin >> A[i];
    }
    out = MaxSubseqSum4( A, N );
    cout << out.Maxsum ;
    cout << " " << out.No_start ;
    cout << " " << out.No_end ;
    A.clear();
    return 0;
}
//最大子列和　求解１：暴力 时间复杂度O(N^3)
struct OutPutMaxSum MaxSubseqSum1( vector<int> &A, long int Number ) {
    bool isAllNegative = true;//所有元素都为负数标记
    int ThisSum;
    long int i, j, k;
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
    //特殊情况判断，所有元素均为负数
    if ( out.Maxsum == 0 ) {
        for ( long int i=0; i<Number; i++ ) {
            if ( A[i] > 0 ) {
                isAllNegative = false;
                break;
            }
        }
        if ( isAllNegative ) {
            out.Maxsum = 0;
            out.No_start = 0;
            out.No_end = Number - 1;
        }
    }
    return out;
}
//最大子列和　求解2：略暴力 时间复杂度O(N^2)
struct OutPutMaxSum MaxSubseqSum2( vector<int> &A, long int Number ) {
    int ThisSum;
    long int i, j;
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
struct OutPutMaxSum MaxSubseqSum3( vector<int> &A, long int Number ) {
    struct OutPutMaxSum out;
    out.Maxsum = 0;
    out.No_start = 0;
    out.No_end = 0;

    return out;

}
//最大子列和　求解4：最快 时间复杂度O(N)
struct OutPutMaxSum MaxSubseqSum4( vector<int> &A, long int Number ) {
    bool isAllNegative = true;//所有元素都为负数标记
    bool isInPosibibleLie = false;//是否在可能的最大子列中
    int ThisSum = 0;
    long int temp_start = 0;
    struct OutPutMaxSum out;
    out.Maxsum = 0;
    out.No_start = 0;
    out.No_end = 0;

    for ( long int i=0; i<Number; i++ ) {
        ThisSum += A[i];
        if ( A[i] > 0 && isInPosibibleLie == false ) {
            isInPosibibleLie = true;
            temp_start = i;
        }
        if ( ThisSum > out.Maxsum ) {
            out.Maxsum = ThisSum;
            out.No_start = temp_start;
            out.No_end = i;
        } else if ( ThisSum <= 0 ){
            isInPosibibleLie = false;
            ThisSum = 0;
        }
    }
    //特殊情况判断，所有元素均为负数
    if ( out.Maxsum == 0 ) {
        for ( long int i=0; i<Number; i++ ) {
            if ( A[i] > 0 ) {
                isAllNegative = false;
                break;
            }
        }
        if ( isAllNegative ) {
            out.Maxsum = 0;
            out.No_start = 0;
            out.No_end = Number - 1;
        }
    }

    return out;
}

