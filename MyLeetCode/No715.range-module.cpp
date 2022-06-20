//
// Created by eisenhao on 2022/6/20.
//

#include<iostream>
#include<vector>
using namespace std;

class RangeModule {
    struct Range {
        int left;
        int right;
    };
public:
    RangeModule() {}

    void addRange(int left, int right) {
        for (int i = 0; i < v.size(); ++i) {
            if (right < v[i].left) {
                v.insert(v.begin() + i, Range{left, right});
                return;
            } else if (right <= v[i].right) {
                // expend
                v[i].left = min(left, v[i].left);
                return;
            } else if (left <= v[i].right) {
                // 查看右侧是否落入后续范围，merge
                int j = i + 1;
                while (j < v.size() && right >= v[j].left) {
                    ++j;
                }
                --j;
                // merge
                v[i].left = min(left, v[i].left);
                v[i].right = max(right, v[j].right);
                if (j > i) {
                    v.erase(v.begin() + i + 1, v.begin() + j + 1);
                }
                return;
            }
        }
        v.push_back(Range{left, right});
    }

    bool queryRange(int left, int right) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i].left > left || v[i].right < left) {
                continue;
            }
            return right <= v[i].right;
        }
        return false;
    }

    void removeRange(int left, int right) {
        for (int i = 0; i < v.size(); ++i) {
            if (v[i].right <= left || v[i].left >= right) {
                continue;
            }
            if (right == v[i].right) {
                if (left <= v[i].left) {
                    v.erase(v.begin() + i);
                } else {
                    v[i].right = left;
                }
                return;
            } else if (right < v[i].right) {
                int tmp = v[i].left;
                v[i].left = right;

                // split
                if (left > tmp) {
                    v.insert(v.begin() + i, Range{tmp, left});
                }
                return;
            } else {
                v[i].right = left;
                // 查看右侧是否落入后续范围，batch delete
                int j = i + 1;
                while (j < v.size() && right > v[j].left) {
                    ++j;
                }
                --j;
                if (right < v[j].right) {
                    v[j].left = right;
                    --j;
                }
                if (left <= v[i].left) {
                    v.erase(v.begin() + i, v.begin() + j + 1);
                } else {
                    v.erase(v.begin() + i + 1, v.begin() + j + 1);
                }
                return;
            }
        }
    }
private:
    vector<Range> v;
};

int main(void) {
    RangeModule rangeModule;
    rangeModule.addRange(10, 20);
    rangeModule.removeRange(14, 16);
    cout << rangeModule.queryRange(10, 14) << endl;
    cout << rangeModule.queryRange(13, 15) << endl;
    cout << rangeModule.queryRange(16, 17) << endl;


//    rangeModule.addRange(6,8);
//    rangeModule.removeRange(7,8);
//    rangeModule.removeRange(8,9);
//    rangeModule.addRange(8,9);
//    rangeModule.removeRange(1,3);
//    rangeModule.addRange(1,8);
//    cout << rangeModule.queryRange(2,4) << endl;
//    cout << rangeModule.queryRange(2,9) << endl;
//    cout << rangeModule.queryRange(4,6) << endl;

    rangeModule.addRange(55,62);
    rangeModule.addRange(1,29);
    rangeModule.removeRange(18,49);
    rangeModule.queryRange(6,98);
    rangeModule.queryRange(59,71);
    rangeModule.removeRange(40,45);
    rangeModule.removeRange(4,58);
    rangeModule.removeRange(57,69);
    rangeModule.removeRange(20,30);
    rangeModule.removeRange(1,40);
    rangeModule.queryRange(73,93);
    rangeModule.removeRange(32,93);
    rangeModule.addRange(38,100);
    rangeModule.removeRange(50,64);
    rangeModule.addRange(26,72);
    rangeModule.queryRange(8,74);
    rangeModule.queryRange(15,53);
    rangeModule.addRange(44,85);
    rangeModule.addRange(10,71);
    rangeModule.queryRange(54,70);
    rangeModule.removeRange(10,45);
    rangeModule.queryRange(30,66);
    rangeModule.addRange(47,98);
    rangeModule.queryRange(1,7);
    rangeModule.removeRange(44,78);
    rangeModule.removeRange(31,49);
    rangeModule.addRange(62,63);
    rangeModule.addRange(49,88);
    rangeModule.removeRange(47,72);
    rangeModule.removeRange(8,50);
    rangeModule.removeRange(49,79);
    rangeModule.addRange(31,47);
    rangeModule.addRange(54,87);
    rangeModule.queryRange(77,78);
    rangeModule.queryRange(59,100);
    rangeModule.queryRange(8,9);
    rangeModule.queryRange(50,51);
    rangeModule.queryRange(67,93);
    rangeModule.removeRange(25,86);
    rangeModule.removeRange(8,92);
    rangeModule.queryRange(31,87);
    rangeModule.addRange(90,95);
    rangeModule.addRange(28,56);
    rangeModule.addRange(10,42);
    rangeModule.queryRange(27,34);
    rangeModule.addRange(75,81);
    rangeModule.addRange(17,63);
    rangeModule.removeRange(78,90);
    rangeModule.addRange(9,18);
    rangeModule.queryRange(51,74);
    rangeModule.removeRange(20,54);
    rangeModule.addRange(35,72);
    rangeModule.queryRange(2,29);
    rangeModule.addRange(28,41);
    rangeModule.addRange(17,95);
    rangeModule.addRange(73,75);
    rangeModule.queryRange(34,43);
    rangeModule.addRange(57,96);
    rangeModule.queryRange(51,72);
    rangeModule.removeRange(21,67);
    rangeModule.removeRange(40,73);
    rangeModule.removeRange(14,26);
    rangeModule.removeRange(71,86);
    rangeModule.queryRange(34,41);
    rangeModule.removeRange(10,25);
    rangeModule.queryRange(27,68);
    rangeModule.queryRange(18,32);
    rangeModule.removeRange(30,31);
    rangeModule.queryRange(45,61);
    rangeModule.addRange(64,66);
    rangeModule.addRange(18,93);
    rangeModule.queryRange(13,21);
    rangeModule.removeRange(13,46);
    rangeModule.removeRange(56,99);
    rangeModule.queryRange(6,93);
    rangeModule.addRange(25,36);
    rangeModule.removeRange(27,88);
    rangeModule.removeRange(82,83);
    rangeModule.addRange(30,71);
    rangeModule.addRange(31,73);
    rangeModule.addRange(10,41);
    rangeModule.queryRange(71,72);
    rangeModule.queryRange(9,56);
    rangeModule.addRange(22,76);
    rangeModule.queryRange(38,74);
    rangeModule.removeRange(2,77);
    rangeModule.queryRange(33,61);
    rangeModule.removeRange(74,75);
    rangeModule.addRange(11,43);
    rangeModule.queryRange(27,75);

//    vector<int > v2;
//    v2.push_back(1);
//    v2.push_back(2);
//    v2.push_back(3);
//    int i = 1, j = 0;
//    v2.erase(v2.begin()+i, v2.begin()+j+1);

    return 0;
}
