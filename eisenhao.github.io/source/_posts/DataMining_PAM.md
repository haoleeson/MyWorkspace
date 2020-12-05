layout: post
title: PAM算法--数据挖掘
date: 2018/10/26 15:05:44
updated: 2019/2/18 15:03:45
comments: true
tags:
- 数据挖掘
- 算法
categories:
- 算法

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_PAM.png" class="full-image" />
# 实现PAM算法对部分含有高斯噪声的waveform数据集进行聚类
## PAM算法介绍
PAM方法于1987年提出用于l1范数和其他距离的工作。 k-medoid是一种经典的聚类分割技术，它将n个对象的数据集聚为k个聚类，假设聚类的数量k是先验的。如果未知，则可以使用诸如轮廓的方法来确定k。 与k均值相比，它对噪声和异常值更具鲁棒性，因为它最小化了成对差异的总和，而不是欧几里德距离的平方和。 可以将medoid定义为群集的对象，其与群集中的所有对象的平均差异最小。即，它是群集中位于最中心的点（迭代选取最中心的点，而非Kmeans的中心计算值，抗噪声能力更强）。

<!-- more -->

## 编写Python程序实现PAM算法
**PAM算法主要分为以下步骤实现**：

* S1.随机生成 k 个 “种子” 作为中心点
* S2.将其余的对象划分至距离这k个类别中的最近的一个簇
* S3.计算此时损失值cost。计算所有对象与其簇中中心点的距离值，将其全部累加得到损失值，记为cost0
* S4.随机选择一个非中心对象Oi分别临时试替换k个簇中心对象中的一个，重新分簇，计算得到一个损失值cost
* S5.如果这个损失值cost小于S3中得到的cost0，则将这个最小损失值计算时对应的非中心点和中心点交换，更新cost0
* S6.重复S4~S6步骤，重复迭代直至收敛

## 对部分含有高斯噪声的waveform数据集进行聚类
### 加载'waveform-+noise.data'文件中的含噪声的数据
通过以下代码读取Waveform Database Generator (Version 2) Data Set中'waveform-+noise.data'文件内的所有数据，可看到数据的最后一列为类属性的标识号，由网页介绍可知,noise waveform数据规模为：5000 x 41，取含噪声waveform数据集的前500个数据样本进行聚类
```python
# 含噪声数据加载
print('数据加载...\n')
data = pd.read_csv('waveform.data', sep=',', engine='python', header=None, skiprows=0, names=None) # waveform.data
print(data[0])
```
### PAM算法对waveform数据集进行聚类
```python
# PAM算法实现
# iteration:最大迭代次数，k:'种子'集群个数，data:待聚类数据
def PAM(iteration, k, data):
    data_numSamples, data_dim = data.shape
    # print(data_numSamples, ' ', data_dim)

    data_new = copy.deepcopy(data)  # 前40列存放数据，不可变。最后1列即第41列存放标签，标签列随着每次迭代而更新。
    data_now = copy.deepcopy(data)  # data_now用于存放中间过程的数据

    center_point = np.random.choice(data_numSamples, k, replace=False)
    center = data_new[center_point, :(data_dim-2)]  # 随机形成的k个中心，维度为（3，40）

    distance = [[] for i in range(k)]
    distance_now = [[] for i in range(k)]  # distance_now用于存放中间过程的距离
    lost = np.ones([data_numSamples, k]) * float('inf')  # 初始lost为维度为（numSamples，3）的无穷大

    for j in range(k):  # 首先完成第一次划分，即第一次根据距离划分所有点到k个类别中
        distance[j] = np.sqrt(np.sum(np.square(data_new[:, :(data_dim-2)] - np.array(center[j])), axis=1))
    data_new[:, data_dim-1] = np.argmin(np.array(distance), axis=0)  # data_new 的最后一列，即标签列随之改变，变为距离某中心点最近的标签，例如与第0个中心点最近，则为0

    for i in range(iteration):  # 假设迭代n次

        for m in range(k):  # 每一次都要分别替换k=k个中心点，所以循环k次。这层循环结束即算出利用所有点分别替代k个中心点后产生的i个lost值

            for l in range(data_numSamples):  # 替换某个中心点时都要利用全部点进行替换，所以循环numSamples次。这层循环结束即算出利用所有点分别替换1个中心点后产生的numSamples个lost值

                center_now = copy.deepcopy(center)  # center_now用于存放中间过程的中心点
                center_now[m] = data_now[l, :(data_dim-2)]  # 用第l个点替换第m个中心点
                for j in range(k):  # 计算暂时替换1个中心点后的距离值
                    distance_now[j] = np.sqrt(np.sum(np.square(data_now[:, :(data_dim-2)] - np.array(center_now[j])), axis=1))
                data_now[:, (data_dim-1)] = np.argmin(np.array(distance),
                                            axis=0)  # data_now的标签列更新，注意data_now时中间过程，所以这里不能选择更新data_new的标签列

                lost[l, m] = (caclEucDistance(data_now[:, :(data_dim-2)], center_now[data_now[:, (data_dim-1)].astype(int)]) \
                              - caclEucDistance(data_now[:, :(data_dim-2)], center[data_new[:, (data_dim-1)].astype(
                            int)])).sum()  # 这里很好理解lost的维度为什么为numSamples*3了。lost[l,m]的值代表用第l个点替换第m个中心点的损失值

        if np.min(lost) < 0:  # lost意味替换代价，选择代价最小的来完成替换
            index = np.where(np.min(lost) == lost)  # 即找到min(lost)对应的替换组合
            index_l = index[0][0]  # index_l指将要替代某个中心点的候选点
            index_m = index[1][0]  # index_m指将要被替代的某个中心点，即用index_l来替代index_m

        center[index_m] = data_now[index_l, :data_dim-2]  # 更新聚类中心

        for j in range(k):
            distance[j] = np.sqrt(np.sum(np.square(data_now[:, :(data_dim-2)] - np.array(center[j])), axis=1))
        data_new[:, (data_dim-1)] = np.argmin(np.array(distance), axis=0)  # 更新参考矩阵,至此data_new的标签列得以更新，即完成了一次迭代

    return center ,data_new  # 最后返回center：集群中心对象，data_new：其最后一列即为最终聚好的标签
```
设置最大迭代次数teration = 10, '种子'集群个数k = 3,对提取的500个含有高斯噪声的waveform数据集分类结果如下：
```python
center
 [[ 1.24  1.75  3.09  3.08  3.39  3.22  5.38  4.55  3.24  2.52  2.66  1.15
   0.69  0.43  0.84  0.11  1.25  0.64 -0.14  0.78 -0.75 -0.02  0.14  0.97
   0.95  0.91  0.06  0.78  0.27 -2.38 -0.38 -0.04 -1.44  0.89 -1.91  0.04
   0.66 -0.05  0.74]
 [ 1.24  0.32  0.19  1.38  0.16  3.28  4.65  4.72  2.97  5.05  4.05  3.99
   3.17  1.06  0.36 -0.23 -0.22  1.4   1.33  0.72  0.63 -0.05  0.45  0.68
  -0.19 -1.13 -0.76 -0.01  0.81  0.3   1.81  0.15  0.89  0.31  1.11 -0.51
   0.42  0.52 -0.01]
 [ 0.05  0.27  1.3  -0.72 -0.6   1.16  1.29  1.59  0.54  2.19  3.77  3.77
   3.76  4.55  4.48  3.07  2.65  1.12  1.09  0.47  1.47  0.72 -0.02  1.14
  -1.04  1.16  0.81  1.63 -0.57  0.33 -0.2  -0.18  0.2  -0.22 -0.77  0.05
   0.03 -0.36  0.96]]
[2. 2. 1. 2. 0. 1. 0. 1. 0. 2. 1. 2. 2. 2. 2. 2. 2. 2. 0. 2. 1. 2. 0. 2.
 0. 1. 2. 0. 2. 2. 2. 1. 2. 2. 2. 2. 0. 2. 0. 0. 1. 2. 2. 1. 1. 2. 2. 1.
 1. 1. 2. 2. 2. 2. 1. 2. 1. 2. 2. 1. 1. 2. 1. 0. 1. 0. 1. 0. 1. 0. 1. 1.
 2. 2. 0. 2. 0. 1. 2. 1. 2. 1. 1. 1. 2. 0. 1. 0. 2. 2. 1. 1. 1. 0. 2. 0.
 1. 1. 1. 2. 0. 0. 2. 1. 2. 2. 1. 2. 2. 0. 2. 1. 2. 1. 2. 2. 2. 1. 1. 0.
 1. 1. 2. 2. 1. 2. 2. 2. 0. 2. 2. 2. 2. 2. 1. 2. 2. 0. 0. 2. 1. 2. 0. 2.
 2. 0. 1. 0. 2. 0. 0. 1. 0. 2. 2. 1. 1. 2. 2. 0. 0. 0. 1. 1. 1. 1. 2. 0.
 2. 2. 0. 0. 0. 2. 2. 2. 1. 2. 2. 2. 0. 1. 2. 2. 1. 2. 2. 2. 2. 0. 1. 0.
 2. 0. 0. 0. 0. 2. 2. 0. 1. 2. 1. 2. 2. 1. 0. 2. 1. 1. 0. 2. 2. 1. 2. 1.
 1. 0. 1. 2. 1. 1. 1. 0. 2. 2. 0. 2. 2. 0. 0. 0. 2. 1. 1. 2. 2. 1. 0. 2.
 1. 2. 1. 2. 1. 2. 0. 1. 1. 2. 0. 2. 1. 0. 2. 0. 2. 2. 2. 0. 1. 2. 0. 2.
 1. 2. 1. 1. 2. 0. 2. 0. 2. 1. 1. 1. 0. 2. 0. 1. 1. 0. 1. 2. 2. 2. 1. 2.
 0. 2. 2. 2. 1. 2. 2. 1. 2. 1. 0. 2. 2. 2. 1. 2. 1. 1. 2. 1. 1. 2. 0. 2.
 2. 2. 2. 2. 2. 1. 2. 2. 0. 0. 1. 2. 0. 0. 2. 2. 2. 0. 1. 0. 2. 2. 2. 2.
 2. 1. 2. 2. 1. 0. 1. 2. 0. 1. 2. 2. 2. 2. 1. 2. 1. 2. 0. 0. 1. 2. 1. 2.
 1. 0. 2. 2. 1. 2. 2. 2. 0. 2. 2. 2. 1. 1. 2. 0. 1. 0. 2. 2. 0. 0. 2. 1.
 2. 0. 1. 0. 2. 0. 0. 2. 2. 1. 0. 2. 2. 2. 2. 1. 1. 1. 0. 2. 2. 2. 1. 2.
 2. 2. 2. 0. 2. 1. 2. 2. 1. 2. 2. 2. 0. 1. 0. 2. 2. 2. 1. 1. 0. 1. 2. 2.
 2. 2. 2. 2. 2. 1. 2. 2. 2. 2. 0. 2. 2. 2. 2. 0. 0. 2. 0. 2. 1. 2. 2. 2.
 1. 0. 2. 1. 2. 2. 2. 1. 2. 0. 1. 2. 1. 0. 2. 2. 2. 2. 1. 2. 2. 2. 2. 2.
 2. 0. 1. 2. 1. 2. 2. 2. 1. 2. 1. 0. 2. 2. 1. 1. 1. 2. 2. 0.]
```

{% note success %}
**备注**
**运行平台**：Arch Linux
**运行环境**：Intellij IDEA
**含高斯噪声文件**：[waveform-+noise.data](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/waveform-+noise.data)
**源代码**：[pam.py](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/pam.py)
{% endnote %}

# 编写Python程序实现PAM算法并对一副噪声图像进行分割
## 加载含高斯噪声的图片的rgb数据
```python
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
## 随机生成k个种子，返回k个随机像素点坐标
```python
def initCentroids(imageRGB, k):
    center = []
    for i in range(k):
        x, y = random.randint(0, imageRGB.shape[0]), random.randint(0, imageRGB.shape[1])
        center += [[x, y]]
    return center
```
## 随机选择一个非中心点Oi
```python
def chooseOneNoCenterSample(imageRGB, centers):
    x, y = 0, 0
    isChooseACenterSampleFlag = True
    while(isChooseACenterSampleFlag):
        isExist = False
        x, y = random.randint(0, imageRGB.shape[0]), random.randint(0, imageRGB.shape[1])
        # 判断与k个中心 是否有重复样本,
        for k in range(len(centers)):
            if(x==centers[k][0] and y==centers[k][1]):
                isExist = True
                break;
        #若无重复，则退出while,并返回[x,y]
        if( isExist == False ):
            break;
        #若重复则继续while
    return [x, y]
```
## 计算变量中每个像素点与k个中心点的欧式距离，并分簇
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
            x.append(np.argmin(temp)) #添加[i,j]像素距离k个‘种子’最小的距离于region
        region.append(x)
    return region #返回与数组同大小的最小欧式距离数组
```
## 计算所有对象与其簇中中心点的距离值，将其全部累加得到损失值，记为cost
```python
def calcCost(imageRGB, features, centers):
    cost = 0.0
    for i in range(imageRGB.shape[0]): #行
        for j in range(imageRGB.shape[1]): #列
            dist = np.sqrt(np.sum(np.square(imageRGB[i, j] - imageRGB[centers[features[i][j]][0], centers[features[i][j]][1]])))
            cost = cost + dist
    return cost
```
## 显示分割前后对比图程序
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
## PAM算法对图片数据聚类实现
```python
def PAM(imageRGB, features, centers):
    # 计算初始cost0
    cost0 = calcCost(imageRGB, features, centers)
    # print('cost0=', cost0)
    # 随机选择一个非中心点Oi
    aNoCenterSample = chooseOneNoCenterSample(imageRGB, centers)
    # print('Center = ', centers)
    # print('aNoCenterSample = ', aNoCenterSample)

    # 替换该随机对象所属的第k个中心对象
    belongsK = features[aNoCenterSample[0]][aNoCenterSample[1]]
    TempCenters = centers
    TempCenters[belongsK][0] = aNoCenterSample[0]  # Rows下标
    TempCenters[belongsK][1] = aNoCenterSample[1]  # Columns下标
    # 重新分簇
    TempFeatures = caclEucDistance(imageRGB, TempCenters)
    # 计算代价cost
    Tempcost = calcCost(imageRGB, TempFeatures, TempCenters)
    # 比较替换后的 cost
    if (Tempcost < cost0):
        # 若比最初损失值cost0小，则确认替换
        centers = TempCenters
        features = TempFeatures
        cost0 = Tempcost
    return features, centers
```

## 使用PAM算法对一副有噪图像进行分割完整主程序
```python
def main():
    #加载图片数据
    imageRGB = getImageRGB('picture.jpg')
    print('Finish load image RGB data...\n')
    # 设置集群数：k=3
    k = 3
    #设置k-means算法执行的最大迭代次数：iteration = 20
    iteration = 10

    # 生成k个随机像素点坐标，作为中心点
    centers = initCentroids(imageRGB, k)
    # 计算样本中每个像素点与k个中心点的欧式距离，并根据距离分到最近簇
    features = caclEucDistance(imageRGB, centers)
    print('PAM start...\n')
    for i in range(iteration, 0, -1):
        print('iteration = ', i)
        features, centers = PAM(imageRGB, features, centers) #PAM迭代
        print('\n' + 'Centers = ', centers, '\n')

    centercolor = getCenterColor(imageRGB, centers, k)
    #显示分割前后对比图
    print('Show the Comparison images...')
    showImage(imageRGB, centercolor, features, k, iteration)
```

## PAM算法分割图片效果图
### 当最大迭代次数限制为10次时：
**k=3时的效果图如下**：
![PAMiteration=10,k=3时的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Pam_result_k=3_iteration=10.png)
**k=8时的效果图如下**：
![PAMiteration=10,k=8时的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Pam_result_k=8_iteration=10.png)

### 当最大迭代次数限制为30次时：
**k=3时的效果图如下**：
![PAMiteration=30,k=3时的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Pam_result_k=3_iteration=30.png)
**k=8时的效果图如下**：
![PAMiteration=30,k=8时的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_Pam_result_k=8_iteration=30.png)
通过反复运行测试，得出的结论基本与K-mean算法一致：在一定的迭代次数限制下，设置的种子数越多，图像分割越明显，细节越丰富；在一定种子数范围内，最大迭代次数越多，图像分割效果并不一定更好。并且程序的运行时间会随着集群k、最大迭代次数iteration的增加而增加。

# 对比PAM算法与Kmeans算法
虽然经过反复测试运行代码，PAM与Kmeans算法对图片的分割效果与集群数k和最大迭代次数iteration的关系结论基本一致，总的来说PAM算法运行时间较长，复杂度也较高。但相比与K-means算法，PAM算法又有一定优势。由于选择的是中心对象而非平均值，所以如结果所示，受样本中的噪声的影响相对较小。


{% note success %}
**备注**
**运行平台**：Arch Linux
**运行环境**：Intellij IDEA
**含噪声图片**：[PamTestPicture.jpg](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/PamTestPicture.jpg)
**源代码**：[pamPicture.py](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/pamPicture.py)
{% endnote %}
