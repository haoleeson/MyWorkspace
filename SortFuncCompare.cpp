/***
 * @describe 测试各排序算法对相同规模用例排序消耗时长
 * @date 2019-11-06
 * @coder eisenhao
 * @Character UTF-8
 */

#include "SortFuncCompare.h"

using namespace std;

int SortFuncCompare::m_uiSizeOfArray = 0;

/**
 * 构造函数
 */
SortFuncCompare::SortFuncCompare() {
    m_uiSizeOfArray = 10;        // 生成随机数组大小缺省值
    func[0] = Bubble_Sort;      // 1.冒泡排序
    func[1] = Selection_Sort;   // 2.选择排序
    func[2] = Insertion_Sort;   // 3.插入排序
    func[3] = Shell_Sort;       // 4.希尔排序
    func[4] = Heap_Sort;        // 5.堆排序
    func[5] = Merge_Sort;       // 6.归并排序
    func[6] = Quick_Sort;       // 7.快速排序
}

/**
 * 析构函数
 */
SortFuncCompare::~SortFuncCompare() {
    if (NULL != m_array)
        delete []m_array;
}

/**
 * 交换两数的值
 * @param num1
 * @param num2
 */
void SortFuncCompare::swapTwoNum(ElementType *num1, ElementType *num2) {
    *num1 ^= *num2;
    *num2 ^= *num1;
    *num1 ^= *num2;
}

/**
 * 生成随机数填充待排序数组
 * @param size 随机数大小
 */
void SortFuncCompare::refreshArray(unsigned int size) {
    if (NULL != m_array)
        delete []m_array;
    m_uiSizeOfArray = size;
    m_array = new ElementType[m_uiSizeOfArray];
    srand((int)time(NULL));  // Generate random seeds
    for (int i = 0; i < m_uiSizeOfArray; ++i) {
        *(m_array + i) = rand() % MAX_RAND_VALUE;
    }
}

/**
 * 打印数组
 */
void SortFuncCompare::showArray() {
    for (int i = 0; i < m_uiSizeOfArray; ++i) {
        std::cout << *(m_array + i) << " ";
        if (i % 10 == 9)
            std::cout << std::endl;
    }
}

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

/**
 * 测试函数
 */
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

/**
 * 冒泡排序
 * @describe 时间复杂度:O(N^2)，空间复杂度:O(1)，原地，稳定
 * @param pArray
 */
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

/**
 * 选择排序
 * @describe 时间复杂度:O(N^2)，空间复杂度:O(1)，原地，稳定
 * @param pArray
 */
void SortFuncCompare::Selection_Sort(ElementType *pArray) {
//    cout << "Selection Sort" << endl;
    for (int i = 0; i < m_uiSizeOfArray - 1; ++i) {
        for (int j = i + 1; j < m_uiSizeOfArray; ++j) {
            if (*(pArray + i) COMPARE *(pArray + j))
                swapTwoNum(pArray + i, pArray + j);
        }
    }
}

/**
 * 插入排序
 * @describe 时间复杂度:O(N^2)，空间复杂度:O(1)，原地，稳定
 * @param pArray
 */
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

/**
 * 希尔排序
 * @describe 时间复杂度:O(N^1.25 ～N^1.5)，空间复杂度:O(1)，原地，非稳定
 * @param pArray
 */
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

/**
 * 堆排序
 * @describe 时间复杂度:O(NlogN)，空间复杂度:O(1)，原地，非稳定
 * @param pArray
 */
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

/**
 * 归并排序
 * @describe 时间复杂度:O(NlogN), O(n)，非原地，非稳定
 * @param pArray
 */
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

/**
 * 快速排序
 * @describe 时间复杂度:O(N^2 ~ NlogN)，空间复杂度:O(1)，原地，非稳定
 * @param pArray
 */
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






