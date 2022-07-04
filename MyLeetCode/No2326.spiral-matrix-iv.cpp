#include <iostream>

#include "myTools.h"

using namespace std;

class Solution {
public:
    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
        vector<vector<int>> res(m, vector<int>(n, -1));

        const char arrow[4] = {'R', 'D', 'L', 'U'};
        int rMax = n - 1, dMax = m - 1, lMin = 0, uMin = 1;
        int aI = 0;
        ListNode* ptr = head;
        int x = 0, y = 0;

        while (ptr) {
            switch (arrow[aI]) {
                case 'R': {
                    while (ptr && y <= rMax) {
                        res[x][y++] = ptr->val;
                        ptr = ptr->next;
                    }
                    --y;    // 退格 y
                    ++x;    // 预增 x
                    --rMax; // 降低螺旋向右极限
                    break;
                }
                case 'D': {
                    while (ptr && x <= dMax) {
                        res[x++][y] = ptr->val;
                        ptr = ptr->next;
                    }
                    --x;    // 退格 x
                    --y;    // 预减 y
                    --dMax; // 降低螺旋向下极限
                    break;
                }
                case 'L': {
                    while (ptr && y >= lMin) {
                        res[x][y--] = ptr->val;
                        ptr = ptr->next;
                    }
                    ++y;    // 进格 y
                    --x;    // 预减 x
                    ++lMin; // 降低螺旋向左极限
                    break;
                }
                case 'U': {
                    while (ptr && x >= uMin) {
                        res[x--][y] = ptr->val;
                        ptr = ptr->next;
                    }
                    ++x;    // 进格 x
                    ++y;    // 预加 y
                    ++uMin; // 降低螺旋向上极限
                    break;
                }
            }

            ++aI;
            if (aI == 4) {
                aI = 0;
            }
        }

        return res;
    }
};

int main(void) {
    Solution solution;
    ListNode* ptr;

    int m1 = 3;
    int n1 = 5;
    int arr1[] = {3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0};
    ListNode* head1 = new ListNode();
    ptr = head1;
    for (int i = 0; i < sizeof(arr1) / sizeof(int); ++i) {
        ptr->next = new ListNode(arr1[i]);
        ptr = ptr->next;
    }
    head1 = head1->next;
    vector<vector<int>> res1 = solution.spiralMatrix(m1, n1, head1);
    MyTools::printVec2D(res1);

    int m2 = 1;
    int n2 = 4;
    int arr2[] = {0, 1, 2};
    ListNode* head2 = new ListNode();
    ptr = head2;
    for (int i = 0; i < sizeof(arr2) / sizeof(int); ++i) {
        ptr->next = new ListNode(arr2[i]);
        ptr = ptr->next;
    }
    head2 = head2->next;
    vector<vector<int>> res2 = solution.spiralMatrix(m2, n2, head2);
    MyTools::printVec2D(res2);

    int m3 = 4;
    int n3 = 5;
    int arr3[] = {515, 942, 528, 483, 20, 159, 868, 999, 474, 320, 734, 956, 12, 124, 224, 252, 909, 732};
    ListNode* head3 = new ListNode();
    ptr = head3;
    for (int i = 0; i < sizeof(arr3) / sizeof(int); ++i) {
        ptr->next = new ListNode(arr3[i]);
        ptr = ptr->next;
    }
    head3 = head3->next;
    vector<vector<int>> res3 = solution.spiralMatrix(m3, n3, head3);
    MyTools::printVec2D(res3);

    return 0;
}
