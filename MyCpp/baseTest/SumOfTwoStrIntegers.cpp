/**
 * Sum of two integers
 * character: UTF-8
 * coder: EisenHao
 * date: 2020-04-24
 */
#include<iostream>
#include<string>
using namespace std;

/**
 * Compare two integers
 * return
 * @param strNumA
 * @param strNumB
 * @return 1 -- >;    0 -- =;    -1 -- <
 */
int compareAbsValue(string strNumA, string strNumB) {
    if (strNumA.length() == strNumB.length()) {
        return strNumA.compare(strNumB);
    }
    return strNumA.length() > strNumB.length() ? 1 : -1;
}

/**
 * Add two integers
 * @condition: strNumA is bigget than strNumB
 * @param strNumA
 * @param strNumB
 * @return ans
 */
string strNumAdd(string strNumA, string strNumB) {
    string ans = "0" + strNumA;
    bool jinWei = false;
    int tmp, iterAns = ans.length() - 1;
    for (int iterB = strNumB.length() - 1; iterB >= 0; --iterB, --iterAns) {
        tmp = ans[iterAns] - '0' + strNumB[iterB] - '0' + (jinWei ? 1 : 0);
        if (jinWei = (tmp > 9)) {
            tmp -= 10;
        }
        ans[iterAns] = tmp + '0';
    }
    while (jinWei && iterAns >= 0) {
        tmp = ans[iterAns] - '0' + (jinWei ? 1 : 0);
        if (jinWei = (tmp > 9)) {
            tmp -= 10;
        }
        ans[iterAns] = '0' + tmp;
        --iterAns;
    }
    // remove surplus '0'
    iterAns = 0;
    while ('0' == ans[iterAns] && iterAns < ans.length() - 1) {
        ++iterAns;
    }
    return 0 == iterAns ? ans : ans.substr(iterAns, ans.length() - iterAns);
}

/**
 * Subtract two integers
 * @condition: strNumA is bigget than strNumB
 * @param strNumA
 * @param strNumB
 * @return ans
 */
string strNumSub(string strNumA, string strNumB) {
    string ans = strNumA;
    bool jieWei = false;
    int tmp, iterAns = ans.length() - 1;
    for (int iterB = strNumB.length() - 1; iterB >= 0; --iterB, --iterAns) {
        tmp = (int)ans[iterAns]  - strNumB[iterB] - (jieWei ? 1 : 0);
        if (jieWei = (tmp < 0)) {
            tmp += 10;
        }
        ans[iterAns] = '0' + tmp;
    }
    while (jieWei && iterAns >= 0) {
        tmp = (int)ans[iterAns]  - '0' - (jieWei ? 1 : 0);
        if (jieWei = (tmp < 0)) {
            tmp += 10;
        }
        ans[iterAns] = '0' + tmp;
        --iterAns;
    }
    // remove surplus '0'
    iterAns = 0;
    while ('0' == ans[iterAns] && iterAns < ans.length() - 1) {
        ++iterAns;
    }
    return 0 == iterAns ? ans : ans.substr(iterAns, ans.length() - iterAns);
}

/**
 * Add two integers
 * @param strNumA
 * @param strNumB
 * @return ans
 */
string calc(string strNumA, string strNumB) {
    string ans;
    int flag = 0x11;// all Positive number
    if (strNumA.length() < 1 || strNumB.length() < 1) {
        return "";
    }
    if ('-' == strNumA[0]) {
        flag &= 0x01;
        strNumA = strNumA.substr(1, strNumA.length() - 1);
    }
    if ('-' == strNumB[0]) {
        flag &= 0x10;
        strNumB = strNumB.substr(1, strNumB.length() - 1);
    }

    switch (flag) {
        // all Positive number
        case 0x11:
            ans = (compareAbsValue(strNumA, strNumB) >= 0) ?
                    strNumAdd(strNumA, strNumB) : strNumAdd(strNumB, strNumA);
            break;
        // all negative number
        case 0x00:
            ans = "-" + ((compareAbsValue(strNumA, strNumB) >= 0) ?
                  strNumAdd(strNumA, strNumB) : strNumAdd(strNumB, strNumA));
            break;
        case 0x01:
            if (0 == compareAbsValue(strNumA, strNumB)) {
                ans = "0";
            } else if (compareAbsValue(strNumA, strNumB) > 0) {
                ans = "-" + strNumSub(strNumA, strNumB);
            } else {
                ans = strNumSub(strNumB, strNumA);
            }
            break;
        case 0x10:
            if (0 == compareAbsValue(strNumA, strNumB)) {
                ans = "0";
            } else if (compareAbsValue(strNumA, strNumB) > 0) {
                ans = strNumSub(strNumA, strNumB);
            } else {
                ans = "-" + strNumSub(strNumB, strNumA);
            }
        default:
            break;
    }
    if ("-0" == ans) {
        return "0";
    }
    return ans;
}

int main(){
    string strNumA, strNumB;
    while(cin >> strNumA >> strNumB){
        cout << calc(strNumA, strNumB) << endl;
    }
    return 0;
}