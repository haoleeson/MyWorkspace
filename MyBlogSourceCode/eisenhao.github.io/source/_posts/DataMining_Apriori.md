layout: post
title: Apriori算法——数据挖掘
date: 2018/12/10 19:05:30
updated: 2019/2/18 17:25:45
comments: true
tags:
- 数据挖掘
- 算法
categories:
- 算法

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Apriori.png" class="full-image" />

# 1. Apriori算法简介
- Apriori是一种在事务数据库上进行频繁项集挖掘和关联规则学习的算法。
- 它通过识别数据库中的频繁单项，并将经常出现的项扩展到越来越大的项目集。
- Apriori确定的频繁项目集可用于确定关联规则，能够显示出数据库中项的一般趋势，故常应用于诸如市场购物栏分析的领域中（决策分析）。

<!-- more -->

- Apriori算法由Agrawal和Srikant于1994年提出。Apriori旨在对包含交易的数据库(例如：客户购买的项目集合，或网站频繁或IP地址的详细信息)进行操作。
- 其他算法设计用于在没有事务(Winepi和Minepi)或没有时间戳(DNA序列)的数据中查找关联规则。
- 每个事务都被视为一组项(项集)。给出一个门槛 C，Apriori算法识别至少是子集的项集 C 数据库中的事务。Apriori使用“自下而上”方法，其中频繁的子集一次扩展一个项目(称为候选生成的步骤)，并且针对数据测试候选组。当没有找到进一步成功的扩展时，算法终止。

# 2. Python编程实现Apriori算法
## 2.1. Apriori算法步骤
- S1.令 k=1
- S2.扫描数据库，生成长度为k的候选项集的集合Ck
- S3.重复S4~S8直到找不到新的候选项集的集合Ck
- S4.从长度为k的频繁项集Lk生成长度为(k + 1)的候选项集
- S5.修剪长度为(k + 1)的候选项集中的出现频率低于(min_support阈值)的候选项目
- S6.通过扫描数据库，统计每个候选项的数目
- S7.删除出现频率低于(min_support阈值)的候选项，只留下频繁出现的候选项目集Lk
- S8. k = k + 1

## 2.2. 生成长度为1的候选项集C1
```python
# C1 是大小为1的所有候选项集的集合
def createC1(dataSet):
    C1 = []
    for transaction in dataSet:
        for item in transaction:
            if not [item] in C1:
                C1.append([item]) #store all the item unrepeatly
    # C1.sort()
    #return map(frozenset， C1)#frozen set， user can't change it.
    return list(map(frozenset， C1))
```

## 2.3. 扫描数据库，返回频繁出现的候选项目集Lk(出现频率大于给定阈值minSupport)
```python
def scanD(D， Ck， minSupport):
    ssCnt={}
    for tid in D:
        for can in Ck:
            if can.issubset(tid):
                #if not ssCnt.has_key(can):
                if not can in ssCnt:
                    ssCnt[can]=1
                else: ssCnt[can]+=1
    numItems=float(len(D))
    retList = []
    supportData = {}
    for key in ssCnt:
        support = ssCnt[key]/numItems #compute support
        if support >= minSupport:
            retList.insert(0， key)
        supportData[key] = support
    return retList， supportData
```

## 2.4. apriori组合，向上合并L
```python
def aprioriGen(Lk， k):
    #creates Ck 参数：频繁项集列表 Lk 与项集元素个数 k
    retList = []
    lenLk = len(Lk)
    for i in range(lenLk):
        for j in range(i+1， lenLk): #两两组合遍历
            L1 = list(Lk[i])[:k-2]; L2 = list(Lk[j])[:k-2]
            L1.sort(); L2.sort()
            if L1 == L2: #若两个集合的前k-2个项相同时， 则将两个集合合并
                retList.append(Lk[i] | Lk[j]) #set union
    return retList
```

## 2.5. apriori算法核心函数
```python
def apriori(dataSet， minSupport = 0.5):
    C1 = createC1(dataSet)
    D = list(map(set， dataSet)) #python3
    L1， supportData = scanD(D， C1， minSupport)#单项最小支持度判断 0.5，生成L1
    L = [L1]
    k = 2
    while (len(L[k-2]) > 0):#创建包含更大项集的更大列表， 直到下一个大的项集为空
        Ck = aprioriGen(L[k-2]， k)#Ck
        Lk， supK = scanD(D， Ck， minSupport)#get Lk
        supportData.update(supK)
        L.append(Lk)
        k += 1 #继续向上合并 生成项集个数更多的
    return L， supportData
```

## 2.6. 主函数
```python
# main函数
if __name__ == "__main__":
    #加载数据集
    dataSet = loadDataSet()
    #挖掘频繁项集
    L， supportData = apriori(dataSet， 0.5)
    print('L = '， L)
    print('supportData = '， supportData)
```

运行结果：
```python
L = [[frozenset({5})， frozenset({2})， frozenset({3})， frozenset({1})]， [frozenset({2，
5})， frozenset({2， 3})， frozenset({1， 3})]， []]
supportData = {frozenset({1}): 0.5， frozenset({3}): 0.75， frozenset({4}): 0.25，
frozenset({2}): 0.75， frozenset({5}): 0.5， frozenset({1， 3}): 0.5， frozenset({2， 3}):
0.5， frozenset({2， 5}): 0.5， frozenset({3， 5}): 0.25， frozenset({1， 5}): 0.25，
frozenset({1， 2}): 0.25， frozenset({2， 3， 5}): 0.25}

Process finished with exit code 0
```
对于数据集[[1， 3， 4]， [2， 3]， [1， 2， 3， 5]， [2， 5]]，运行apriori挖掘(出现频率大于阈值0.5)的频繁项集合为:[5]， [2]，
[3]， [1]， [2，5]， [2，3]， [1，3]，其中[2，5]， [2，3]， [1，3]在数据库中出现的频率均为0.5

{% note success %}
**备注**
**运行平台**：Arch Linux
**运行环境**：Intellij IDEA
**源代码**：[Apriori.py](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/Apriori.py)
{% endnote %}
