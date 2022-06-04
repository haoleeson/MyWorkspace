#include <iostream>
#include <vector>
using namespace std;

#define PhNumType long long int //type of various which can save the telephone number

struct CalledTimesOfPhNum {
    PhNumType phonenumber; //phonenumber
    int calledtimes; //the called times
};

void showVector ( void );//show Vector
int  SearchIfExist ( const PhNumType& inPutPhNum ); //Search if telephone number Exist
int& value ( const PhNumType& inPutPhNum ); //Search if telephone number Exist and deal with

void FindTheMadman ( const PhNumType& inPutPhNum );//find the Madman
void ShowTheMadMan (void);//OutPut the Madman

void FindTheMadman_2 ( void );//find the Madman 2

//
    int NumofMadman=0;
    vector<CalledTimesOfPhNum> CalledPhNumBuff;//built a Vector to save PhNum
    struct CalledTimesOfPhNum OutPut = { 99999999999, 0 };
//
int main (void) {
    PhNumType inPutPhNum;
    int N;
    //input Number elements of Data Array
    cin >> N;
    //Online deal with
    for( int i=0; i< 2*N; i++ ) {
        cin >> inPutPhNum;
        ++ value (inPutPhNum);
        //FindTheMadman ( inPutPhNum ); // Online deal with
    }
    //showVector ();
    //ShowTheMadMan();
    FindTheMadman_2();
    CalledPhNumBuff.clear();
    return 0;
}

//show Vector
void showVector ( void ) {
    cout << endl;
    for( int i=0; i<CalledPhNumBuff.size(); i++ ) {
        cout << "No." << i << ": " << CalledPhNumBuff[i].phonenumber <<" : " << CalledPhNumBuff[i].calledtimes << endl;
    }
}

//Search if telephone number Exist
int SearchIfExist ( const PhNumType& inPutPhNum ) {
    for ( int i=0; i<CalledPhNumBuff.size(); i++ ) {
        if ( inPutPhNum == CalledPhNumBuff[i].phonenumber ) {
            return i;
        }
    }
    return -1;
}
//Search if telephone number Exist and deal with
int& value ( const PhNumType& inPutPhNum ) {
    for ( int i=0; i<CalledPhNumBuff.size() ; i++ ) {
        //if Exist, return calledtimes
        if ( inPutPhNum == CalledPhNumBuff[i].phonenumber ) {
            return CalledPhNumBuff[i].calledtimes;
        }
    }
    //if don't Exist, add element to Buff 
    struct CalledTimesOfPhNum temp = { inPutPhNum, 0 };
    CalledPhNumBuff.push_back( temp );
    return CalledPhNumBuff[CalledPhNumBuff.size()-1].calledtimes;
}

//find the Madman
void FindTheMadman ( const PhNumType& inPutPhNum ) {
    int c_i;
    //step 1: find if Exist in Buff
    c_i = SearchIfExist( inPutPhNum );
    //deal with
    if ( c_i == -1 ) {
        //Option 1: no exit, add one telephone number at the end of Buff
        struct CalledTimesOfPhNum temp = {inPutPhNum,1};
        CalledPhNumBuff.push_back( temp );
    } else {
        //Option 2: exit, calledtimes + 1
        int tempcalledtimes = ++( CalledPhNumBuff[c_i].calledtimes );
        //Step 3: Find the Madman
        if ( tempcalledtimes > OutPut.calledtimes ) {
            //prepare to be the Madman
            NumofMadman = 1;
            OutPut.phonenumber = inPutPhNum;
            OutPut.calledtimes = tempcalledtimes;
        } else if ( tempcalledtimes == OutPut.calledtimes ) {
            //multiplies Madman
            NumofMadman++;
            //if phonenumber is smaller, then update
            if ( inPutPhNum < OutPut.phonenumber ) {
                OutPut.phonenumber = inPutPhNum;
            }
        }
    }
}
//find the Madman 2
void FindTheMadman_2 ( void ) {
    PhNumType temp, temp_phoneNum = 99999999999;
    int max_times = -1;
    for ( int i=0; i<CalledPhNumBuff.size(); i++ ) {
        temp = CalledPhNumBuff[i].calledtimes;
        if ( temp > max_times ) {
            NumofMadman = 1;
            max_times = CalledPhNumBuff[i].calledtimes;
            temp_phoneNum = CalledPhNumBuff[i].phonenumber;
        } else if ( temp == max_times ){
            NumofMadman++;
            if ( CalledPhNumBuff[i].phonenumber < temp_phoneNum ){
                temp_phoneNum = CalledPhNumBuff[i].phonenumber;
            }
        }
    }
    //ShowTheMadMan
    //Option 1: only one Madman
    cout << temp_phoneNum << " " << max_times;
    if ( NumofMadman > 1 ) {
        //Option 2: multiplies same Madman
        cout << " " << NumofMadman;
    }
}
//OutPut the Madman
void ShowTheMadMan(void) {
    //Option 1: only one Madman
    cout << OutPut.phonenumber << " " << OutPut.calledtimes;
    if ( NumofMadman > 1 ) {
        //Option 2: multiplies same Madman
        cout << " " << NumofMadman;
    }
}
