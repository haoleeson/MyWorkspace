#include <iostream>
#include <vector>
using namespace std;

#define LengthOfNum 11

struct PhNum{
    char phonenumber[LengthOfNum+1];
};
struct TimesofPhNum{
    char phonenumber[LengthOfNum+1];
    long int timesofcall = 1;//set 1 as default
};

void showVectorA ( vector<PhNum> &A, long int Number );//show Vector A
void CopyPhNum( char *PtrA, char *PtrB);//copy the telephone number
bool CmpPhNum( struct TimesofPhNum A, struct PhNum B );//compare the telephone number
bool isPhNumSmaller( char *PtrA, char *PtrB);//if smaller
long int SearchIfExist( vector<TimesofPhNum> &CallTimes, long int TotalNumofPheNum, struct PhNum B );//Search if telephone number Exist
void FindTheMadman ( vector<PhNum> &A, long int Number );//find the Madman

int main (void) {
    long int N;
    //input Number elements of Data Array
    cin >> N;
    if ( N <= 0 || N > 100000 ) {
        return 0;
    }
    vector<PhNum> A( 2*N + 1 ); //build a vector to save the Array
    for( long int i=0; i< 2*N; i += 2 ) {
        cin >> A[i].phonenumber >> A[i+1].phonenumber ;
    }
    FindTheMadman ( A, 2*N );
    A.clear();
    return 0;
}

//show Vector A
void showVectorA ( vector<PhNum> &A, long int Number ) {
    for( long int i=0; i<Number; i++ ) {
        cout << "No." << i << ": " << A[i].phonenumber << endl;
        // if ( i%2 == 0 ) cout << endl;
    }
}

//compare the telephone number
bool CmpPhNum( struct TimesofPhNum A, struct PhNum B ) {
    char* PtrA = &(A.phonenumber[0]);
    char* PtrB = &(B.phonenumber[0]);
    for ( int i=0; i<LengthOfNum; i++ ) {
        if ( *(PtrA+i) != *(PtrB+i) ) {
            return false;
        }
    }
    return true;
}

//copy the telephone number
void CopyPhNum( char *PtrA, char *PtrB) {
    for ( int i=0; i<LengthOfNum+1; i++ ) {
        *(PtrA+i) = *(PtrB+i);
    }
}

//if smaller
bool isPhNumSmaller( char *PtrA, char *PtrB) {
    for ( int i=0; i<LengthOfNum; i++ ) {
        if(  *(PtrA+i) < *(PtrB+i) ) {
            return true;
        }else if(  *(PtrA+i) > *(PtrB+i) ) {
            return false;
        }
    }
    return true;//if str A==B return true
}
//Search if telephone number Exist
long int SearchIfExist( vector<TimesofPhNum> &CallTimes, long int TotalNumofPheNum, struct PhNum B ) {
    for (long int i=0; i<TotalNumofPheNum; i++) {
        if ( CmpPhNum( CallTimes[i], B ) ) {
            return i;
        }
    }
    return -1;
}

//find the Madman
void FindTheMadman ( vector<PhNum> &A, long int Number ) {
    long int xiabiao, maxtimes=-1, NumOfSameMax=0, TotalNumofPheNum;

    vector<TimesofPhNum> CallTimes( 1 );
    CopyPhNum( &CallTimes[0].phonenumber[0], &A[0].phonenumber[0] );
    TotalNumofPheNum = 1;

    //Step 1: total the called times
    for ( long int i=1; i<Number; i++ ) {
        //step a: find if Exist
        xiabiao = SearchIfExist( CallTimes, TotalNumofPheNum, A[i] );
        //step b: deal with
        if ( xiabiao == -1 ) {
            // no exit, add one telephone number
            struct TimesofPhNum temp;
            CopyPhNum( &temp.phonenumber[0], &A[i].phonenumber[0] );
            CallTimes.insert( CallTimes.end(),  temp );
            TotalNumofPheNum++;
        } else {
            // exit, timesofcall + 1
            CallTimes[xiabiao].timesofcall++;
        }
    }
    /*
    // cout
    for (long int i=0; i< TotalNumofPheNum; i++) {
        cout << "No." << i << ": " << CallTimes[i].phonenumber << " CallTimes:" << CallTimes[i].timesofcall << endl;
    }
    if (isPhNumSmaller( &CallTimes[0].phonenumber[0], &CallTimes[1].phonenumber[0] )) cout << " true" <<endl;
    */

    //Step 2: Find the Max Called times
    for (long int i=0; i<TotalNumofPheNum; i++) {
        if (  CallTimes[i].timesofcall > maxtimes ) {
            maxtimes = CallTimes[i].timesofcall;
        }
    }
    //Step 3: Find the number of Same max
    for ( long int i=0; i<TotalNumofPheNum; i++ ) {
        if (  CallTimes[i].timesofcall == maxtimes ) {
            NumOfSameMax++;
            xiabiao = i;//save the xiabiao
        }
    }
    //Step 4: OutPut the Madman
    if (NumOfSameMax == 1) {
        //Option 1: only one Madman
        cout << CallTimes[xiabiao].phonenumber << " " << maxtimes;
    } else if ( NumOfSameMax > 1 ) {
        //Option 2: multiplies same Madman
        char OutNum[11];
        CopyPhNum( &OutNum[0], &CallTimes[xiabiao].phonenumber[0] );
        //Step a: Find the smallest Same max xiabiao
        for (long int i=0,k=0; i<TotalNumofPheNum; i++) {
            if (  CallTimes[i].timesofcall == maxtimes ) {
                if ( isPhNumSmaller( &CallTimes[i].phonenumber[0], &OutNum[0] ) ) {
                    CopyPhNum( &OutNum[0], &CallTimes[i].phonenumber[0] );
                }
            }
        }
        cout << OutNum << " " << maxtimes << " " << NumOfSameMax;
    }
    CallTimes.clear();
}
