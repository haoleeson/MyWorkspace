#include <iostream>
#include <cmath>
using namespace std;

//求解指数幂的值

int main(void)
{
	int x, y;

	cout << "输入底数x的值：";
	cin >> x;
	cout << "输入指数幂y的值：";
	cin >> y;
	cout << x << "的" << y << "次幂为：" << pow(x,y) << endl;
	return 0;
}
