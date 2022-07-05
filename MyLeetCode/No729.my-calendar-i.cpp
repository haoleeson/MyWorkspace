#include <iostream>
#include <vector>

#include "myTools.h"

using namespace std;

class MyCalendar {
    struct Calendar {
        int start;
        int end;
        Calendar() {}
        Calendar(int _start, int _end) : start(_start), end(_end) {}
    };

public:
    MyCalendar() {}

    bool book(int start, int end) {
        int i = 0, sizeMyC = myC.size();
        for (; i < sizeMyC; ++i) {
            if ((start >= myC[i].start && start < myC[i].end) || (end > myC[i].start && end <= myC[i].end) ||
                (start < myC[i].start && end > myC[i].end)) {
                return false;
            }
            if (end <= myC[i].start) {
                break;
            }
        }

        // 尾部合并
        if (i - 1 >= 0 && myC[i - 1].end == start) {
            // 是否又与下一首部连接，更新，删除多余
            if (i < sizeMyC && end == myC[i].start) {
                myC[i - 1].end = myC[i].end;
                myC.erase(myC.begin() + i, myC.begin() + i + 1);
            } else {
                myC[i - 1].end = end;
            }
        }
        // 首部合并
        else if (i < sizeMyC && end == myC[i].start) {
            myC[i].start = start;
        }
        // 遍历完未冲突，独立插入
        else {
            myC.insert(myC.begin() + i, Calendar(start, end));
        }

        // 调试，打印
        //        cout << "[";
        //        for (int j = 0; j < myC.size(); ++j) {
        //            cout << ",[" << myC[j].start << "," << myC[j].end << "]";
        //        }
        //        cout << "]" << endl;

        return true;
    }

private:
    vector<Calendar> myC;
};

int main(void) {
    MyCalendar myCalendar1;
    int arr1[][2] = {{10, 20}, {15, 25}, {20, 30}};
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); ++i) {
        bool tmp = myCalendar1.book(arr1[i][0], arr1[i][1]);
        cout << tmp << endl;
    }

    MyCalendar myCalendar2;
    int arr2[][2] = {{10, 20}, {15, 25}, {41, 50}, {30, 40}, {20, 30}, {50, 60}, {40, 41}};
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); ++i) {
        bool tmp = myCalendar2.book(arr2[i][0], arr2[i][1]);
        cout << tmp << endl;
    }

    return 0;
}
