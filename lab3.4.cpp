#include <iostream>
using namespace std;

//requset Fibonacci

int fib (int n)
{
	if (n < 3){
		cout << "Return 1!\n";
		return 1;
	}else{
		cout << "Call fib(" << n-2 << ") and fib(" << n-1 << ").\n";
		return( fib(n-2) + fib(n-1));
	}
	return 0;
}

int main(void)
{
	int n=0, answer=0;
	cout << "Enter number n: ";
	cin >> n;
	answer = fib(n);
	cout << "'" << answer << "'" << " is the " << "'" << n << "'" << "'s Fibonacci"<<endl;
	return 0;
}

