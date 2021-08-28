layout: post
title: 经典排序算法性能比较
date: 2019/11/17 19:26:44
updated: 2019/12/15 13:51:45
comments: true
tags:
- C++
- 算法
categories:
- 算法

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/SortFuncComparePicture.png" class="full-image" />

排序作为常用的解决实际问题的计算方法，被广泛应用于生活中的方方面面，如:成绩排名，价格升降序，相似产品比价等等。在数字化时代的今天，处理实际问题的数据规模常常十分庞大，同一个计算任务选用不同的算法，其执行效率可能相差几百倍，几千倍甚至更高，因此效率常被作入为评判一个算法优劣的重要指标。博主对七种经典排序算法（不止于此）进行编码实现和以处理同规模数据所耗时长为指标进行了性能比较（冒泡、选择、插入、希尔、堆、归并和快排）。
<!-- more -->

# 1. 测试排序函数运行时间方法
运行排序算法前后打点，取前后两次打点的差值，再除以打点的频率得到函数的运行时长。
```c++
/**
 * 测试排序函数运行时间
 * @param pFunction 排序函数的函数指针
 * @Return 运行时长（秒）
 */
double SortFuncCompare::testRunTime(void (*pFunction)(ElementType *)) {
    clock_t start, stop;
    double runTime;
    start = clock();
    (*pFunction)(m_array);
    stop = clock();
    runTime = ((double)stop - (double)start) / CLOCKS_PER_SEC;
//    cout << "run time = " << runTime << " s" << endl;
    return runTime;
}
```

# 2. 测试函数
定义排序函数的函数指针数组，size为7，逐一将七种static函数地址赋值到函数指针数组，然后循环执行七种函数对相同规模的随机数组的排序操作，便可得到各排序算法在各规模数据下的运行时长。
```c++
void (*func[NUM_OF_SORT_FUNC])(ElementType*);// 定义函数指针数组
func[0] = Bubble_Sort;      // 1.冒泡排序
func[1] = Selection_Sort;   // 2.选择排序
func[2] = Insertion_Sort;   // 3.插入排序
func[3] = Shell_Sort;       // 4.希尔排序
func[4] = Heap_Sort;        // 5.堆排序
func[5] = Merge_Sort;       // 6.归并排序
func[6] = Quick_Sort;       // 7.快速排序
void SortFuncCompare::testFuncRuntime(void) {
    double *runTime = new double[NUM_OF_SORT_FUNC];// Record the running time
    // Size of random array:10 ～ 100,000
    for (unsigned int size = MIN_NUM_OF_RAND_ARRAY; size <= MAX_NUM_OF_RAND_ARRAY; size *= 10) {
        for (int i = 0; i < NUM_OF_SORT_FUNC; ++i) {
            // Generate a random array
            refreshArray(size);
            // Execute and record the running time
            *(runTime + i) = testRunTime(func[i]);
        }
        // Output time consuming
        cout << "Num of Array = " << size << "\t: ";
        for (int j = 0; j < NUM_OF_SORT_FUNC - 1; ++j) {
            cout << *(runTime + j) << ", ";
        }
        cout << *(runTime + NUM_OF_SORT_FUNC - 1) << endl;
    }
    delete[] runTime;
}
```
# 3. 七种经典排序算法的编码实现
## 3.1. 冒泡排序
时间复杂度:O(N^2)，空间复杂度:O(1)，原地，稳定
```c++
void SortFuncCompare::Bubble_Sort(ElementType* pArray) {
//    cout << "Bubble Sort" << endl;
    bool swapFlag;
    for (int i = m_uiSizeOfArray - 1; i > 0; --i) {
        swapFlag = false;
        for (int j = 0; j < i; ++j) {
            if (*(pArray + j) COMPARE *(pArray + j + 1)) {
                swapTwoNum(pArray + j, pArray + j + 1);
                if (!swapFlag)
                    swapFlag = true;
            }
        }
        if (!swapFlag)
            break;
    }
}
```

## 3.2. 选择排序
时间复杂度:O(N^2)，空间复杂度:O(1)，原地，稳定
```c++
void SortFuncCompare::Selection_Sort(ElementType *pArray) {
//    cout << "Selection Sort" << endl;
    for (int i = 0; i < m_uiSizeOfArray - 1; ++i) {
        for (int j = i + 1; j < m_uiSizeOfArray; ++j) {
            if (*(pArray + i) COMPARE *(pArray + j))
                swapTwoNum(pArray + i, pArray + j);
        }
    }
}
```

## 3.3. 插入排序
时间复杂度:O(N^2)，空间复杂度:O(1)，原地，稳定
```c++
void SortFuncCompare::Insertion_Sort(ElementType *pArray) {
//    cout << "Insert Sort" << endl;
    ElementType tmp;
    int j;
    for (int i = 1; i < m_uiSizeOfArray; ++i) {
        tmp = *(pArray + i);
        for (j = i; j > 0 && *(pArray + j - 1) COMPARE tmp; --j) {
            *(pArray + j) = *(pArray + j - 1);
        }
        *(pArray + j) = tmp;
    }
}
```

## 3.4. 希尔排序
时间复杂度:O(N^1.25 ～N^1.5)，空间复杂度:O(1)，原地，非稳定
```c++
void SortFuncCompare::Shell_Sort(ElementType *pArray) {
//    cout << "Shell Sort" << endl;
    ElementType tmp;
    int j;
    for (int D = m_uiSizeOfArray / 2; D > 0; D /= 2) {
        // like Insert sort whose step is D
        for (int i = D; i < m_uiSizeOfArray; ++i) {
            tmp = *(pArray + i);
            for (j = i; j >= D && *(pArray + j - D) COMPARE tmp; j -= D) {
                *(pArray + j) = *(pArray + j - D);
            }
            *(pArray + j) = tmp;
        }
    }
}
```

## 3.5. 堆排序
时间复杂度:O(NlogN)，空间复杂度:O(1)，原地，非稳定
```c++
void SortFuncCompare::Heap_Sort(ElementType *pArray) {
//    cout << "Heap Sort" << endl;
    // build big root heap
    for (int i = m_uiSizeOfArray / 2 - 1; i >= 0; --i) {
        heapDown(pArray, i, m_uiSizeOfArray);
    }
    // choose biggest to end--
    for (int j = m_uiSizeOfArray - 1; j >= 1; --j) {
        swapTwoNum(pArray, pArray + j);
        heapDown(pArray, 0, j);
    }
}
void SortFuncCompare::heapDown(ElementType *pArray, int fatherIndex, int maxIndex) {
    int sonIndex = 2 * fatherIndex + 1;// default left son
    if (sonIndex < maxIndex) {
        // choose the bigger son
        if (sonIndex + 1 < maxIndex && *(pArray + sonIndex + 1) COMPARE *(pArray + sonIndex))
            ++sonIndex;
        // if the bigger son is bigger than its father, then swap
        if (*(pArray + sonIndex) COMPARE *(pArray + fatherIndex))
            swapTwoNum(pArray + sonIndex, pArray + fatherIndex);
        heapDown(pArray, sonIndex, maxIndex);
    }
}
```

## 3.6. 归并排序
时间复杂度:O(NlogN), 空间复杂度:O(n)，非原地，非稳定
```c++
void SortFuncCompare::Merge_Sort(ElementType *pArray) {
//    cout << "Merge Sort" << endl;
    ElementType* tmpA = new ElementType[m_uiSizeOfArray];
    if (NULL != tmpA) {
        mergeSort(pArray, tmpA, 0, m_uiSizeOfArray - 1);
        delete[] tmpA;
    }
}
void SortFuncCompare::mergeSort(ElementType *pArray, ElementType *tmpA, int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int middleIndex = (leftIndex + rightIndex) / 2;
        mergeSort(pArray, tmpA, leftIndex, middleIndex);
        mergeSort(pArray, tmpA, middleIndex + 1, rightIndex);
        merge(pArray, tmpA, leftIndex, middleIndex + 1, rightIndex);
    }
}
void SortFuncCompare::merge(ElementType *pArray, ElementType *tmpA,
                            int leftIndex, int middleIndex, int rightIndex) {
    int leftSubIndex = leftIndex;
    int rightSubIndex = middleIndex;
    int tmpIndex = leftIndex;
    // compare
    while (leftSubIndex < middleIndex && rightSubIndex <= rightIndex) {
        *(tmpA + tmpIndex++) = (*(pArray + leftSubIndex) COMPARE *(pArray + rightSubIndex)) ?
                               *(pArray + rightSubIndex++) : *(pArray + leftSubIndex++);
    }
    // copy the left rest (if remain)
    while (leftSubIndex < middleIndex) {
        *(tmpA + tmpIndex++) = *(pArray + leftSubIndex++);
    }
    // copy the right rest (if remain)
    while (rightSubIndex <= rightIndex) {
        *(tmpA + tmpIndex++) = *(pArray + rightSubIndex++);
    }
    // write the result from tmpA to pArray
    for (int i = leftIndex; i <= rightIndex; ++i) {
        *(pArray + i) = *(tmpA + i);
    }
}
```

## 3.7. 快速排序
时间复杂度:O(NlogN ~ N^2)，空间复杂度:O(1)，原地，非稳定
```c++
void SortFuncCompare::Quick_Sort(ElementType *pArray) {
//    cout << "Quick Sort" << endl;
    quickSort(pArray, 0, m_uiSizeOfArray - 1);
}
#define MIN_NUM_OF_CUTOFF 32 // when the length of subarray small than MIN_NUM_OF_CUTOFF, choose the insert sort
void SortFuncCompare::quickSort(ElementType *pArray, int leftIndex, int rightIndex) {
    if (rightIndex - leftIndex > MIN_NUM_OF_CUTOFF) {
        int i = leftIndex;
        int j = rightIndex - 1;
        // choose middle pivot
        ElementType middlePivot = choosePivot(pArray, leftIndex, rightIndex);
        while(true) {
            while (middlePivot COMPARE *(pArray + ++i)) {}
            while (*(pArray + --j) COMPARE middlePivot) {}
            if (i < j) {
                swapTwoNum(pArray + i, pArray + j);
            } else {
                break;
            }
        }
        // put the middle pivot into the middle index
        swapTwoNum(pArray + i, pArray + rightIndex - 1);
        quickSort(pArray, leftIndex, i - 1);
        quickSort(pArray, i + 1, rightIndex);
    } else {
        // Insert sort
        ElementType tmp;
        int j;
        for (int i = leftIndex + 1; i <= rightIndex; ++i) {
            tmp = *(pArray + i);
            for (j = i; j > leftIndex && *(pArray + j - 1) COMPARE tmp; --j) {
                *(pArray + j) = *(pArray + j - 1);
            }
            *(pArray + j) = tmp;
        }
    }
}
ElementType SortFuncCompare::choosePivot(ElementType *pArray, int leftIndex, int rightIndex) {
    int middleIndex = (leftIndex + rightIndex) / 2;
    if (*(pArray + leftIndex) COMPARE *(pArray + middleIndex)) {
        swapTwoNum(pArray + leftIndex, pArray + middleIndex);
    }
    if (*(pArray + leftIndex) COMPARE *(pArray + rightIndex)) {
        swapTwoNum(pArray + leftIndex, pArray + rightIndex);
    }
    if (*(pArray + middleIndex) COMPARE *(pArray + rightIndex)) {
        swapTwoNum(pArray + middleIndex, pArray + rightIndex);
    }
    swapTwoNum(pArray + middleIndex, pArray + rightIndex - 1);
    // return the middle value
    return *(pArray + rightIndex - 1);
}
```
# 4. 实验结果
各排序算法在各个数据规模下排序所耗时长（秒）。

数据规模|冒泡|选择|插入|希尔|堆|归并|快排
:----|:----|:----|:----|:----|:----|:----|:----
十| 2e-06| 1e-06| 1e-06| 1e-06| 2e-06| 1e-06| 1e-06
百| 3.3e-05| 3.3e-05| 8e-06| 8e-06| 1.1e-05| 1e-05| 5e-06
千| 0.003153| 0.003| 0.000627| 0.000164| 0.00016| 0.000118| 6.9e-05
万| 0.365065| 0.387825| 0.060752| 0.001938| 0.002096| 0.001431| 0.00089
十万| 38.2601| 35.2071| 7.63559| 0.034236| 0.031059| 0.019387| 0.01238
百万| 9708.16| 3736.74| 1643.99| 0.93| 0.98| 0.5| 0.3

## 4.1. 分析
### 4.1.1. 数据规模不超过一百时
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/SortFuncComparePicture_size100.png" class="full-image" />
当数据规模较小时，各排序算法所耗时长区别并不明显，但当数据规模为一百时已有明显区别，最快的排序算法与最满的排序算法效率相差一个数量级。

### 4.1.2. 数据规模为一千时
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/SortFuncComparePicture_size1000.png" class="full-image" />
除了冒泡和选择排序耗时三十几毫秒，其他排序算法耗时均在一毫秒内，此时各排序算法最快与最满效率比值已达为四十多倍

### 4.1.3. 数据规模为十万时
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/SortFuncComparePicture_size100000.png" class="full-image" />
当排序数据规模达到十万时，可以发现排序最快的算法是快排仅12毫秒，效率是最慢的冒泡排序(38秒)的三千多倍，性能差异已十分明显。

### 4.1.4. 数据规模为百万时
当排序数据规模达到百万时，可以发现排序最快的算法是快排仅0.3秒，效率是最慢的冒泡排序(9708.16秒，约2.7小时)的三万多倍，性能差异已非常巨大。而且已知快排的平均时间复杂度为O(N*logN)，大胆推测当数据规模为千万级别时，快排算法在此平台下耗时仅需3秒多，而时间复杂度为O(N^2)的冒泡排序在此平台下预计耗时将达到11天，两种算法的效率有天壤之别。

### 4.1.5. 经过此次实验收获
- 各种排序算法在数规模小于一百时还没有太大差距，此时选实现较简单的就好
- 当数据达到一定规模后，不同算法执行效率差异巨大，此时追求算法效率显得十分重要

# 5. 附件
本次实验源代码详见博主的个人git仓库:
- [SortFuncCompare.h](https://github.com/EisenHao/Cpp_Learning/blob/master/SortFuncCompare.h)
- [SortFuncCompare.cpp](https://github.com/EisenHao/Cpp_Learning/blob/master/SortFuncCompare.cpp)
