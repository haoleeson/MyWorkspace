layout: post
title: Kmeans算法--数据挖掘
date: 2018/10/24 19:20:44
updated: 2019/2/18 15:03:45
comments: true
tags:
- 数据挖掘
- 算法
categories:
- 算法

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Kmeans.png" class="full-image" />

# 实现K-means算法对无噪声的waveform数据集进行分割
## K-means算法介绍
k均值聚类是一种矢量量化方法，最初来自信号处理，是数据挖掘中聚类分析的常用方法。 k均值聚类的目的是将n个观测值划分为k个聚类，其中每个观测值属于具有最近均值的聚类，作为聚类的原型。这导致数据空间划分为Voronoi单元。
<!-- more -->

这个问题在计算上很困难（NP难）;然而，有效的启发式算法快速收敛到局部最优。这些通常类似于通过k均值和高斯混合建模所采用的迭代细化方法的高斯分布混合的期望最大化算法。他们都使用集群中心来建模数据;然而，k均值聚类倾向于找到具有可比空间范围的聚类，而期望最大化机制允许聚类具有不同的形状。
该算法与k-最近邻分类器具有松散的关系，这是一种流行的分类机器学习技术，由于名称的原因常常与k-means混淆。应用1最近邻分类器，通过k均值获得的聚类中心将新数据分类到现有聚类中。这被称为最近的质心分类器或Rocchio算法。

## Python编程实现K-means算法
**K-means算法主要分为以下步骤实现**：
* S1.随机生成 k 个 “种子”
* S2.依次求解当前(第i个)元素对k个'种子'的最小欧式距离，得到距当前(第i个)元素欧式距离最小的('种子')集群
* S3.如果当前(第i个)元素的与k个‘种子’(集群)的最小欧式距离所对应的【种子编号】遇上一次记录不一致 ==> (第i个)元素所属集群发生改变，更新所属集群
* S4.重新计算k个('种子')集群的各属性值的平均值，得到新的k个('种子')集群
* S5.若S2～S4的运行过程中，至少1个元素的所属‘种子’(集群)发生改变，则不断重复运行S2~S5过程,直至没有元素所属‘种子’(集群)发生改变视为聚类成功(也可限定最大迭代次数)跳转S6
* S6.结束迭代，返回k个集群的中心值centroids, 及每个集群所包含的元素数组clusterAssment

```python
import random
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd # Pandas库：强大、灵活的数据分析和探索工具

# 计算欧式距离:
# 将'vector1'与'vector2'中所有对应属性值之差的平方求和，再求平方根
def caclEucDistance(vector1, vector2):
    distance = np.sqrt(np.sum(np.square(vector2 - vector1)))
    return distance

# 随机生成 k 个 “种子”
def initCentroids(dataSet, k):
    numSamples, dim = dataSet.shape
    centroids = np.zeros((k, dim)) #创建大小为：'k x 元素属性列值' 的全0矩阵，用于存放k个‘种子’（集群）
    # 随机生成 k 个 “种子”
    for i in range(k):
        index = int(random.uniform(0, numSamples))
        centroids[i, :] = dataSet[index, :] #在数据集中取 k 个值
    return centroids

# k-means 算法实现
def kmeans(dataSet, k):
    numSamples = dataSet.shape[0]
    clusterAssment = np.mat(np.zeros((numSamples, 2)))
    # clusterAssment '元素属性值行 x 2列矩阵'
    # 第一列：存储此示例所属的('种子')集群
    # 第二列：存储当前(第i个)元素与其所属的('种子')集群的欧式距离
    clusterChanged = True
    # clusterChanged：在迭代时'种子'是否改变标志

    ## 随机生成 k 个 “种子”
    centroids = initCentroids(dataSet, k)

	# 一直迭代直到没有1个'种子'的所属('种子')集群发生改变
    while clusterChanged:
   
        # 迭代前为'种子'是否改变标志赋初值(False:未改变，如果执行完循环体后仍未False,视作迭代完成，退出迭代)
        clusterChanged = False 
                
        ## 依次求解每个元素对k个'种子'的最小距离
        for i in range(numSamples):
            minDist = 100000.0
            minIndex = 0
            
            #比较当前(第i个)元素 对应 k个'种子' 的欧式距离，求出最小（存于minDist），并记录对应种子编号（存于minIndex）
            for j in range(k):
                distance = caclEucDistance(centroids[j, :], dataSet[i, :])
                if distance < minDist:
                    minDist = distance
                    minIndex = j

            ## 如果当前(第i个)元素的与k个‘种子’(集群)的最小欧式距离所对应的【种子编号】遇上一次记录不一致 ==> (第i个)元素所属集群发生改变
            if clusterAssment[i, 0] != minIndex:
            	# 该变标志置'True' , 更新当前(第i个)元素的所属集群编号
                clusterChanged = True
                clusterAssment[i, :] = minIndex, minDist ** 2

        ## 重新计算各个集群的中心点，并更新
        for j in range(k):
            pointsInCluster = dataSet[np.nonzero(clusterAssment[:, 0].A == j)[0]]
            centroids[j, :] = np.mean(pointsInCluster, axis=0)

    # 此处表示退出迭代 ==> 聚类成功
    print('Congratulations, cluster complete!')
    return centroids, clusterAssment
```

## 编写Python程序实现K-means算法对UCI的waveform数据集的3个类中每类数据取100个的分割
从UCI获取[
Waveform Database Generator (Version 2) Data Set](http://archive.ics.uci.edu/ml/datasets/waveform+database+generator+(version+2))数据集。由网页介绍可知该数据集中，数据量为：5000， 属性数为：40(实际21列), waves数据的类为：3。

### 程序加载waveform.data数据
通过以下代码读取Waveform Database Generator (Version 2) Data Set中'waveform.data'文件内的所有数据，可看到数据的最后一列为类属性的标识号，由网页介绍可知，waves数据共有3类。
```python
# 数据加载
print('数据加载...\n')
data = pd.read_csv('waveform.data', sep=',', engine='python', header=None, skiprows=0, names=None) # waveform.data
print(data[0])
```
### 在第0~2类中，每类提取100个数据
在3类中每类取100个数据使用上一步实现的K-means算法的进行聚类,其中每类取100个样本，并将这300个样本拼接到一个列表，将这个操作封装成函数如下：
```python
# 在data中，第0~2类，每获取100个数据并简单拼接
def geteveryClass3Data100Samples(data):
    data_class0 = data[data[21]==0].head(100) #取第0类数据前100个
    data_class1 = data[data[21]==1].head(100) #取第1类数据前100个
    data_class2 = data[data[21]==2].head(100) #取第2类数据前100个
    data_3x100 = pd.concat([data_class0, data_class1, data_class2]) #简单拼接到一起
    data_3x100 = data_3x100.sort_index() #将这300个样本，按原文件的索引从小到大排序(打乱第0~2类的数据)
    data_3x100 = data_3x100.reset_index(drop=True) #重新建立索引
    return data_3x100
```
### 用K-means算法对UCI的waveform数据集中筛选出的300个样本进行分割
设置'种子'(集群)个数为:5, 运行k-means算法进行迭代分割
```python
data_3x100 = np.mat(data_3x100)
k = 5
centroids, clusterAssment = kmeans(data_3x100, k)
```
设置分割'种子'(集群)个数为:5时，k-means分割（集群中心点）如下：
```python
centroids:
[[-0.07813559  0.40762712 -0.00067797  0.27966102  0.30101695  0.99237288
   2.17169492  2.86677966  3.79711864  4.43864407  5.55898305  4.80983051
   3.42457627  3.19677966  2.29627119  1.22847458  0.41711864  0.37355932
   0.1579661   0.04322034  0.28288136  1.54237288]
 [-0.09621622  0.93040541  1.7172973   2.41486486  3.45162162  4.06337838
   5.0372973   4.08067568  3.61054054  2.96756757  2.16027027  1.42175676
   0.93310811  0.84135135  0.76283784  0.67040541  0.5422973   0.45581081
   0.01040541  0.13513514  0.15216216  0.43243243]
 [-0.0027027   0.50324324  0.90378378  1.23        1.77783784  1.97189189
   2.92        2.16405405  1.71540541  1.70378378  1.92513514  2.20432432
   2.42216216  2.71108108  3.4572973   2.60216216  2.22405405  1.64891892
   1.4772973   0.91378378 -0.10621622  0.        ]
 [ 0.11701149 -0.04942529  0.15103448  0.2254023   0.02505747  0.53701149
   0.52448276  0.95298851  1.39574713  2.04942529  2.98126437  3.51758621
   3.88402299  4.27816092  4.94563218  3.90206897  2.75586207  2.2708046
   1.31091954  0.7808046  -0.05574713  1.56321839]
 [ 0.16418605  0.40674419  0.60651163  1.61302326  1.84697674  2.77744186
   4.06790698  3.94511628  4.00023256  4.18767442  4.25465116  3.05651163
   2.0372093   1.23186047  0.92744186  0.74837209 -0.07837209 -0.14767442
   0.1255814  -0.0727907  -0.06697674  0.95348837]]
```
设置分割'种子'(集群)个数为:10时，k-means分割（集群中心点）如下：
```python
centroids:
 [[ 0.05916667  0.48        0.4125      1.08        1.20388889  2.09888889
   3.15527778  3.62388889  4.28333333  4.35555556  5.08        3.77861111
   2.64166667  1.89805556  1.35138889  0.85166667 -0.05416667  0.03388889
   0.08083333  0.07666667  0.16888889  1.        ]
 [-0.48290323  0.64677419  1.51258065  2.13935484  3.30935484  3.56096774
   4.61419355  3.29774194  3.21        2.65354839  1.97225806  1.4
   1.31290323  1.58870968  1.15967742  1.19612903  1.1016129   0.96290323
   0.39032258  0.47419355  0.21322581  0.16129032]
 [-0.57913043  0.70695652  0.55217391  0.59521739  1.11130435  0.91608696
   1.8326087   0.71521739  1.23130435  1.29086957  1.73695652  3.23869565
   3.33608696  3.50521739  4.50695652  3.38652174  2.71173913  1.58913043
   1.32434783  1.0573913   0.06608696  0.52173913]
 [ 0.56333333  0.22777778  1.39777778  1.62666667  1.97166667  2.52888889
   3.37111111  2.64666667  2.01611111  1.95        1.60555556  1.56888889
   2.40555556  2.01555556  2.97277778  2.33055556  2.20944444  1.59333333
   1.20611111  0.66777778  0.08222222  0.        ]
 [-0.35111111  0.43777778  0.35111111  0.60111111  1.68888889  1.59
   2.60777778  2.73111111  1.46444444  1.9         2.70111111  2.50222222
   1.77888889  2.82777778  3.32111111  2.25111111  1.80444444  1.69111111
   1.83777778  1.02333333 -0.81777778  0.        ]
 [ 0.13974359  0.03769231 -0.19538462 -0.03897436  0.06948718  0.30487179
   0.94025641  1.81025641  2.21564103  2.92897436  4.26564103  4.30051282
   3.85358974  3.62333333  3.78410256  2.80692308  1.69282051  1.52538462
   1.12794872  0.55102564 -0.08230769  2.        ]
 [ 0.27111111 -0.21111111  0.24088889  0.47222222 -0.22355556  0.66466667
   0.25977778  0.54777778  1.01555556  1.72822222  2.55888889  3.07777778
   3.85911111  4.78444444  5.672       4.64822222  3.32355556  2.85711111
   1.46044444  0.83622222  0.00777778  1.42222222]
 [ 0.38176471  0.59882353  0.895       2.25941176  2.44352941  3.32911765
   4.81647059  4.02794118  3.63352941  3.83470588  3.34117647  2.41088235
   1.30147059  0.83588235  0.90970588  0.585       0.13470588 -0.05617647
   0.10294118 -0.23382353 -0.06294118  0.82352941]
 [-0.084       1.168       2.10333333  2.54066667  3.858       4.87866667
   5.49433333  4.91        4.08633333  3.16633333  2.175       1.17433333
   0.554       0.12933333  0.15466667  0.12266667  0.01733333  0.14733333
  -0.47633333  0.00633333  0.173       0.63333333]
 [-0.10057143  0.44885714  0.00542857  0.09514286  0.19742857  0.86142857
   1.98857143  2.93914286  3.95371429  4.702       5.82428571  5.14028571
   3.702       3.64314286  2.28428571  1.14228571  0.34742857  0.16857143
   0.04457143 -0.09171429  0.222       1.65714286]]
```

{% note success %}
**备注**
**运行平台**：Arch Linux
**运行环境**：Intellij IDEA
**待处理文件**：[waveform.data](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/waveform.data)
**源代码**：[kmeans.py](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/kmeans.py)
{% endnote %}


# K-means算法对一副无噪图像进行分割
**加载图片数据**
```python
# 获取图片的rgb列表
def getImageRGB(file):
    image = img.imread(file)
    width, height, x = image.shape
    # 创建与照片像素规模同大小rgb列表，存rgb数据
    rgb = np.zeros((width, height, x))
    for i in range(width):
        for j in range(height):
            rgb[i][j] = image[i, j]
    return rgb
```
**修改k个随机种子生成函数，使返回k个随机像素点坐标**

```python
# 随机生成k个种子，返回k个随机像素点坐标
def initCentroids(imageRGB, k):
    center = []
    for i in range(k):
        x, y = random.randint(0, imageRGB.shape[0]), random.randint(0, imageRGB.shape[1])
        center += [[x, y]]
    return center
```
**修改欧式距离的计算公式，按对第一步随机产生的k个变量的欧式距离分簇**

```python
def caclEucDistance(imageRGB, centers):
    region = []
    for i in range(imageRGB.shape[0]): #行
        x = []
        for j in range(imageRGB.shape[1]): #列
            temp = []
            for k in range(len(centers)): #计算k个像素点与k个中心点的欧式距离
                dist = np.sqrt(np.sum(np.square(imageRGB[i, j] - imageRGB[centers[k][0], centers[k][1]])))
                temp += [dist] #添加到temp临时数组中
            x.append(np.argmin(temp)) #距离最小的集群的下标，按距离分簇
        region.append(x)
    return region #返回与数组同大小的 像素与簇对应关系
```
**迭代循环中计算每个像素点与k个簇平均值的欧式距离，并分簇**

```python
def loopCaclEucDistance(imageRGB, CalCentercolor):
    region = []
    for i in range(imageRGB.shape[0]): #行
        x = []
        for j in range(imageRGB.shape[1]): #列
            temp = []
            for k in range(len(CalCentercolor)): #计算k个像素点与k个中心点的欧式距离
                dist = np.sqrt(np.sum(np.square(imageRGB[i, j] - CalCentercolor[k])))
                temp += [dist] #添加到temp临时数组中
            x.append(np.argmin(temp))  #距离最小的集群的下标，按距离分簇
        region.append(x)
    return region #返回与数组同大小的 像素与簇对应关系
```
**计算集群内所有样本的平均值**

```python
def calNewCenter(features, imageRGB, k):
    temp = [] #一位数组
    for i in features:
        for j in i:
            temp.append(j)
    centercolor = [0] * k
    # 累加 每个集群中所包含的 像素点的RGB值
    for i in range(len(features)): #Rows
        for j in range(len(features[i])): #Columns
            centercolor[features[i][j]] += imageRGB[i, j]
    
    for i in range(len(centercolor)):
        centercolor[i] /= temp.count(i) #求每个集群的RGB 均值
        # 将求得的均值[取整]
        for j in range(len(centercolor[i])):  #Columns
            centercolor[i][j] = int(centercolor[i][j])
    return centercolor
```
**显示分割前后对比图程序**

```python
def showImage(imageRGB, centercolor, features, k, iteration):
    NewImage = np.empty((len(features), len(features[0]), 3))
    for i in range(len(features)):
        for j in range(len(features[i])):
            NewImage[i, j] = centercolor[features[i][j]]
    # 绘制图片
    fig = plt.figure(figsize=(10, 4), facecolor='white')
    fig.suptitle('k='+str(k)+', iteration='+str(iteration), fontsize=12, color='k')
    fig.gca().xaxis.set_major_locator(plt.NullLocator())
    fig.gca().yaxis.set_major_locator(plt.NullLocator())

    # 创建子图1: 绘制原图
    ax1 = fig.add_subplot(1, 2, 1)
    ax1.axis('off') # 关闭坐标轴显示
    ax1.imshow(imageRGB / 255)
    ax1.set_title('Original image', fontsize=10, color='k')

    # 创建子图2: 绘制分割图
    ax2 = fig.add_subplot(1, 2, 2)
    ax2.axis('off') # 关闭坐标轴显示
    ax2.imshow(NewImage / 255)
    ax2.set_title('Split graph', fontsize=10, color='k')

    # 显示绘制图像
    pylab.show()
    plt.show()
```

## 使用K-means算法对一副无噪图像进行分割完整主程序
```python
def main():
    #加载图片数据
    imageRGB = getImageRGB('picture.jpg')
    print('Finish load image RGB data...')
    #设置集群数：k=3
    k = 3
    # 生成k个随机像素点坐标
    InitialCenter = initCentroids(imageRGB, k)
    # 计算样本中每个像素点与k个中心点的欧式距离，并重新分类
    features = caclEucDistance(imageRGB, InitialCenter)

    #设置k-means算法执行的最大迭代次数：iteration = 20
    iteration = 20
    for i in range(iteration, 0, -1):
        print('iteration = ', i)
        CalCentercolor = calNewCenter(features, imageRGB, k) # 得到每个簇的均值
        # 根据簇中的新均值，并重新分簇
        features = loopCaclEucDistance(imageRGB, CalCentercolor)
        print('\n'+'Center[k] = ', CalCentercolor, '\n')

    #显示分割前后对比图
    showImage(imageRGB, CalCentercolor, features, k, iteration)
```

## K-means算法分割图片效果图
### 当最大迭代次数限制为20次时：
**k=3时的效果图如下**：
![iteration=20,k=3时的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Kmeans_result_k=3_iteration=20.png)
**k=8时的效果图如下**：
![iteration=20,k=8时的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Kmeans_result_k=8_iteration=20.png)

#### 当最大迭代次数限制为50次时：
**k=3时的效果图如下**：
![iteration=50,k=3时的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Kmeans_result_k=3_iteration=50.png)
**k=8时的效果图如下**：
![iteration=50,k=8时的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Kmeans_result_k=8_iteration=50.png)
通过反复运行测试，得出在一定的迭代次数限制下，设置的种子数越多，图像分割越明显，细节越丰富；在一定种子数范围内，最大迭代次数越多，图像分割效果并不一定更好。并且程序的运行时间会随着集群k、最大迭代次数iteration的增加而增加。


{% note success %}
**备注**
**运行平台**：Arch Linux
**运行环境**：Intellij IDEA
**待聚类图片**：[KmeansTestPicture.jpg](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/KmeansTestPicture.jpg)
**源代码**：[kmeansPicture.py](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/kmeansPicture.py)
{% endnote %}
