#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/**
 * 剑指 Offer 20. 表示数值的字符串
 * 请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。
 * 例如，字符串"+100"、"5e2"、"-123"、"3.1416"、"-1E-16"、"0123"都表示数值，
 * 但"12e"、"1a3.14"、"1.2.3"、"+-5"及"12e+5.4"都不是。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/biao-shi-shu-zhi-de-zi-fu-chuan-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/


class Solution {
public:
    enum State {
        STATE_INITIAL,
        STATE_INT_SIGN,
        STATE_INTEGER,
        STATE_POINT,
        STATE_POINT_WITHOUT_INT,
        STATE_FRACTION,
        STATE_EXP,
        STATE_EXP_SIGN,
        STATE_EXP_NUMBER,
        STATE_END,
    };

    enum CharType {
        CHAR_NUMBER,
        CHAR_EXP,
        CHAR_POINT,
        CHAR_SIGN,
        CHAR_SPACE,
        CHAR_ILLEGAL,
    };

    CharType toCharType(char ch) {
        if (ch >= '0' && ch <= '9') {
            return CHAR_NUMBER;
        } else if (ch == 'e' || ch == 'E') {
            return CHAR_EXP;
        } else if (ch == '.') {
            return CHAR_POINT;
        } else if (ch == '+' || ch == '-') {
            return CHAR_SIGN;
        } else if (ch == ' ') {
            return CHAR_SPACE;
        } else {
            return CHAR_ILLEGAL;
        }
    }

    bool isNumber(string s) {
        unordered_map<State, unordered_map<CharType, State>> transfer{
                {
                        STATE_INITIAL, {
                                               {CHAR_SPACE, STATE_INITIAL},
                                               {CHAR_NUMBER, STATE_INTEGER},
                                               {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                                               {CHAR_SIGN, STATE_INT_SIGN},
                                       }
                }, {
                        STATE_INT_SIGN, {
                                               {CHAR_NUMBER, STATE_INTEGER},
                                               {CHAR_POINT, STATE_POINT_WITHOUT_INT},
                                       }
                }, {
                        STATE_INTEGER, {
                                               {CHAR_NUMBER, STATE_INTEGER},
                                               {CHAR_EXP, STATE_EXP},
                                               {CHAR_POINT, STATE_POINT},
                                               {CHAR_SPACE, STATE_END},
                                       }
                }, {
                        STATE_POINT, {
                                               {CHAR_NUMBER, STATE_FRACTION},
                                               {CHAR_EXP, STATE_EXP},
                                               {CHAR_SPACE, STATE_END},
                                       }
                }, {
                        STATE_POINT_WITHOUT_INT, {
                                               {CHAR_NUMBER, STATE_FRACTION},
                                       }
                }, {
                        STATE_FRACTION,
                        {
                                               {CHAR_NUMBER, STATE_FRACTION},
                                               {CHAR_EXP, STATE_EXP},
                                               {CHAR_SPACE, STATE_END},
                                       }
                }, {
                        STATE_EXP,
                        {
                                               {CHAR_NUMBER, STATE_EXP_NUMBER},
                                               {CHAR_SIGN, STATE_EXP_SIGN},
                                       }
                }, {
                        STATE_EXP_SIGN, {
                                               {CHAR_NUMBER, STATE_EXP_NUMBER},
                                       }
                }, {
                        STATE_EXP_NUMBER, {
                                               {CHAR_NUMBER, STATE_EXP_NUMBER},
                                               {CHAR_SPACE, STATE_END},
                                       }
                }, {
                        STATE_END, {
                                               {CHAR_SPACE, STATE_END},
                                       }
                }
        };

        int len = s.length();
        State st = STATE_INITIAL;

        for (int i = 0; i < len; i++) {
            CharType typ = toCharType(s[i]);
            if (transfer[st].find(typ) == transfer[st].end()) {
                return false;
            } else {
                st = transfer[st][typ];
            }
        }
        return st == STATE_INTEGER || st == STATE_POINT || st == STATE_FRACTION || st == STATE_EXP_NUMBER || st == STATE_END;
    }
};


class Solution0 {
public:
    bool isLegal(char ch) {
        if (ch >= '0' && ch <= '9') {
            return true;
        }
        switch (ch) {
            case '+':
            case '-':
            case 'e':
            case 'E':
            case '.':
                return true;
        }
        return false;
    }

    bool isNumber(string s) {
        bool SignFlag = false;// 正负号
        bool DecimalPointFlag = false;// 小数点
        bool eFlag = false;// 科学计数符
        bool eFollowNumber = false;
        bool DecimalPointFollowNumber = false;
        bool numberFlag = false;

        int len = s.length();
        for (char ch : s) {
            if (!isLegal(ch)) {
                return false;
            }

            switch (ch) {
                case '+':
                case '-':
                    if (SignFlag && (!eFlag)) {
                        return false;
                    }
                    SignFlag = true;
                    break;

                case 'e':
                case 'E':
                    if (eFlag || !numberFlag) {
                        return false;
                    }
                    eFlag = true;
                    break;

                case '.':
                    if (eFlag || DecimalPointFlag || !numberFlag) {
                        return false;
                    }
                    DecimalPointFlag = true;
                    break;
            }

            if (ch >= '0' && ch <= '9') {
                if (eFlag && !eFollowNumber) {
                    eFollowNumber = true;
                }
                if (DecimalPointFlag && !DecimalPointFollowNumber) {
                    DecimalPointFollowNumber = true;
                }
                if (!numberFlag) {
                    numberFlag = true;
                }
            }
        }

        if (eFlag && !eFollowNumber) {
            return false;
        }
        if (DecimalPointFlag && !DecimalPointFollowNumber) {
            return false;
        }
        return true;
    }
};

int main() {
    Solution solution;
    string string1 = "3.1416";
    cout << solution.isNumber(string1) << endl;
    return 0;
}
