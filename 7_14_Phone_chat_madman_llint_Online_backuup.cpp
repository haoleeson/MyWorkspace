#include <iostream>
#include <vector>
using namespace std;

#define PhNumType long long int //type of various which can save the telephone number

struct CalledTimesOfPhNum{
    PhNumType phonenumber; //phonenumber
    int calledtimes = 1; //set 1 as default
};

void showVector ( vector<CalledTimesOfPhNum> &CalledPhNumBuff, int Number );//show Vector A
int SearchIfExist ( vector<CalledTimesOfPhNum> &CalledPhNumBuff, int NumofBuff, PhNumType inPutPhNum );//Search if telephone number Exist
void FindTheMadman ( PhNumType inPutPhNum );//find the Madman
void ShowTheMadMan (void);//OutPut the Madman

//
    int NumofMadman=0, NumofBuff=0;
    vector<CalledTimesOfPhNum> CalledPhNumBuff;//built a Vector to save PhNum
    struct CalledTimesOfPhNum OutPut;
//
int main (void) {
    int N;
    OutPut.phonenumber = 99999999999;
    OutPut.calledtimes = 0;
    //input Number elements of Data Array
    cin >> N;
    //Online deal with
    for( int i=0; i< 2*N; i++ ) {
        PhNumType inPutPhNum;
        cin >> inPutPhNum;
        FindTheMadman ( inPutPhNum ); // Online deal with
    }
    //showVector ( CalledPhNumBuff, NumofBuff );
    ShowTheMadMan();
    CalledPhNumBuff.clear();
    return 0;
}

//show Vector
void showVector ( vector<CalledTimesOfPhNum> &CalledPhNumBuff, int Number ) {
    for( int i=0; i<Number; i++ ) {
        cout << "No." << i << ": " << CalledPhNumBuff[i].phonenumber <<" : " << CalledPhNumBuff[i].calledtimes << endl;
        // if ( i%2 == 0 ) cout << endl;
    }
}

//Search if telephone number Exist
int SearchIfExist ( vector<CalledTimesOfPhNum> &CalledPhNumBuff, int NumofBuff, PhNumType inPutPhNum ) {
    for ( int i=0; i<NumofBuff; i++ ) {
        if ( inPutPhNum == CalledPhNumBuff[i].phonenumber ) {
            return i;
        }
    }
    return -1;
}

//find the Madman
void FindTheMadman ( PhNumType inPutPhNum ) {
    int c_i;
    //step 1: find if Exist in Buff
    c_i = SearchIfExist( CalledPhNumBuff, NumofBuff, inPutPhNum );
    //deal with
    if ( c_i == -1 ) {
        //Option 1: no exit, add one telephone number at the end of Buff
        struct CalledTimesOfPhNum temp;
        temp.phonenumber = inPutPhNum;
        CalledPhNumBuff.insert( CalledPhNumBuff.end(),  temp );
        NumofBuff++;
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

//OutPut the Madman
void ShowTheMadMan(void) {
    //Option 1: only one Madman
    cout << OutPut.phonenumber << " " << OutPut.calledtimes;
    if ( NumofMadman > 1 ) {
        //Option 2: multiplies same Madman
        cout << " " << NumofMadman;
    }
}
