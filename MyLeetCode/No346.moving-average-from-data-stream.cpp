#include <iostream>
#include <queue>

using namespace std;

class MovingAverage {
private:
    int totalSize;
    int curSize;
    double sum;
    queue<int> q;

public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        this->totalSize = size;
        this->curSize = 0;
        this->sum = 0;
    }

    double next(int val) {
        sum += val;
        q.push(val);
        ++curSize;
        if (curSize > totalSize) {
            sum -= q.front();
            q.pop();
            --curSize;
        }

        return sum / curSize;
    }
};

int main() {
    MovingAverage movingAverage(3);
    double res1 = movingAverage.next(1);
    cout << res1 << endl;
    double res2 = movingAverage.next(10);
    cout << res2 << endl;
    double res3 = movingAverage.next(3);
    cout << res3 << endl;
    double res4 = movingAverage.next(5);
    cout << res4 << endl;

    return 0;
}
