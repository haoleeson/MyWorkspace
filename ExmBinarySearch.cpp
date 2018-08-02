#include <iostream>
#define ElementType int
#define NoFindFlag -1
#define TableMaxSize 10
using namespace std;
int BinarySearch(ElementType Tbl[], int TableSize, ElementType K);//二分查找

int main (void) {
    ElementType Table[TableMaxSize] = {1,2,3,4,5,6,7,8,9,10};
    int ifSearch, K = 5;
    ifSearch = BinarySearch(Table, TableMaxSize, K);
    if( ifSearch != NoFindFlag ) {
        cout << "Success: 找到元素:" << K << ", 下标为:" << ifSearch << endl;
    } else {
        cout << "Error: 未找到元素:" << K << endl;
    }
    return 0;
}
//二分查找,要求：数组, 从小到大有序排列
int BinarySearch(ElementType Tbl[], int TableSize, ElementType K) {
    int left, right, mid;
    left = 1;
    right = TableSize - 1;
    while (left <= right) {
        mid = (left + right)/2;
        if ( K < Tbl[mid]) {
            right = mid - 1;
        }else if ( K > Tbl[mid] ) {
            left = mid + 1;
        } else {
            return mid;
        }
    }
    return NoFindFlag;
}
