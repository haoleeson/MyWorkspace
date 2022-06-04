#include <iostream>
using namespace std;
int main(void)
{
   char str[] = "Unable to read....";
   cout << "Error message : " << str << endl;
   cerr << "Error message : " << str << endl;
   clog << "Error message : " << str << endl; 
}
