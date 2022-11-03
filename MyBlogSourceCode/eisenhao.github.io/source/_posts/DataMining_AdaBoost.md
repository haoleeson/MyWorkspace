layout: post
title: AdaBoost算法——数据挖掘
date: 2018/12/3 14:05:30
updated: 2019/2/18 17:05:45
comments: true
tags:
- 数据挖掘
- 算法
categories:
- 算法

---
<img src="../../../../uploads/DataMining_AdaBoost.png" class="full-image" />

# 1. 集成学习AdaBoost算法简介
AdaBoost全称是adaptive boosting，该算法基本思想:多个结构较为简单，分类或预测精度较低的弱学习算法可以通过某种方式结合成具有较强学习能力的强学习算法。根据统计学习方法的三要素，AdaBoost 方法=加法模型+指数损失函数(策略)+前向分步 算法。

<!-- more -->
# 2. AdaBoost运行原理如下:

- S1.初始化训练数据的权值分布。如果有N个样本，则每一个训练样本最开始时都被赋予相同的权值:1/N。

- S2.训练弱分类器。
  - 具体训练过程中，如果某个样本点已经被准确地分类，那么在构造下一个训练集中，它的权值就被降低;
  - 相反，如果某个样本点没有被准确地分类，那么它的权值就得到提高。
  - 然后，权值更新过的样本集被用于训练下一个分类器，整个训练过程如此迭代地进行下去。

- S3.将各个训练得到的弱分类器组合成强分类器。各个弱分类器的训练过程结束后，加大分类误差率小的弱分类器的权重，使其在最终的分类函数中起着较大的决定作用，而降低分类误差率大的弱分类器的权重，使其在最终的分类函数中起着较小的决定作用。换言之，误差率低的弱分类器在最终分类器中占的权重较大，否则较小。

# 3. Python编程实现基于单层决策树的AdaBoost算法
## 3.1. 基于单层决策树的AdaBoost算法步骤
- S1.找出最佳单层决策树: a.将最小分类误差率minerror=inf b.对数据集中的每一个特征: c.对该特征的每个步长(找出决策阈值): d.对每个不等号(>=，<): e.建立一颗单层决策树(只包含树桩)并利用加权数据集并计算该决策树的分类误差率 f.如果分类误差率小于minerror，则将当前单层决策树设置成最佳单层决策树。
- S2.利用单层决策树的分类误差率计算该决策树的比例系数alpha
- S3.计算更新权重向量D
- S4.更新累计类别估计值，计算AdaBoost模型的错误率
- S5.如果错误率为0或者分类器数目i>M，则退出循环

## 3.2. 寻找最优决策树
找到加权错误率(分类错误率)最小的单层决策树(会被不断迭代)
```python
def buildStump(dataArray， classLabels， D):
    dataMatrix = np.mat(dataArray); labelMat = np.mat(classLabels).T
    m， n = np.shape(dataMatrix)
    stepNum = 10.0; bestStump = {}; bestClassEst = np.mat(np.zeros((m， 1)))
    minError = np.inf
    for i in range(n):
        rangeMin = dataMatrix[:， i].min(); rangeMax = dataMatrix[:， i].max()
        stepSize = (rangeMax - rangeMin)/stepNum
        for j in range(-1， int(stepNum)+1):
            for thresholdIneq in ['lt'， 'gt']:
                thresholdValue =  rangeMin + float(j) * stepSize
                predictClass = stumpClassify(dataMatrix， i， thresholdValue， thresholdIneq)
                errArray =  np.mat(np.ones((m， 1)))
                errArray[predictClass == labelMat] = 0
                weightError = D.T * errArray
                #print "split: dim %d， thresh: %.2f， threIneq:%s， weghtError %.3F" %(i， thresholdValue， thresholdIneq， weightError)
                if weightError < minError:
                    minError = weightError
                    bestClassEst = predictClass.copy()
                    bestStump['dimen'] = i
                    bestStump['thresholdValue'] = thresholdValue
                    bestStump['thresholdIneq'] = thresholdIneq
    return bestClassEst， minError， bestStump
```

## 3.3. 输出多个弱分类器的数组
```python
def adaBoostTrainDS(dataArray， classLabels， numIt=40):
    weakClass = []#定义弱分类数组，保存每个基本分类器bestStump
    m， n = np.shape(dataArray)
    D = np.mat(np.ones((m， 1))/m)
    aggClassEst = np.mat(np.zeros((m， 1)))
    for i in range(numIt):
        print("i:"， i)
        bestClassEst， minError， bestStump = buildStump(dataArray， classLabels， D)#step1:找到最佳的单层决策树
        print("D.T:"， D.T)
        alpha = float(0.5*np.log((1-minError)/max(minError， 1e-16)))#step2: 更新alpha
        print("alpha:"， alpha)
        bestStump['alpha'] = alpha
        weakClass.append(bestStump)#step3:将基本分类器添加到弱分类的数组中
        print("classEst:"， bestClassEst)
        expon = np.multiply(-1*alpha*np.mat(classLabels).T， bestClassEst)
        D = np.multiply(D， np.exp(expon))
        D = D/D.sum()#step4:更新权重，该式是让D服从概率分布
        aggClassEst += alpha*bestClassEst#steo5:更新累计类别估计值
        print("aggClassEst:"， aggClassEst.T)
        print(np.sign(aggClassEst) != np.mat(classLabels).T)
        aggError = np.multiply(np.sign(aggClassEst) != np.mat(classLabels).T， np.ones((m， 1)))
        print("aggError"， aggError)
        aggErrorRate = aggError.sum()/m
        print("total error:"， aggErrorRate)
        if aggErrorRate == 0.0: break
    return weakClass
```

## 3.4. 输出分类结果
```python
def adaTestClassify(dataToClassify， weakClass):
    dataMatrix = np.mat(dataToClassify)        
    m =np.shape(dataMatrix)[0]
    aggClassEst = np.mat(np.zeros((m， 1)))
    for i in range(len(weakClass)):
        # 输出决策树桩标签
        classEst = stumpClassify(dataToClassify， weakClass[i]['dimen']， weakClass[i]['thresholdValue']， weakClass[i]['thresholdIneq'])
        aggClassEst += weakClass[i]['alpha'] * classEst
        print('第'， i， '个弱分类器权值：'， aggClassEst)
    return np.sign(aggClassEst)
```

## 3.5. 主函数
```python
# main函数
if __name__  ==  '__main__':
    D =np.mat(np.ones((5， 1))/5)
    # 加载一个两个特征的数据集
    dataMatrix， classLabels = loadSimData()
    # 找到加权错误率（分类错误率）最小的单层决策树
    bestClassEst， minError， bestStump = buildStump(dataMatrix， classLabels， D)
    # 输出：多个弱分类器的数组
    weakClass = adaBoostTrainDS(dataMatrix， classLabels， 9)
    #
    testClass = adaTestClassify(np.mat([0， 0])， weakClass)
    print('最终分类标签：'， testClass)
```

运行结果：
```python
D.T: [[0.2 0.2 0.2 0.2 0.2]]
alpha: 0.6931471805599453
classEst: [[-1.]
[ 1.]
[-1.]
[-1.]
[ 1.]]
aggClassEst: [[-0.69314718 0.69314718 -0.69314718 -0.69314718 0.69314718]]
[[ True]
[False]
[False]
[False]
[False]]
aggError [[1.]
[0.]
[0.]
[0.]
[0.]]
total error: 0.2
i: 1
D.T: [[0.5
0.125 0.125 0.125 0.125]]
alpha: 0.9729550745276565
classEst: [[ 1.]
[ 1.]
[-1.]
[-1.]
[-1.]]
aggClassEst: [[ 0.27980789 1.66610226 -1.66610226 -1.66610226 -0.27980789]]
[[False]
[False]
[False]
[False]
[ True]]
aggError [[0.]
[0.]
[0.]
[0.]
[1.]]
total error: 0.2
i: 2
D.T: [[0.28571429 0.07142857 0.07142857 0.07142857 0.5  ]]
alpha: 0.8958797346140273
classEst: [[1.]
[1.]
[1.]
[1.]
[1.]]
aggClassEst: [[ 1.17568763 2.56198199 -0.77022252 -0.77022252 0.61607184]]
[[False]
[False]
[False]
[False]
[False]]
aggError [[0.]
[0.]
[0.]
[0.]
[0.]]
total error: 0.0
第 0 个弱分类器权值: [[-0.69314718]]
第 1 个弱分类器权值: [[-1.66610226]]
第 2 个弱分类器权值: [[-2.56198199]]
最终分类标签: [[-1.]]
```


{% note success %}
**备注**
**运行平台**：Arch Linux
**运行环境**：Intellij IDEA
**源代码**：[AdaBoost.py](../../../../uploads/AdaBoost.py)
{% endnote %}

