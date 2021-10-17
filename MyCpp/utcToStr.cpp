/**
  Describe: convert utc to str and str to utc
  Coding: UTF-8
*/

#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef unsigned long int UTCSECOND_TYPE;             // UTC秒数类型
#define MAX_STRTIME_LEN 30

//extern std::string utcToStr(time_t utcValue);
//extern UTCSECOND_TYPE strBatchNoToUtc(const std::string& strBatchNo);

/**
 * 将UTC时间转换为实时时间字符串
 * @param utcValue UTC秒数
 * @des eg. Input: 1577783825UL, Output: "20191231171705"
 * @return
 */
std::string utcToStr(time_t utcValue) {
    struct tm t;
    localtime_r(&utcValue, &t);
    char buf[MAX_STRTIME_LEN] = {0};
    strftime(buf, MAX_STRTIME_LEN, "%Y%m%d%H%M%S", &t);
    return buf;
}

/**
 * 将批次号转换为对应UTC秒数
 * @param strBatchNo 批次号
 * @des eg. Input: "201912311717", Output: 1577783820UL
 * @return
 */
UTCSECOND_TYPE strBatchNoToUtc(const std::string& strBatchNo) {
    if (strBatchNo.empty() || strBatchNo.length() < 12) {
        return 0;
    }

    struct tm t;
    int year = atoi(strBatchNo.substr(0,4).c_str());
    int mon = atoi(strBatchNo.substr(4,2).c_str());
    int day = atoi(strBatchNo.substr(6,2).c_str());
    int hour = atoi(strBatchNo.substr(8,2).c_str());
    int min = atoi(strBatchNo.substr(10,2).c_str());

    t.tm_year = year - 1900;
    t.tm_mon = mon - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = min;
    t.tm_sec = 0;
    t.tm_isdst = 0;// 不实行夏令时

    return (UTCSECOND_TYPE)mktime(&t);
}


int main() {
    std::cout << "Test 1 : UTC -> Str" << std::endl;
    time_t inputUTC = 1577783825UL;
    std::cout << "InputUTC = " << inputUTC << "UL, Output = " << utcToStr(inputUTC) << std::endl << std::endl;

    std::cout << "Test 2 : Str -> UTC" << std::endl;
    std::string inputStrBatchNo = "201912311717";
    std::cout << "InputStrBatchNo = \"" << inputStrBatchNo << "\", Output = " << strBatchNoToUtc(inputStrBatchNo) << "UL" << std::endl;
    return 0;
}
