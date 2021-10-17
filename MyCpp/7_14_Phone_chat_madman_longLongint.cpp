#include <iostream>
#include <vector>
using namespace std;

#define PhNumType long long int //type of various which can save the telephone number

struct CalledTimesOfPhNum{
    int A_i;//xiabiao
    int calledtimes = 1; //set 1 as default
};

void showVectorA ( vector<PhNumType> &A, int Number );//show Vector A
int SearchIfExist( vector<CalledTimesOfPhNum> &CalledPhNumBuff, int NumofBuff, vector<PhNumType> &A, int search_a_i );//Search if telephone number Exist
void FindTheMadman ( vector<PhNumType> &A, int Number );//find the Madman

int main (void) {
    int N;
    //input Number elements of Data Array
    cin >> N;
    vector<PhNumType> A( 2*N + 1 ); //build a vector to save the Array
    for( int i=0; i< 2*N; i++ ) {
        cin >> A[i];
    }
    //showVectorA ( A, 2*N );
    FindTheMadman ( A, 2*N );
    A.clear();
    return 0;
}

//show Vector A
void showVectorA ( vector<PhNumType> &A, int Number ) {
    for( int i=0; i<Number; i++ ) {
        cout << "No." << i << ": " << A[i] << endl;
        // if ( i%2 == 0 ) cout << endl;
    }
}
//Search if telephone number Exist
int SearchIfExist( vector<CalledTimesOfPhNum> &CalledPhNumBuff, int NumofBuff, vector<PhNumType> &A, int search_a_i ) {
    PhNumType temp_PhNum = A[search_a_i];
    for ( int i=0; i<NumofBuff; i++ ) {
        if ( temp_PhNum == A[ (CalledPhNumBuff[i].A_i)] ) {
            return i;
        }
    }
    return -1;
}

//find the Madman
void FindTheMadman ( vector<PhNumType> &A, int Number ) {
    int c_i, TheMaxCalledTimes=-1, NumofMadman=0, NumofBuff=0;
    PhNumType showSmallestPhNum = 999999999999;

    vector<CalledTimesOfPhNum> CalledPhNumBuff( 1 );
    CalledPhNumBuff[0].A_i = 0 ;
    NumofBuff = 1;

    //Step 1: total the called times
    for ( int i=1; i<Number; i++ ) {
        //step a: find if Exist
        c_i = SearchIfExist( CalledPhNumBuff, NumofBuff, A, i );
        //step b: deal with
        if ( c_i == -1 ) {
            // no exit, add one telephone number
            struct CalledTimesOfPhNum temp;
            temp.A_i = i;
            CalledPhNumBuff.insert( CalledPhNumBuff.end(),  temp );
            NumofBuff++;
        } else {
            // exit, calledtimes + 1
            int tempcalledtimes = ++( CalledPhNumBuff[c_i].calledtimes );
            //Step 2: Find the Max Called times
            if (  tempcalledtimes > TheMaxCalledTimes ) {
                TheMaxCalledTimes = tempcalledtimes;
            }
        }
    }
    //Step 3: Find the number of Same max
    for ( int i=0; i<NumofBuff; i++ ) {
        if (  CalledPhNumBuff[i].calledtimes == TheMaxCalledTimes ) {
            NumofMadman++;
            if ( A[(CalledPhNumBuff[i].A_i)] < showSmallestPhNum ) {
                showSmallestPhNum = A[(CalledPhNumBuff[i].A_i)];
            }
        }
    }
    //Step 4: OutPut the Madman
    if (NumofMadman == 1) {
        //Option 1: only one Madman
        cout << showSmallestPhNum << " " << TheMaxCalledTimes;
    } else if ( NumofMadman > 1 ) {
        //Option 2: multiplies same Madman
        cout << showSmallestPhNum << " " << TheMaxCalledTimes << " " << NumofMadman;
    }
    CalledPhNumBuff.clear();
}
