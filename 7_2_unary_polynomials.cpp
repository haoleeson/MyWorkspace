#include <iostream>
#include <vector>
using namespace std;

#define ElementType long int
#define Bigger( a, b ) ( ((a)>(b)) ? (a) : (b) )
#define Smaller( a, b ) ( ((a)<(b)) ? (a) : (b) )

// struct of Univariate Polynomial  eg: aX^b
struct Polynomial {
    ElementType coefficient; //coefficient   a
    ElementType index; //index  b
};

void OutPutPolynomialA ( vector<Polynomial> &A, int Number ); //Output the Polynomial
void SummationAandB ( vector<Polynomial> &A, int NoA, vector<Polynomial> &B, int NoB );//OutPut the Summation of Polynomial A and B
void MultiplicationAandB ( vector<Polynomial> &A, int NoA, vector<Polynomial> &B, int NoB );//OutPut the multiplication of Polynomial A and B

int main (void) {
    int NoA, NoB;
    //input Polynomial A
    cin >> NoA;
    if ( NoA<=0 || NoA>1000 ) {
        return 0;
    }
    vector<Polynomial> A(NoA); //build a vector to save the first Polynomial
    for( int i=0; i<NoA; i++ ) {
        cin >> A[i].coefficient;
        cin >> A[i].index;
    }
    //input Polynomial B
    cin >> NoB;
    if ( NoB<=0 || NoB>1000 ) {
        return 0;
    }
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
    cout << endl;
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
void Print_Space_control ( bool *isFirstFlag ) {
    if ( !(*isFirstFlag) ) {
        cout << " ";
    } else {
        (*isFirstFlag) = false;
    }
}

//OutPut the Summation of Polynomial A and B
void SummationAandB ( vector<Polynomial> &A, int NoA, vector<Polynomial> &B, int NoB ) {
    int i=0, j=0, temp_sum;
    bool isFirstFlag = true;//output Format control
    while ( i<NoA && j<NoB ) {
        if ( A[i].index == B[j].index ) {
            //Option 1:  A[i].index and B[j].index are same
            temp_sum = A[i].coefficient + B[j].coefficient ;
            if ( temp_sum != 0 ) {
                Print_Space_control( &isFirstFlag );//output Format control
                cout << temp_sum << " " << A[i].index;
            }
            i++;
            j++;
        }else if ( A[i].index > B[j].index ) {
            //Option 2: A[i].index is bigger than B[j].index
            Print_Space_control( &isFirstFlag );//output Format control
            cout << A[i].coefficient << " " << A[i].index;
            i++;
        }else if ( B[j].index > A[i].index ) {
            //Option 3: A[i].index is smaller than B[j].index
            Print_Space_control( &isFirstFlag );//output Format control
            cout << B[j].coefficient << " " << B[j].index;
            j++;
        }else {}
    }

    while ( i < NoA ) {
        Print_Space_control( &isFirstFlag );//output Format control
        cout << A[i].coefficient << " " << A[i].index;
        i++;
    }
    while ( j < NoB ) {
        Print_Space_control( &isFirstFlag );//output Format control
        cout << B[j].coefficient << " " << B[j].index;
        j++;
    }
    //special Option zero Polynomial
    if ( isFirstFlag ) {
//        cout << "0 0";
        temp_sum = 0;
        cout << temp_sum << " " << temp_sum;
    }
}

void Find_Max ( vector<Polynomial> &M, vector<int> &xiabiao, int BiggerColumn, int smallerRow ) {
    int max_temp = -1001, max_count=0, m_i;
    //Step 1: find the max
    for ( int i=0; i<smallerRow; i++ ) {
        if ( xiabiao[i] < BiggerColumn ) {
            m_i = i*BiggerColumn + xiabiao[i];//the reall index in <vector>M
            if ( M[m_i].index > max_temp  ) {
                max_temp = M[m_i].index;
            }
        }
    }
    //Step 2: Count the number of max, and save the reall same max indexs(if more than 1)
    vector<int>save_max_i(smallerRow);
    for ( int i=0; i<smallerRow; i++ ) {
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
        cout << " " << sum_coefficient << " " << M[(save_max_i[0])].index;
    } else {}
    save_max_i.clear();
}

//OutPut the multiplication of Polynomial A and B
void MultiplicationAandB ( vector<Polynomial> &A, int NoA, vector<Polynomial> &B, int NoB ) {
    long int k=0;
    int smallerRow, BiggerColumn;
    smallerRow = Smaller ( NoA, NoB );
    BiggerColumn = Bigger ( NoA, NoB );

    //Step 1: save the multiplication result
    vector<Polynomial> M( NoA * NoB ); //build a vector to save the result of multiplication of Polynomial A and B
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
    vector<int> xiabiao( smallerRow, 0 );
    cout << M[0].coefficient << " " << M[0].index;
    xiabiao[0] = 1;
    for ( long int i=1; i<(NoA*NoB); i++ ) {
        Find_Max( M, xiabiao, BiggerColumn, smallerRow );
    }
    xiabiao.clear();
}

