/**
 * B树的数据结构设计与代码实现
 * @description 特点：
 * 1. 采用面向对象设计思路，可自定义每个 BTree 对象的阶数 m
 * 2. 采用模板类设计，可在实例化时自定义 <KEY_TYPE, VALUE_TYPE> 类型
 * 3. 支持二分法查找关键字数组
 * 4. BTree 对象，支持：新增(或改值)、删除、查询、结构化打印 Btree 的<key, value>内容
 * author: EisenHao
 * date：2020/10/15.
 */

#ifndef __MYBTREE_H_
#define __MYBTREE_H_
#include <iostream>
#include <string>
#include <sstream>
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
        VALUE_TYPE* valuePtrs;// 若为叶子节点，指向value的指针数组
        BTreeNode<KEY_TYPE, VALUE_TYPE>** childPtrs;// 子节点指针数组
    };
private:
    void fillValue(void* valuePtr);// 填充 valuePtrs[0] 或 childPtrs[0] 值
    void fillValue(int keyIndex, KEY_TYPE key, void* valuePtr);// 填充值（需外部确保keyIndex有效）
    void insert0Value(KEY_TYPE key0, void* valuePtr0);// 插入 keys[0] 和 childPtrs[0] 的值，其他key后挪
    void removeValue(int keyIndex);// 删除值
    int binarySearchKey(KEY_TYPE key);// 二分查询关键字数组中，第一个key[i] >= key对应的子节点可能所在下标 i
public:
    BTreeNode(int maxKeyNum, bool isLeaf = true);
    ~BTreeNode();
    bool containKey(KEY_TYPE key);// 查询key是否存在
    VALUE_TYPE getValue(KEY_TYPE key);// 获取key的value值，无则返回nullptr
    string toString();// 节点打印
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
    BTreeNode<KEY_TYPE, VALUE_TYPE>* root; // 根节点
private:
    bool appointNotFullInsert(BTreeNode<KEY_TYPE, VALUE_TYPE>*InsertNode, KEY_TYPE key, void* valuePtr);// 指定未满节点的插入操作
    bool appointSplitInsert(BTreeNode<KEY_TYPE, VALUE_TYPE>*splitNode, KEY_TYPE key, void* valuePtr);// 指定已满节点的分裂插入操作
    bool appointInsert(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, KEY_TYPE key, void* valuePtr);// 指定节点的插入操作
    bool appointRemove(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, KEY_TYPE& recordKey, int deleteKeyIndex, int childOrder);// 指定节点的删除操作
    bool browFromLeftBro(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, int childOrder);// 右旋：从左兄弟节点挪一个关键字到node节点（以维持node节点平衡）
    bool browFromRightBro(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, int childOrder);// 左旋：从右兄弟节点挪一个关键字到node节点（以维持node节点平衡）
    bool browFromBro(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, int childOrder);// 旋转，若左右兄弟存在，则间接向左右兄弟借关键码
    bool reduceLevel(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, int childOrder);// 降层处理
    bool mergeTwoContChild(BTreeNode<KEY_TYPE, VALUE_TYPE>*parent, int firstChildOrder);// 合并两个连续的子节点
    bool mergeWithBro(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, int childOrder);// 与左兄弟节点 或 右兄弟节点合并
    bool removeBalance(BTreeNode<KEY_TYPE, VALUE_TYPE>*node, int childOrder);// 维持 node 节点平衡
public:
    BTree(int m = 3);
    ~BTree();
    bool containKey(KEY_TYPE key);// 查询key是否存在
    VALUE_TYPE getValue(KEY_TYPE key);// 获取key的value值，无则返回nullptr
    void print();// 打印B树
    bool insert(KEY_TYPE key, VALUE_TYPE value);// 插入<key, value>
    bool remove(KEY_TYPE key);// 从B树中删除<key, value>（若存在）
};



/***********************************  下方为 BTreeNode 类函数实现部分 ***********************************/
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
 * 插入 key[0] 和 childPtrs[0] 的值，其他key后挪
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param key0
 * @param valuePtr0
 */
template<class KEY_TYPE, class VALUE_TYPE>
void BTreeNode<KEY_TYPE, VALUE_TYPE>::insert0Value(KEY_TYPE key0, void *valuePtr0) {
    for (int i = keyNum; i > 0; --i) {
        keys[i] = keys[i - 1];
    }
    keys[0] = key0;
    ++keyNum;
    if (isLeaf) {
        for (int i = keyNum; i > 0; --i) {
            valuePtrs[i] = valuePtrs[i - 1];
        }
        valuePtrs[0] = (VALUE_TYPE)valuePtr0;
    } else {
        for (int i = keyNum; i > 0; --i) {
            childPtrs[i] = childPtrs[i - 1];
        }
        childPtrs[0] = (BTreeNode<KEY_TYPE, VALUE_TYPE>*)valuePtr0;
        childPtrs[0]->parent = this;
    }
}

/**
 * 删除值
 * @describe 若非叶子节点，会释放 childPtrs[keyIndex + 1] 内存
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
    // 删除 valuePtr[keyIndex + 1] 或 childPtrs[keyIndex + 1]，其他前挪
    if (isLeaf) {
        for (int i = keyIndex + 1; i < keyNum; ++i) {
            valuePtrs[i] = valuePtrs[i + 1];
        }
    } else {
        if (childPtrs[keyIndex + 1]) {
            delete childPtrs[keyIndex + 1];
        }
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
 * 二分查询关键字数组中，第一个keys[i] >= key对应的子节点可能所在下标 i
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param key
 * @return i -- 可能的子节点下标
 */
template<class KEY_TYPE, class VALUE_TYPE>
int BTreeNode<KEY_TYPE, VALUE_TYPE>::binarySearchKey(KEY_TYPE key) {
    if (keyNum <= 0) {
        return 0;
    }
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
    // 若是叶子节点（未找到），返回false；若非叶子节点，继续向下寻找
    return isLeaf ? false : childPtrs[i]->containKey(key);
}

/**
 * 查询以当前节点为根的BTree子树中，是否已经存在 Key，若存在返回其value指针
 * @tparam KEY_TYPE
 * @param key
 * @return nullptr -- 未找到key; others -- 其value指针
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
    // 若是叶子节点（未找到），返回nullptr；若非叶子节点，继续向下寻找
    return isLeaf ? nullptr : childPtrs[i]->getValue(key);
}

/**
 * toString
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @return
 */
template<class KEY_TYPE, class VALUE_TYPE>
string BTreeNode<KEY_TYPE, VALUE_TYPE>::toString() {
    stringstream ss;
    // 第几层节点打印几个TAB
    for (BTreeNode<KEY_TYPE, VALUE_TYPE>* ptr = this->parent; ptr != nullptr; ptr = ptr->parent) {
        ss << "    ";
    }
    ss << "{" << "isLeaf:" << isLeaf << ", keyNum:" << keyNum << ", key:[";
    if (keyNum > 0) {
        ss << keys[0];
        for (int i = 1; i < keyNum; ++i) {
            ss << "," << keys[i];
        }
    }
    ss << "], ";
    if (isLeaf) {
        ss << "valuePtrs:[";
        if (keyNum >= 0) {
            ss << valuePtrs[0];
            for (int i = 1; i <= keyNum; ++i) {
                ss << "," << valuePtrs[i];
            }
        }
    } else {
        ss << "childPtrs:[\n";
        for (int i = 0; i < keyNum + 1; ++i) {
            if (childPtrs[i] != nullptr) {
                ss << childPtrs[i]->toString();
            }
        }
        // 第几层节点打印几个TAB
        for (BTreeNode<KEY_TYPE, VALUE_TYPE>* ptr = this->parent; ptr != nullptr; ptr = ptr->parent) {
            ss << "    ";
        }
    }
    ss << "]}\n";
    return ss.str();
}
/***********************************  上方为 BTreeNode 类函数实现部分 ***********************************/


/***********************************  下方为 BTree 类函数实现部分 ***********************************/
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
 * 指定节点的删除操作
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param node
 * @param recordKey
 * @param deleteKeyIndex 待删除 key 所在下标
 * @param childOrder 是父节点的第几个孩子
 * @return true -- 删除成功；false -- 删除后本层为空，还需递归上层删除
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::appointRemove(BTreeNode<KEY_TYPE, VALUE_TYPE> *node, KEY_TYPE& recordKey,
                                                int deleteKeyIndex, int childOrder) {
    // 若此节点非叶子节点, 继续下落到叶子节点执行删除（若返回结果值为false，还需递归上层删除）
    if (!node->isLeaf) {
        if (appointRemove(node->childPtrs[deleteKeyIndex + 1], recordKey, -1, deleteKeyIndex + 1)) {
            return true;
        }
    }
    // 若无 key 关键字，说明此节点仅有recordKey对应的valuePtr，删除整个节点为空（需释放）
    if (node->keyNum <= 0) {
        // 若父节点非空，（若父节点为空，说明此node是root节点，不能删除）
        if (node->parent) {
            node->parent->childPtrs[childOrder] = nullptr;// 清除父节点指向node指针的值
            delete node;// 释放node节点
        }
        return false;// 返回false，还需递归上层删除
    }
    // 若有其他 key 关键字，截取下一个key以更新recordKey
    if (deleteKeyIndex + 1 < node->keyNum) {
        recordKey = node->keys[deleteKeyIndex + 1];
    }
    // 删除 node 节点下标为 deleteKeyIndex 对应的<key, value>
    node->removeValue(deleteKeyIndex);
    // 维持node节点删除节点之后的平衡
    removeBalance(node, childOrder);
    return true;
}

/**
 * 右旋：从左兄弟节点挪一个关键字到node节点（以维持node节点平衡）
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param node 待平衡节点
 * @param childOrder 属于父节点的第几个子节点
 * @return false -- 挪借失败；true -- 挪借成功
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::browFromLeftBro(BTreeNode<KEY_TYPE, VALUE_TYPE> *node, int childOrder) {
    // 父节点不存在，返回false
    BTreeNode<KEY_TYPE, VALUE_TYPE>* parent = node->parent;
    if (!parent) {
        return false;
    }
    BTreeNode<KEY_TYPE, VALUE_TYPE>* leftBroPtr = childOrder <= 0 ? nullptr : parent->childPtrs[childOrder - 1];
    // 不存在左兄弟节点 或 左兄弟节点节点无法挪借关键字，则返回false
    if (!leftBroPtr || leftBroPtr->keyNum <= minKeyNum) {
        return false;
    }
    // 将父节点的keys[childOrder - 1]关键字 和 左兄弟节点最后一个关键字指向的指针 --> 挪到本节点
    void* tmpValue = leftBroPtr->isLeaf ? (void*)(leftBroPtr->valuePtrs[leftBroPtr->keyNum])
                                        : (void*)(leftBroPtr->childPtrs[leftBroPtr->keyNum]);
    node->insert0Value(parent->keys[childOrder - 1], tmpValue);
    // 将左兄弟节点最后一个关键字，填充到父节点的 keys[childOrder - 1]
    parent->keys[childOrder - 1] = leftBroPtr->keys[leftBroPtr->keyNum - 1];
    // 更新左兄弟节点关键字数
    --leftBroPtr->keyNum;
    return true;
}

/**
 * 左旋：从右兄弟节点挪一个关键字到node节点（以维持node节点平衡）
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param node 待平衡节点
 * @param childOrder 属于父节点的第几个子节点
 * @return false -- 挪借失败；true -- 挪借成功
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::browFromRightBro(BTreeNode<KEY_TYPE, VALUE_TYPE> *node, int childOrder) {
    // 父节点不存在，返回false
    BTreeNode<KEY_TYPE, VALUE_TYPE>* parent = node->parent;
    if (!parent) {
        return false;
    }
    BTreeNode<KEY_TYPE, VALUE_TYPE>* rightBroPtr = childOrder >= parent->keyNum ? nullptr : parent->childPtrs[childOrder + 1];
    // 不存在右兄弟节点节点 或 右兄弟节点节点无法挪借关键字，则返回false
    if (!rightBroPtr || rightBroPtr->keyNum <= minKeyNum) {
        return false;
    }
    // 将父节点的keys[childOrder]关键字 和 右兄弟节点第0个子指针 --> 挪到本节点末尾
    void* tmpValue;
    if (rightBroPtr->isLeaf) {
        tmpValue = (void*)(rightBroPtr->valuePtrs[0]);
    } else {
        tmpValue = (void*)(rightBroPtr->childPtrs[0]);
        rightBroPtr->childPtrs[0] = nullptr;
    }
    node->fillValue(node->keyNum, parent->keys[childOrder], tmpValue);
    // 将右兄弟节点的第一个关键字，填充到父节点的 keys[childOrder]
    parent->keys[childOrder] = rightBroPtr->keys[0];
    // 删除右兄弟节点的keys[0] 和 childPtrs[0] 的值，其他key前挪
    rightBroPtr->removeValue(-1);
    // 更新本节点关键字数
    ++node->keyNum;
    return true;
}

/**
 * 旋转：从左（或右）兄弟节点挪一个关键字到node节点（以维持node节点平衡）
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param node
 * @param childOrder 是父节点的第几个孩子
 * @return false -- 挪借失败；true -- 挪借成功
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::browFromBro(BTreeNode<KEY_TYPE, VALUE_TYPE> *node, int childOrder) {
    BTreeNode<KEY_TYPE, VALUE_TYPE>* parent = node->parent;
    if (!parent) {
        return false;
    }
    // 可从左右节点挪借的关键字数
    int fromLeft = 0, fromRight = 0;
    BTreeNode<KEY_TYPE, VALUE_TYPE>* leftBroPtr = childOrder <= 0 ? nullptr : parent->childPtrs[childOrder - 1];
    // 若存在左兄弟节点 且 左兄弟节点关键字字数大于 minKeyNum，则可从左兄弟挪借关键字
    if (leftBroPtr && leftBroPtr->keyNum > minKeyNum) {
        fromLeft = leftBroPtr->keyNum - minKeyNum;
    }
    BTreeNode<KEY_TYPE, VALUE_TYPE>* rightBroPtr = childOrder >= parent->keyNum ? nullptr : parent->childPtrs[childOrder + 1];
    // 若存在右兄弟节点 且 右兄弟节点关键字字数大于 minKeyNum，则可从右兄弟挪借关键字
    if (rightBroPtr && rightBroPtr->keyNum > minKeyNum) {
        fromRight = rightBroPtr->keyNum - minKeyNum;
    }
    // 左右兄弟节点可挪借关键字数均为0，返回false
    if (fromLeft == 0 && fromRight == 0) {
        return false;
    }
    // 选取左右兄弟节点中，关键字数较多的一方挪借（相等则优先从右节点挪借）
    return fromLeft > fromRight ? browFromLeftBro(node, childOrder) : browFromRightBro(node, childOrder);
}

/**
 * 降层处理
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param node 待删除层
 * @param childOrder 是父节点的第几个孩子
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::reduceLevel(BTreeNode<KEY_TYPE, VALUE_TYPE> *node, int childOrder) {
    // node 为空，或关键字数大于0，或为叶子节点，不进行降层
    if (!node || node->keyNum > 0 || node->isLeaf) {
        return false;
    }
    // 若父节点非空
    if (node->parent) {
        // 若其兄弟节点与其node->childPtrs[0] 是否是叶子节点属性不同，则不降层
        for (int i = 0; i < node->parent->keyNum + 1; ++i) {
            if (node->parent->childPtrs[i]->isLeaf != node->childPtrs[0]->isLeaf) {
                return false;
            }
        }
        // 降层处理
        node->parent->childPtrs[childOrder] = node->childPtrs[0];
        node->childPtrs[0] = nullptr;
        delete node;// 释放node节点
        return true;
    } else if (node == root) {
        // 若父节点为空，但为根节点
        root = node->childPtrs[0];// 更新root节点
        root->parent = nullptr;
        node->childPtrs[0] = nullptr;// 清除父节点指向node指针的值
        delete node;// 释放node节点
        return true;
    }
    return false;
}

/**
 * 合并两个连续的子节点（合并到第一个节点，删除第二个节点）
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param parent 父节点
 * @param firstChildOrder 两个连续节点中首节点属于父节点的第几个子节点
 * @return false -- 右连续的兄弟节点不存在 或 即使合并后任然不平衡；true -- 合并成功
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::mergeTwoContChild(BTreeNode<KEY_TYPE, VALUE_TYPE> *parent, int firstChildOrder) {
    // 父节点不存在 或 不存在左、右连续的兄弟节点，返回false
    if (!parent || firstChildOrder < 0 || firstChildOrder >= parent->keyNum) {
        return false;
    }
    BTreeNode<KEY_TYPE, VALUE_TYPE>* leftBroPtr = parent->childPtrs[firstChildOrder];
    BTreeNode<KEY_TYPE, VALUE_TYPE>* rightBroPtr = parent->childPtrs[firstChildOrder + 1];
    // 左兄弟节点节点关键字 + 右兄弟节点关键字 + 1 > 最大关键字数，则返回false
    if (leftBroPtr->keyNum + rightBroPtr->keyNum + 1 > maxKeyNum) {
        return false;
    }
    // 将父节点的keys[firstChildOrder]关键字 和 右兄弟节点的第0个子指针 --> 挪到左兄弟节点后部
    void* tmpValue = rightBroPtr->isLeaf ? (void*)(rightBroPtr->valuePtrs[0]) : (void*)(rightBroPtr->childPtrs[0]);
    leftBroPtr->fillValue(leftBroPtr->keyNum, parent->keys[firstChildOrder], tmpValue);
    ++leftBroPtr->keyNum;
    // 再将右兄弟节点的其余 rightBroPtr->keyNum 个<key, valuePtr> 挪到左兄弟节点后部
    if (rightBroPtr->isLeaf) {
        for (int i = 0; i < rightBroPtr->keyNum; ++i) {
            leftBroPtr->fillValue(leftBroPtr->keyNum + i, rightBroPtr->keys[i], rightBroPtr->valuePtrs[i + 1]);
        }
    } else {
        for (int i = 0; i < rightBroPtr->keyNum; ++i) {
            leftBroPtr->fillValue(leftBroPtr->keyNum + i, rightBroPtr->keys[i], rightBroPtr->childPtrs[i + 1]);
        }
        rightBroPtr->childPtrs[0] = nullptr;// 右兄弟节点的第0个子指针置null，防止后续释放node内存时误删
    }
    // 更新左兄弟节点与右兄弟节点关键字数
    leftBroPtr->keyNum += rightBroPtr->keyNum;
    rightBroPtr->keyNum = 0;
    // 父节点删除右兄弟节点<key, value>记录值
    parent->removeValue(firstChildOrder);
    // 可能导致parent->keyNum = 0，降层处理
    if (parent->keyNum == 0 && parent == root && !parent->isLeaf) {
        reduceLevel(parent, 0);
    }
    return true;
}

/**
 * 与左兄弟节点 或 右兄弟节点合并
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param node 待合并节点
 * @param childOrder 属于父节点的第几个子节点
 * @return false -- 右兄弟节点不存在 或 即使合并后任然不平衡；true -- 合并成功
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::mergeWithBro(BTreeNode<KEY_TYPE, VALUE_TYPE> *node, int childOrder) {
    BTreeNode<KEY_TYPE, VALUE_TYPE>* parent = node->parent;
    if (!parent) {
        return false;
    }
    // 左、右兄弟节点的可合并的关键字数
    int fromLeft = INT32_MAX, fromRight = INT32_MAX;
    BTreeNode<KEY_TYPE, VALUE_TYPE>* leftBroPtr = childOrder <= 0 ? nullptr : parent->childPtrs[childOrder - 1];
    // 若存在左兄弟节点，且左兄弟节点关键字 + 本节点关键字 + 1 <= 最大关键字数，则可与左兄弟节点合并
    if (leftBroPtr && leftBroPtr->keyNum + node->keyNum + 1 <= maxKeyNum) {
        fromLeft = leftBroPtr->keyNum;
    }
    BTreeNode<KEY_TYPE, VALUE_TYPE>* rightBroPtr = childOrder >= parent->keyNum ? nullptr : parent->childPtrs[childOrder + 1];
    // 若存在右兄弟节点，且右兄弟节点关键字 + 本节点关键字 + 1 <= 最大关键字数，则可与右兄弟节点合并
    if (rightBroPtr && rightBroPtr->keyNum + node->keyNum + 1 <= maxKeyNum) {
        fromRight = rightBroPtr->keyNum;
    }
    // 左、右兄弟节点均不可合并，则返回false
    if (fromLeft == INT32_MAX && fromRight == INT32_MAX) {
        return false;
    }
    // 选取左右兄弟节点中，关键字数较少的一方合并（相等则优先与左兄弟节点合并）
    return mergeTwoContChild(parent, childOrder - (int)(fromLeft <= fromRight));
}

/**
 * 维持 node 节点平衡
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param node 待平衡节点
 * @param childOrder 属于父节点的第几个子节点
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::removeBalance(BTreeNode<KEY_TYPE, VALUE_TYPE> *node, int childOrder) {
    // 若节点的关键词数为0，且非叶子节点（降层）
    if (node->keyNum == 0 && !node->isLeaf) {
        reduceLevel(node, childOrder);
        return true;
    }
    // 若节点已平衡，返回
    if (node->keyNum >= minKeyNum) {
        return true;
    }
    // 无父节点，或属于父节点的子节点非法
    if (!node->parent || childOrder < 0 || node->parent->keyNum < childOrder) {
        return false;
    }
    // 节点关键字数少于minKeyNum，优先尝试从左、右兄弟节点挪借关键字（以维持平衡）
    if (browFromBro(node, childOrder)) {
        return true;// 挪借成功，则返回
    }
    // 无法挪借，则尝试与左或右兄弟节点关键字较少的一方合并（以维持平衡）
    return mergeWithBro(node, childOrder);
}

template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::containKey(KEY_TYPE key) {
    return root->containKey(key);
}

template<class KEY_TYPE, class VALUE_TYPE>
VALUE_TYPE BTree<KEY_TYPE, VALUE_TYPE>::getValue(KEY_TYPE key) {
    return root->getValue(key);
}

template<class KEY_TYPE, class VALUE_TYPE>
void BTree<KEY_TYPE, VALUE_TYPE>::print() {
    cout << root->toString() << endl;
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

/**
 * 从B树中删除<key, value>（若存在）
 * @tparam KEY_TYPE
 * @tparam VALUE_TYPE
 * @param key
 * @return true -- 删除成功； false -- 不存在 / 删除失败
 */
template<class KEY_TYPE, class VALUE_TYPE>
bool BTree<KEY_TYPE, VALUE_TYPE>::remove(KEY_TYPE key) {
    int i = -1, lastI;
    BTreeNode<KEY_TYPE, VALUE_TYPE>* ptr = root;
    while (true) {
        lastI = i;
        i = ptr->binarySearchKey(key);
        if (i < ptr->keyNum && ptr->keys[i] == key) {
            break;
        }
        // 若是叶子节点，说明无该key，则返回false
        if (ptr->isLeaf) {
            return false;
        }
        // 若非叶子节点，继续向下寻找待删除的key
        ptr = ptr->childPtrs[i];
    }
    // 已找到 key，调用指定节点的删除操作
    return appointRemove(ptr, ptr->keys[i], i, lastI);
}
/***********************************  上方为 BTree 类函数实现部分 ***********************************/

/*
测试代码 main.cpp
#include <iostream>
#include "myBTree.h"
using namespace std;

int main() {
    BTree<int, char*> bt(5);
    bt.insert(4, "four");
    bt.insert(3, "three");
    bt.insert(2, "two");

    bt.insert(1, "one");
    bt.insert(3, "THREE");
    bt.insert(5, "five");
    bt.insert(6, "six");
    bt.insert(7, "seven");
    bt.insert(8, "eight");
    bt.insert(9, "night");
    bt.insert(10, "ten");
    bt.insert(11, "eleven");
    bt.insert(12, "twelve");
    bt.insert(13, "thirteen");
    bt.insert(14, "fourteen");
    bt.insert(15, "fifteen");
    bt.insert(16, "sixteen");
    bt.insert(17, "seventeen");
    bt.insert(18, "eighteen");

    cout << "containKey(12):" << bt.containKey(12) << endl;
    cout << "containKey(9):" << bt.containKey(9) << endl;
    cout << "getValue(15):" << bt.getValue(15) << endl;
    cout << "getValue(3):" << bt.getValue(3) << endl;
    bt.print();

    bt.remove(11);
    bt.print();
    bt.remove(13);
    bt.print();
    bt.remove(14);
    bt.print();
    bt.remove(15);
    bt.print();
    bt.remove(17);
    bt.print();
    bt.remove(10);
    bt.print();
    bt.remove(9);
    bt.print();
    bt.remove(16);
    bt.print();
    bt.remove(12);
    bt.print();
    bt.remove(18);
    bt.print();
    bt.remove(7);
    bt.print();
    bt.remove(6);
    bt.print();
    bt.remove(2);
    bt.print();
    bt.remove(5);
    bt.print();
    bt.remove(3);
    bt.print();
    bt.remove(8);
    bt.print();
    bt.remove(4);
    bt.print();
    bt.remove(1);
    bt.print();

    bt.insert(12, "s12");
    bt.insert(54, "s54");
    bt.insert(123, "s123");
    bt.insert(6435, "s6435");
    bt.insert(125, "s125");
    bt.insert(65, "s65");
    bt.print();
    return 0;
}
 */

#endif //__MYBTREE_H_
