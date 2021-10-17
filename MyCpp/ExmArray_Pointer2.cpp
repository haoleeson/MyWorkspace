#include <iostream>
using namespace std;
const int MAX = 4;
int main(int argc, const char * argv[]) 
{
    const char *names[MAX] = {
        "Zara Ali",
        "Hina Ali",
        "Nuha Ali",
        "Sara Ali",
    };
    for (int i = 0; i < MAX; i++) 
    {
        cout << " --- names[i]              = " << names[i] << endl;
        cout << " --- *names[i]             = " << *names[i] << endl;
        cout << endl;
        cout << " --- (*names[i] + 1)       = " << (*names[i] + 1) << endl;
        cout << " --- (char)(*names[i] + 1) = " << (char)(*names[i] + 1) << endl;
        cout << " ------------------------------------ " << endl << endl << endl << endl;
    }
    return 0;
}
