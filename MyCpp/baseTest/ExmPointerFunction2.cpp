#include <iostream>
#include <string>
using namespace std;

struct UserMessage {
    string userName;
    string userPassword;
};

void showUser ( struct UserMessage* user ) {
    if ( user == NULL ) {
        cout << "Error: register failed!" << endl;
    } else {
        cout << "Success: register success:)" << endl;
        cout << "User: " << user->userName << endl << "Psw: " << user->userPassword << endl;
    }
}

struct UserMessage* Register ( void ) {
    string str0, str1, str2;
    cout << endl << "Please input UserName:";
    cin >> str0;
    cout << endl << "Please input Password:";
    cin >> str1;
    cout << endl << "Please input Password again:";
    cin >> str2;
    if ( str1.compare(str2) == 0 ) {
        //(string)(user->userName) = str0; //Doesn't work
        //(string)(user->userPassword) = str1; //Doesn't work
        struct UserMessage* user = new UserMessage;
        *user = { str0, str1 };
        return user;
    }
    return NULL;
}

int main(void) {
    struct UserMessage* Test = Register();
    showUser(Test);
    return 0;
}
