#include<iostream>
using namespace std;

class Solution {
public:
    string defangIPaddr(string address) {
        int len = address.length();
        char* buff = new char[len + 7];

        int index = 0;
        for (char ch : address) {
            if (ch == DOT_CH) {
                buff[index] = LEFT_BRACKETS;
                buff[index + 1] = DOT_CH;
                buff[index + 2] = RIGHT_BRACKETS;
                index += 3;
            } else {
                buff[index++] = ch;
            }
        }
        buff[index] = STR_END_CH;

        return string(buff);
    }

private:
    char DOT_CH = '.';
    char LEFT_BRACKETS = '[';
    char RIGHT_BRACKETS = ']';
    char STR_END_CH = '\0';
};

int main(void) {

    Solution solution;
    cout << solution.defangIPaddr("1.1.1.1") << endl;
    cout << solution.defangIPaddr("255.100.50.0") << endl;

    return 0;
}
