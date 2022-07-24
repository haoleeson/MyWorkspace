#include <iostream>
#include <vector>
using namespace std;

// 思路：模拟正向反向
class Solution {
public:
    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        int lenN = distance.size(), smaller, bigger, optDist = 0, negDist = 0;

        // 找到正向顺序
        if (start < destination) {
            smaller = start;
            bigger = destination;
        } else if (start > destination) {
            smaller = destination;
            bigger = start;
        } else {
            return 0;
        }

        // 计算正向距离（smaller --> bigger）
        for (int i = smaller; i < bigger; ++i) {
            optDist += distance[i];
        }

        // 计算反向距离（bigger --> --> smaller）
        for (int i = bigger;; ++i) {
            // 跨终点站
            if (i == lenN) {
                i = 0;
            }
            if (i == smaller) {
                break;
            }
            negDist += distance[i];
        }

        return min(optDist, negDist);
    }
};

int main(void) {
    Solution solution;
    int arr1[] = {1, 2, 3, 4};
    int start1 = 0;
    int destination1 = 1;
    vector<int> distance1(arr1, arr1 + sizeof(arr1) / sizeof(int));
    int res1 = solution.distanceBetweenBusStops(distance1, start1, destination1);
    cout << res1 << endl;

    int arr2[] = {1, 2, 3, 4};
    int start2 = 0;
    int destination2 = 2;
    vector<int> distance2(arr2, arr2 + sizeof(arr2) / sizeof(int));
    int res2 = solution.distanceBetweenBusStops(distance2, start2, destination2);
    cout << res2 << endl;

    int arr3[] = {1, 2, 3, 4};
    int start3 = 0;
    int destination3 = 3;
    vector<int> distance3(arr3, arr3 + sizeof(arr3) / sizeof(int));
    int res3 = solution.distanceBetweenBusStops(distance3, start3, destination3);
    cout << res3 << endl;

    return 0;
}
