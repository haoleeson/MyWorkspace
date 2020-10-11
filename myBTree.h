/**
 * B树的数据结构设计与代码实现
 * author: EisenHao
 * date：2020/10/6.
 */

#ifndef __MYBTREE_H_
#define __MYBTREE_H_
#include <iostream>
using namespace std;

template<class KEY_TYPE, class VALUE_TYPE>
class BTree;

/**
 * B树节点类
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 */
template<class KEY_TYPE, class VALUE_TYPE>
class BTreeNode {
    friend class BTree<KEY_TYPE, VALUE_TYPE>;// 申明友元类
private:
    bool isLeaf;// 是否是叶子节点
    int keyNum;// 当前节点所含关键字个数
    BTreeNode<KEY_TYPE, VALUE_TYPE>* parent;// 父指针
    KEY_TYPE* keys;// 关键字数组
    union {
        VALUE_TYPE* valuePtrs;// 若为叶子节点，指向value的指针
        BTreeNode<KEY_TYPE, VALUE_TYPE>** childPtrs;// 子节点指针数组
    };
private:
    void fillValue(int keyIndex, KEY_TYPE key, void* valuePtr);// 填充值（需外部确保keyIndex有效）
    void fillValue(void* valuePtr);// 填充 valuePtrs[0] 或 childPtrs[0] 值
    void removeValue(int keyIndex);// 删除值
    int binarySearchKey(KEY_TYPE key);// 二分查询关键字数组中，第一个key[i] >= key对应的子节点可能所在下标 i
public:
    BTreeNode(int maxKeyNum, bool isLeaf = true);
    ~BTreeNode();
    bool containKey(KEY_TYPE key);// 查询key是否存在
    VALUE_TYPE getValue(KEY_TYPE key);// 获取key的value值，无则返回nullptr
    void print();// 节点打印
};

/**
 * B树管理类
 * @tparam KEY_TYPE
 */
template<class KEY_TYPE, class VALUE_TYPE>
class BTree {
private:
    int m;// m阶，┌m/2┐ - 1 <= j <= m - 1
    int maxKeyNum;// 最多关键字个数 =  m - 1;
    int minKeyNum;// 最少关键字个数 = ┌m/2┐ - 1 = (m - 1) / 2 == maxKeyNum / 2
    BTreeNode<KEY_TYPE, VALUE_TYPE>* root;
private:
    bool appointInsert(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, KEY_TYPE key, void* valuePtr);// 指定节点的插入操作
    bool appointSplitInsert(BTreeNode<KEY_TYPE, VALUE_TYPE>*splitNode, KEY_TYPE key, void* valuePtr);// 指定已满节点的分裂插入操作
    bool appointNotFullInsert(BTreeNode<KEY_TYPE, VALUE_TYPE>*InsertNode, KEY_TYPE key, void* valuePtr);// 指定未满节点的插入操作
public:
    BTree(int m = 3);
    ~BTree();
    bool insert(KEY_TYPE key, VALUE_TYPE value);// 插入<key, value>
    bool remove(KEY_TYPE key);// 从B树中删除<key, value>（若存在）
    VALUE_TYPE getValue(KEY_TYPE key);// 获取key的value值，无则返回nullptr
    void print();// 打印B树
};


/***********************************  下方为实现部分 ***********************************/

/**
 * B树节点类，构造函数
 * @tparam KEY_TYPE
 * @param maxKeyNum
 */
template<class KEY_TYPE, class VALUE_TYPE>
BTreeNode<KEY_TYPE, VALUE_TYPE>::BTreeNode(int maxKeyNum, bool isLeaf) :isLeaf(isLeaf), keyNum(0), parent(nullptr) {
    keys = new KEY_TYPE[maxKeyNum];
    if (isLeaf) {
        valuePtrs = new VALUE_TYPE[maxKeyNum + 1];
    } else {
        childPtrs = new BTreeNode<KEY_TYPE, VALUE_TYPE>*[maxKeyNum + 1]{nullptr};
    }
}

/**
 * B树节点类，析构函数
 * @tparam KEY_TYPE
 */
template<class KEY_TYPE, class VALUE_TYPE>
BTreeNode<KEY_TYPE, VALUE_TYPE>::~BTreeNode() {
    delete []keys;
    if (isLeaf) {
        delete []valuePtrs;
    } else {
        // 清理释放子节点
        for (int i = 0; i < keyNum + 1; ++i) {
            if (childPtrs[i] != nullptr) {
                delete childPtrs[i];
            }
        }
        delete []childPtrs;
    }
}

/**
 * 二分查询关键字数组中，第一个key[i] >= key对应的子节点可能所在下标 i
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param key
 * @return i -- 可能的子节点下标
 */
template<class KEY_TYPE, class VALUE_TYPE>
int BTreeNode<KEY_TYPE, VALUE_TYPE>::binarySearchKey(KEY_TYPE key) {
    int left = 0, right = keyNum - 1, mid = (left + right) / 2;
    while (left < right && keys[mid] != key) {
        if (keys[mid] > key) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
        mid = (left + right) / 2;
    }
    return key > keys[mid] ? mid + 1 : mid;
}

/**
 * 查询以当前节点为根的BTree子树中，是否存在键 key
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param key
 * @return true -- 存在key； false -- 不存在key
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTreeNode<KEY_TYPE, VALUE_TYPE>::containKey(KEY_TYPE key) {
    int i = binarySearchKey(key);
    if (i < keyNum && keys[i] == key) {
        return true;
    }
    return isLeaf ? false : childPtrs[i]->containKey(key);
}

/**
 * 查询以当前节点为根的BTree子树中，是否已经存在 Key，若存在返回其value指针
 * @tparam KEY_TYPE
 * @param key
 * @return nullptr -- 未找到; others -- 其value指针
 */
template<class KEY_TYPE, class VALUE_TYPE>
VALUE_TYPE BTreeNode<KEY_TYPE, VALUE_TYPE>::getValue(KEY_TYPE key) {
    int i = binarySearchKey(key);
    if (i < keyNum && keys[i] == key) {
        // 若是叶子节点，则返回value指针，否则继续下落到叶子节点
        if (isLeaf) {
            return valuePtrs[i + 1];
        }
        BTreeNode<KEY_TYPE, VALUE_TYPE>* ptr = childPtrs[i + 1];
        while (!ptr->isLeaf) {
            ptr = ptr->childPtrs[0];
        }
        return ptr->valuePtrs[0];
    }
    return isLeaf ? nullptr : childPtrs[i]->getValue(key);
}

template<class KEY_TYPE, class VALUE_TYPE>
void BTreeNode<KEY_TYPE, VALUE_TYPE>::print() {
    // 第几层节点打印几个TAB
    for (BTreeNode<KEY_TYPE, VALUE_TYPE>* ptr = this->parent; ptr != nullptr; ptr = ptr->parent) {
        cout << "    ";
    }
    cout << "{" << "isLeaf:" << isLeaf << ", keyNum:" << keyNum << ", key:[";
    if (keyNum > 0) {
        cout << keys[0];
        for (int i = 1; i < keyNum; ++i) {
            cout << "," << keys[i];
        }
    }
    cout << "], ";
    if (isLeaf) {
        cout << "valuePtrs:[";
        if (keyNum >= 0) {
            cout << valuePtrs[0];
            for (int i = 1; i <= keyNum; ++i) {
                cout << "," << valuePtrs[i];
            }
        }
    } else {
        cout << "childPtrs:[" << endl;
        for (int i = 0; i < keyNum + 1; ++i) {
            if (childPtrs[i] != nullptr) {
                childPtrs[i]->print();
            }
        }
        // 第几层节点打印几个TAB
        for (BTreeNode<KEY_TYPE, VALUE_TYPE>* ptr = this->parent; ptr != nullptr; ptr = ptr->parent) {
            cout << "    ";
        }
    }
    cout << "]}" << endl;
}

/**
 * 填充值（需外部确保 keyIndex 有效）
 */
template<class KEY_TYPE, class VALUE_TYPE>
void BTreeNode<KEY_TYPE, VALUE_TYPE>::fillValue(int keyIndex, KEY_TYPE key, void* valuePtr) {
    keys[keyIndex] = key;
    if (isLeaf) {
        valuePtrs[keyIndex + 1] = (VALUE_TYPE)valuePtr;
    } else {
        childPtrs[keyIndex + 1] = (BTreeNode<KEY_TYPE, VALUE_TYPE>*)valuePtr;
        childPtrs[keyIndex + 1]->parent = this;
    }
}

/**
 * 填充value[0]值
 */
template<class KEY_TYPE, class VALUE_TYPE>
void BTreeNode<KEY_TYPE, VALUE_TYPE>::fillValue(void *valuePtr) {
    if (isLeaf) {
        valuePtrs[0] = (VALUE_TYPE)valuePtr;
    } else {
        childPtrs[0] = (BTreeNode<KEY_TYPE, VALUE_TYPE>*)valuePtr;
        childPtrs[0]->parent = this;
    }
}

/**
 * 删除值
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param keyIndex 有效范围 [-1, keyNum)
 */
template<class KEY_TYPE, class VALUE_TYPE>
void BTreeNode<KEY_TYPE, VALUE_TYPE>::removeValue(int keyIndex) {
    // keyIndex不合法直接返回；或当 keyIndex == -1 且 keyNum == 0 时，需删除节点，无需执行以下操作
    if (keyIndex < -1 || keyIndex >= keyNum || keyNum == 0) {
        return;
    }
    // 删除 valuePtr[keyIndex + 1] 或 childPtrs[keyIndex + 1]，前挪
    if (isLeaf) {
        for (int i = keyIndex + 1; i < keyNum; ++i) {
            valuePtrs[i] = valuePtrs[i + 1];
        }
    } else {
        for (int i = keyIndex + 1; i < keyNum; ++i) {
            childPtrs[i] = childPtrs[i + 1];
        }
    }
    // 删除 keys[keyIndex]，keyIndex == -1 时等价于删除keys[0]
    if (keyIndex == -1) {
        keyIndex = 0;
    }
    --keyNum;
    for (int i = keyIndex; i < keyNum; ++i) {
        keys[i] = keys[i + 1];
    }
}

/**
 * B树管理类，构造函数
 * @tparam KEY_TYPE
 */
template<class KEY_TYPE, class VALUE_TYPE>
BTree<KEY_TYPE, VALUE_TYPE>::BTree(int m) : m(m), maxKeyNum(m - 1), minKeyNum((m - 1) / 2) {
    // 实例化空树根节点（也是叶子节点）
    root = new BTreeNode<KEY_TYPE, VALUE_TYPE>(maxKeyNum);
    cout << "create a BTree, which max Key num = " << maxKeyNum << endl;
}

/**
 * B树管理类，析构函数
 * @tparam KEY_TYPE
 */
template<class KEY_TYPE, class VALUE_TYPE>
BTree<KEY_TYPE, VALUE_TYPE>::~BTree() {
    if (root) {
        delete root;
    }
}

/**
 * 指定节点的插入操作
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param node
 * @param key
 * @param valuePtr
 * @return
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::appointInsert(BTreeNode<KEY_TYPE, VALUE_TYPE> *node, KEY_TYPE key, void *valuePtr) {
    if (node->keyNum < maxKeyNum) {
        return appointNotFullInsert(node, key, valuePtr);
    } else if (node->keyNum == maxKeyNum) {
        return appointSplitInsert(node, key, valuePtr);
    }
    return false;
}

/**
 * 指定节点的已满分裂插入
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param splitNode 待分裂节点(keyNum == maxKeyNum)
 * @param key
 * @param valuePtr
 * @return
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::appointSplitInsert(BTreeNode<KEY_TYPE, VALUE_TYPE> *splitNode,
                                                     KEY_TYPE key, void *valuePtr) {
    // 若待分裂节点未满，不进行分裂插入操作
    if (splitNode->keyNum != maxKeyNum) {
        return false;
    }
    // 查询新key应插入位置
    int midIndex = maxKeyNum - minKeyNum, insertIndex = splitNode->binarySearchKey(key);
    // 新增右兄弟节点
    BTreeNode<KEY_TYPE, VALUE_TYPE>* rightBrotherPtr = new BTreeNode<KEY_TYPE, VALUE_TYPE>(maxKeyNum, splitNode->isLeaf);
    // 拷贝后半部分到右兄弟节点
    KEY_TYPE rightBrotherKey, tmpKey;
    void* tmpValue;
    // 模拟超载1位已经插入<key, valuePtr>后的，<tmpKey, tmpValue>队列
    for (int i = maxKeyNum; i >= min(insertIndex, midIndex); --i) {
        if (i > insertIndex) {
            tmpKey = splitNode->keys[i - 1];
            tmpValue = splitNode->isLeaf ? (void*)(splitNode->valuePtrs[i]) : (void*)(splitNode->childPtrs[i]);
        } else if (i < insertIndex) {
            tmpKey = splitNode->keys[i];
            tmpValue = splitNode->isLeaf ? (void*)(splitNode->valuePtrs[i + 1]) : (void*)(splitNode->childPtrs[i + 1]);
        } else {
            tmpKey = key;
            tmpValue = valuePtr;
        }
        // 1. 将后半部分挪到右兄弟节点
        if (i > midIndex) {
            rightBrotherPtr->fillValue(i - midIndex - 1, tmpKey, tmpValue);
        } else if (i == midIndex) {
            rightBrotherKey = tmpKey;// 记录右兄弟节点对应的Key值
            rightBrotherPtr->fillValue(tmpValue);
        } else {
            // 若 insertIndex <= i < midIndex 前半部分也许做插入<key, valuePtr>后的改动（如有需要）
            splitNode->fillValue(i, tmpKey, tmpValue);
        }
    }
    // 刷新分裂后两兄弟节点的key数值
    rightBrotherPtr->keyNum = minKeyNum;
    splitNode->keyNum = maxKeyNum - minKeyNum;
    // 特殊处理 (指定节点的待分裂插入节点无父节点，则需新增root节点)
    if (splitNode->parent == nullptr) {
        BTreeNode<KEY_TYPE, VALUE_TYPE>* newRoot = new BTreeNode<KEY_TYPE, VALUE_TYPE>(maxKeyNum, false);
        newRoot->fillValue(splitNode);// 将原root指针填充到newRoot->childPtrs[0]
        root = newRoot;// 更新root记录值
    }
    // 再将新增的右兄弟节点和其对应的Key值: <rightBrotherKey, rightBrotherPtr>，插入共同的父节点
    return appointInsert(splitNode->parent, rightBrotherKey, rightBrotherPtr);
}

/**
 * 指定节点的未满插入
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param InsertNode
 * @param key
 * @param valuePtr
 * @return
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::appointNotFullInsert(BTreeNode<KEY_TYPE, VALUE_TYPE>* InsertNode,
                                                       KEY_TYPE key, void *valuePtr) {
    // 若待插入节点已满，则无法进行未满插入操作
    if (InsertNode->keyNum >= maxKeyNum) {
        return false;
    }
    int i = InsertNode->binarySearchKey(key);
    // 先将keys中下标i及之后的key向后挪一个位置
    ++InsertNode->keyNum;
    for (int j = InsertNode->keyNum - 1; j > i; --j) {
        InsertNode->keys[j] = InsertNode->keys[j - 1];
        InsertNode->valuePtrs[j + 1] = InsertNode->valuePtrs[j];
    }
    // 在i处填充<key, valuePtr>的值
    InsertNode->fillValue(i, key, valuePtr);
    return true;
}

/**
 * B数管理类，插入 <key, value>
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param key
 * @param value
 * @return
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::insert(KEY_TYPE key, VALUE_TYPE value) {
    int i;
    BTreeNode<KEY_TYPE, VALUE_TYPE>* ptr = root;
    while (true) {
        i = ptr->binarySearchKey(key);
        // 若key已存在，替换更新value
        if (i < ptr->keyNum && ptr->keys[i] == key) {
            // 若是叶子节点，替换value指针
            if (ptr->isLeaf) {
                ptr->valuePtrs[i + 1] = value;
                return true;
            }
            // 非叶子节点, 继续下落到叶子节点再替换value指针
            ptr = ptr->childPtrs[i + 1];
            while (!ptr->isLeaf) {
                ptr = ptr->childPtrs[0];
            }
            ptr->valuePtrs[0] = value;
            return true;
        }
        // 若是叶子节点，执行后续插入操作
        if (ptr->isLeaf) {
            break;
        }
        // 若非叶子节点，继续向下寻找插入位置
        ptr = ptr->childPtrs[i];
    }
    // 指定节点的插入操作
    return appointInsert(ptr, key, value);
}

template<class KEY_TYPE, class VALUE_TYPE>
void BTree<KEY_TYPE, VALUE_TYPE>::print() {
    root->print();
}

template<class KEY_TYPE, class VALUE_TYPE>
VALUE_TYPE BTree<KEY_TYPE, VALUE_TYPE>::getValue(KEY_TYPE key) {
    return root->getValue(key);
}

/**
 * 从B树中删除<key, value>（若存在）
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param key
 * @return true -- 删除成功； false -- 不存在 / 删除失败
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::remove(KEY_TYPE key) {
    int i;
    BTreeNode<KEY_TYPE, VALUE_TYPE>* ptr = root;
    while (true) {
        i = ptr->binarySearchKey(key);
        if (i < ptr->keyNum && ptr->keys[i] == key) {
            // 若此节点是叶子节点，直接删除
            if (ptr->isLeaf) {
                ptr->removeValue(i);
                return true;
            }
            // 若此节点非叶子节点, 继续下落到叶子节点
            KEY_TYPE* recordKey = &ptr->keys[i];
            BTreeNode<KEY_TYPE, VALUE_TYPE>* childPtr = ptr->childPtrs[i + 1];
            while (childPtr->keyNum > 0) {
                i = -1;
                ptr = childPtr;
                if (ptr->isLeaf) {
                    break;
                }
                childPtr = childPtr->childPtrs[0];
            }
            if (childPtr && childPtr->keyNum == 0) {
                delete childPtr;
            }
            *recordKey = ptr->keys[i + 1];
            ptr->removeValue(i);
            return true;
        }
        // 若是叶子节点，说明不存在该key，则返回false
        if (ptr->isLeaf) {
            break;
        }
        // 若非叶子节点，继续向下寻找待删除的key
        ptr = ptr->childPtrs[i];
    }
    return false;
}

#endif //__MYBTREE_H_
