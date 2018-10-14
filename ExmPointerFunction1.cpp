#include <iostream>
using namespace std;

char* Cover (char* const Ptr ) {
    char* p = Ptr;
    char ch = *p ;
    while( ch != '\0' ) {
        if( ch >= 'a' && ch <= 'z' ) {
            *p -= 32;
        } else if ( ch >= 'A' && ch <= 'Z' ) {
            *p += 32;
        } else {}
        ch = *(++p);
    }
    return Ptr;
}

int main(void) {
    char str[15] = {"Hello World!"};
    cout << "Previous: " << str << endl;
    cout << "Aftet: " << Cover(str) << endl;
    return 0;
}
