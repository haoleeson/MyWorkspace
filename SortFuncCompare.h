/***
 * @describe 测试各排序算法对相同规模用例排序消耗时长
 * @date 2019-11-06
 * @coder eisenhao
 * @Character UTF-8
 */
#ifndef _SORTFUNCCOMPARE_H_
#define _SORTFUNCCOMPARE_H_

#include <iostream>
#include <time.h>

// 宏定义参数配置
#define ElementType         int     // 排序元素类型
#define MAX_RAND_VALUE      65535   // 生成随机数的最大值
//#define m_uiSizeOfArray       1e5      // 待排序数组元素个数(每排序前会随机赋值)
#define NUM_OF_SORT_FUNC    7       // 排序函数的个数
#define COMPARE             >       // 大于符号(增排序)，小于符号(减排序)

class SortFuncCompare {
public:
    SortFuncCompare();
    ~SortFuncCompare();
    void refreshArray(unsigned int size);          // 生成随机数填充待排序数组
    void showArray(void);             // 打印数组
    double testRunTime(void (*pFunction)(ElementType*));             // 测试排序函数运行时间
    void testFuncRuntime(void);       // 排序算法运行时长检测

private:
    static void swapTwoNum(ElementType *num1, ElementType *num2);// 交换两数的值
    static void heapDown(ElementType *pArray, int fatherIndex, int maxIndex);// 完全二叉树大数下降操作
    static void mergeSort(ElementType *pArray, ElementType* tmpA, int leftIndex, int rightIndex);
    static void merge(ElementType* pArray, ElementType* tmpA, int leftIndex, int middleIndex, int rightIndex);
    static void quickSort(ElementType *pArray, int leftIndex, int rightIndex);
    static ElementType choosePivot(ElementType *pArray, int leftIndex, int rightIndex);
public:
    static void Bubble_Sort(ElementType* pArray);               // 1.冒泡排序
    static void Selection_Sort(ElementType* pArray);            // 2.选择排序
    static void Insertion_Sort(ElementType *pArray);            // 3.插入排序
    static void Shell_Sort(ElementType* pArray);                // 4.希尔排序
    static void Heap_Sort(ElementType* pArray);                 // 5.堆排序
    static void Merge_Sort(ElementType* pArray);                // 6.归并排序
    static void Quick_Sort(ElementType* pArray);                // 7.快速排序
private:
    ElementType* m_array;                                       // 待排序数组
    static int m_uiSizeOfArray;                                 // 待排序数组元素个数(每排序前会随机赋值)
    void (*func[NUM_OF_SORT_FUNC])(ElementType*);               // 各排序函数指针数组
};

#endif //_SORTFUNCCOMPARE_H_
