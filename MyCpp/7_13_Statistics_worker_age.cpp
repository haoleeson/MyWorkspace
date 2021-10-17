#include <iostream>
#include <vector>
using namespace std;
#define ElementType int
#define AgeSegment 50

int main (void) {
    long int Number;
    int age;
    //input Number elements of Data Array
    cin >> Number;
    if ( Number <= 0 || Number > 100000 ) {
        return 0;
    }
    vector<ElementType> A( AgeSegment + 1, 0 ); //build a vector to save the Array
    for( long int i=0; i<Number; i++ ) {
        cin >> age;
        A[age] ++;
    }
    for( int i=0; i<AgeSegment+1; i++ ) {
        if ( A[i] != 0 ) {
            cout << i << ":" << A[i] << endl;
        }
    }
    A.clear();
    return 0;
}

