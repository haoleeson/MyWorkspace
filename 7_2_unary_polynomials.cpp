#include <iostream>
#include <vector>
using namespace std;

#define ElementType long int
#define Bigger( a, b ) ( ((a)>(b)) ? (a) : (b) )
#define Smaller( a, b ) ( ((a)<(b)) ? (a) : (b) )

//to avoid Segmentation Fault Error, vector more 1,eg:"vector<ElementType> M( Number + 1 )"

// struct of Univariate Polynomial  eg: aX^b
struct Polynomial {
    ElementType coefficient = 0; //coefficient   a
    ElementType index = 0; //index  b
};

void OutPutPolynomialA ( vector<Polynomial> &A, int Number ); //Output the Polynomial
void SummationAandB ( vector<Polynomial> &A, int NoA, vector<Polynomial> &B, int NoB );//OutPut the Summation of Polynomial A and B
void MultiplicationAandB ( vector<Polynomial> &A, int NoA, vector<Polynomial> &B, int NoB );//OutPut the multiplication of Polynomial A and B

int main (void) {
    int NoA = 0, NoB = 0;
    //input Polynomial A
    cin >> NoA;
    vector<Polynomial> A(NoA); //build a vector to save the first Polynomial
    for( int i=0; i<NoA; i++ ) {
        cin >> A[i].coefficient;
        cin >> A[i].index;
    }
    //input Polynomial B
    cin >> NoB;
    vector<Polynomial> B(NoB); //build a vector to save the second Polynomial
    for( int i=0; i<NoB; i++ ) {
        cin >> B[i].coefficient;
        cin >> B[i].index;
    }
/*
    OutPutPolynomialA( A, NoA );//Output the Polynomial A
    cout << endl;
    OutPutPolynomialA( B, NoB );//Output the Polynomial B
*/
    MultiplicationAandB( A, NoA, B, NoB );
    cout << endl;
    SummationAandB( A, NoA, B, NoB );
    B.clear();
    A.clear();
    return 0;
}

//Output the Polynomial
void OutPutPolynomialA ( vector<Polynomial> &A, int Number ) {
    for ( int i=0; i<Number ;i++ ) {
        //output Format control
        if ( i != 0 ) {
            cout << " ";
        }
        cout << A[i].coefficient << " " << A[i].index;
    }
}

//output Format control
void Print_Space_control ( bool *noPrintFLag ) {
    if ( !(*noPrintFLag) ) {
        cout << " ";
    } else {
        (*noPrintFLag) = false;
    }
}

//OutPut the Summation of Polynomial A and B
void SummationAandB ( vector<Polynomial> &A, int NoA, vector<Polynomial> &B, int NoB ) {
    int i=0, j=0, temp_sum;
    bool noPrintFLag = true;//output Format control
    while ( i<NoA && j<NoB ) {
        if ( A[i].index == B[j].index ) {
            //Option 1:  A[i].index and B[j].index are same
            temp_sum = A[i].coefficient + B[j].coefficient ;
            if ( temp_sum != 0 ) {
                Print_Space_control( &noPrintFLag );//output Format control
                cout << temp_sum << " " << A[i].index;
            }
            i++;
            j++;
        }else if ( A[i].index > B[j].index ) {
            //Option 2: A[i].index is bigger than B[j].index
            Print_Space_control( &noPrintFLag );//output Format control
            cout << A[i].coefficient << " " << A[i].index;
            i++;
        }else if ( B[j].index > A[i].index ) {
            //Option 3: A[i].index is smaller than B[j].index
            Print_Space_control( &noPrintFLag );//output Format control
            cout << B[j].coefficient << " " << B[j].index;
            j++;
        }else {}
    }
    while ( i < NoA ) {
        Print_Space_control( &noPrintFLag );//output Format control
        cout << A[i].coefficient << " " << A[i].index;
        i++;
    }
    while ( j < NoB ) {
        Print_Space_control( &noPrintFLag );//output Format control
        cout << B[j].coefficient << " " << B[j].index;
        j++;
    }
    //special Option zero Polynomial
    if ( noPrintFLag ) {
//        cout << "0 0";
        temp_sum = 0;
        cout << temp_sum << " " << temp_sum;
    }
}

//Find the max and output
void Find_Max ( vector<Polynomial> &M, vector<int> &xiabiao, int BiggerColumn, int SmallerRow ) {
    int max_temp = -1001, max_count=0, m_i;
    //Step 1: find the max
    for ( int i=0; i<SmallerRow; i++ ) {
        if ( xiabiao[i] < BiggerColumn ) {
            m_i = i*BiggerColumn + xiabiao[i];//the reall index in <vector>M
            if ( M[m_i].index > max_temp  ) {
                max_temp = M[m_i].index;
            }
        }
    }
    //Step 2: Count the number of max, and save the reall same max indexs(if more than 1)
    vector<int>save_max_i( SmallerRow , 0 );
    for ( int i=0; i<SmallerRow; i++ ) {
        if ( xiabiao[i] < BiggerColumn ) {
            m_i = i*BiggerColumn + xiabiao[i];//the reall index in <vector>M
            if ( M[m_i].index == max_temp  ) {
                save_max_i[max_count++] = m_i;
                xiabiao[i]++;
            }
        }
    }
    //Step 3: Output
    if ( max_count == 1 ) {
        cout << " " << M[(save_max_i[0])].coefficient << " " << M[(save_max_i[0])].index;
    } else if ( max_count > 1 ) {
        int sum_coefficient = 0;
        for ( int i=0; i<max_count; i++ ) {
            sum_coefficient += M[(save_max_i[i])].coefficient ;
        }
        if ( sum_coefficient != 0 ) {
            cout << " " << sum_coefficient << " " << M[(save_max_i[0])].index;
        }
    } else {}
    save_max_i.clear();
}

//OutPut the multiplication of Polynomial A and B
void MultiplicationAandB ( vector<Polynomial> &A, int NoA, vector<Polynomial> &B, int NoB ) {
    long int k=0, total_num = NoA * NoB;
    int SmallerRow, BiggerColumn;
    SmallerRow = Smaller ( NoA, NoB );
    BiggerColumn = Bigger ( NoA, NoB );
    //Step 1: save the multiplication result
    vector<Polynomial> M( total_num + 1 ); //build a vector to save the result of multiplication of Polynomial A and B
    if ( NoA > NoB ) {
        for ( int j=0; j<NoB; j++ ) {
            for ( int i=0; i<NoA; i++ ) {
                M[k].coefficient = A[i].coefficient * B[j].coefficient ;
                M[k].index = A[i].index + B[j].index ;
                k++;
            }
        }
    } else {
        for ( int i=0; i<NoA; i++ ) {
            for ( int j=0; j<NoB; j++ ) {
                M[k].coefficient = A[i].coefficient * B[j].coefficient ;
                M[k].index = A[i].index + B[j].index ;
                k++;
            }
        }
    }
    //Step 2: Find max index element and output the max
    vector<int> xiabiao( SmallerRow + 1, 0 );
    cout << M[0].coefficient << " " << M[0].index;
    xiabiao[0] = 1;
    for ( long int i=1; i<total_num; i++ ) {
        Find_Max( M, xiabiao, BiggerColumn, SmallerRow );
    }
    xiabiao.clear();
    M.clear();
}

