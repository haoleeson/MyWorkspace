#include <string.h>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class SmallestInfiniteSet {
public:
    SmallestInfiniteSet() {
        minNum = 1;
        memset(flag, true, sizeof(flag));
    }

    int popSmallest() {
        int res = minNum;
        flag[minNum] = false;

        // 找到下一个最小正数
        while (minNum < 1001 && !flag[minNum]) {
            ++minNum;
        }
        return res;
    }

    void addBack(int num) {
        if (!flag[num]) {
            flag[num] = true;
            if (num < minNum) {
                minNum = num;
            }
        }
    }

private:
    bool flag[1001];
    int minNum;
};

int main(void) {
    SmallestInfiniteSet smallestInfiniteSet;

    smallestInfiniteSet.addBack(2);                    // 2 已经在集合中，所以不做任何变更。
    cout << smallestInfiniteSet.popSmallest() << endl; // 返回 1 ，因为 1 是最小的整数，并将其从集合中移除。
    cout << smallestInfiniteSet.popSmallest() << endl; // 返回 2 ，并将其从集合中移除。
    cout << smallestInfiniteSet.popSmallest() << endl; // 返回 3 ，并将其从集合中移除。
    smallestInfiniteSet.addBack(1);                    // 将 1 添加到该集合中。
    cout << smallestInfiniteSet.popSmallest() << endl; // 返回 1 ，因为 1 在上一步中被添加到集合中，
                                                       // 且 1 是最小的整数，并将其从集合中移除。
    cout << smallestInfiniteSet.popSmallest() << endl; // 返回 4 ，并将其从集合中移除。
    cout << smallestInfiniteSet.popSmallest() << endl; // 返回 5 ，并将其从集合中移除。

    return 0;
}
