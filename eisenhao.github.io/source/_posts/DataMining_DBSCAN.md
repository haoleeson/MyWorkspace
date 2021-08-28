layout: post
title: DBSCAN算法--数据挖掘
date: 2018/11/10 11:05:44
updated: 2019/2/18 16:07:45
comments: true
tags:
- 数据挖掘
- 算法
categories:
- 算法

---
<img src="https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN.png" class="full-image" />

# 1. DBSCAN算法介绍
基于密度的噪声应用空间聚类（DBSCAN）是Martin Ester，Hans-Peter Kriegel，JörgSander和Xiaowei Xu于1996年提出的数据聚类算法。它是一种基于密度的聚类算法：给定一些空间中的一组点，它将紧密堆积在一起的点（具有许多邻近邻居的点）组合在一起，标记为单独位于低密度区域的离群点（最近的点）邻居们太远了）。 DBSCAN是最常见的聚类算法之一，也是科学文献中引用最多的算法。 2014年，该算法在领先的数据挖掘会议KDD上获得了时间奖的测试（在理论和实践中获得了大量关注的算法奖）。
<!-- more -->

# 2. Python编程实现DBSCAN算法
**DBSCAN算法主要分为以下步骤实现**：
- S1.任意选择一个未访问过的点 P
- S2.标记点 P为已访问
- S3.计算得到所有从p 关于 Eps 和 MinPts 密度可达的点的集合 NeighborPts
- S4.若 P 不是核心对象，标记点 P 为噪声，跳转步骤S1重新选取 P；若 P 为核心对象，则扩展当前核心对象 P 的所属簇（expandCluster函数）
- S5.判断是否所有点均已被访问，若是则跳转S6; 若否则继续 S1 ~ S5步骤
- S6.DBSCAN算法运行结束，返回二维分类数组Cluster

# 3. DBSCAN算法Python代码实现如下：
```Python
# 基于密度的DBSCAN算法
def DBSCAN(data, Eps, MinPts):
    print('开始DBSCAN...')
    # 创建一个同规模数组，记录每个点的 分类、是否访问
    classification = np.ones(len(data)) * NoVisitedValue  # 存储是否访问及分类信息: -3，未访问； -2，噪声点；
    Cluster = [] #记录分簇信息，第i行存储所有归类于第i簇的元素下标

    while(True):
        # 选择一个 未访问的 点 P
        P = chooseOneNoVisitedP(data, classification)
        if (P == isAllVisitedValue): #已经全部遍历，退出While循环
            break;
        # # 若点 P 已被访问，跳过（注释，包含点P）
        # if (isVisited(classification, P) == True):
        #     continue
        #  若点 P 未被访问， 标记 P 为已访问
        classification[P] = VisitedValue
        NeighborPts = regionQuery(data, P, Eps)
        # print(P,'\'s NeighborPts is: ', NeighborPts)
        if (len(NeighborPts) < MinPts):  # 若 P非核心对象
            #标记 P 为 NOISE
            classification[P] = NoiseValue
        else:
            # print('扩展当前核心对象 P = ', P, '的所属簇')
            classification, Cluster = expandCluster(data, classification, P, NeighborPts, Cluster, Eps, MinPts)

    return Cluster
```

## 3.1. DBSCAN算法中的关键函数--expandCluster函数实现步骤：
- S1.将当前核心对象 P 添加到新的 P 的所属类Cluster_P中
- S2.从点 P 的邻域列表 NeighborPts 中取一个点 P'
- S3.判断点 P' 是否已被访问。若已被访问，跳转步骤S7；若未被访问，继续执行下一步骤
- S4.标记点 P' 为已被访问，并计算得到所有从P' 关于 Eps 和 MinPts 密度可达的点的集合 NeighborPts_i
- S5.判断点 P' 是否为核心对象，若是，将 P' 的邻域内点 NeighborPts_i 非重复地添加到点 P 的扩展邻域列表NeighborPts中；若否，继续执行下一步骤
- S6.判断点 P' 是否已经被分类，若否，添加点 P' 到列表 Cluster_P 中；若是，继续执行下一步骤
- S7.判断是否 P 扩展邻域列表 NeighborPts 中的所有元素均已被访问，若否，则循环步骤 S2 ～ S7; 若是，继续执行下一步骤
- S8.将列表 Cluster_P 添加到总分类列表 Cluster 中

## 3.2. expandCluster函数Python代码实现如下：
```Python
# 扩展当前核心对象 P 的所属簇
def expandCluster(data, classification, P, NeighborPts, Cluster, Eps, MinPts):
    Cluster_P = []
    Cluster_P += [P] #将核心对象添加到 P 的临时所属簇
    # 遍历点 P 的所有 NeighborPts， 这个NeighborPts可能会增加
    i = 0
    while(True):
        # 若邻域内的 P' 正好是 P，跳过
        if (NeighborPts[i] == P):
            i = i + 1
            # 若所有 NeighborPts 均已遍历，退出while
            if (i >= len(NeighborPts)):
                break
            else:
                continue # 跳过
        # 若 P' 未访问
        if (isVisited(classification, NeighborPts[i]) == False):
            classification[NeighborPts[i]] = VisitedValue # 标记 P' 已访问
            NeighborPts_i = regionQuery(data, NeighborPts[i], Eps) # 求 P' Eps邻域内的点
            if (len(NeighborPts_i) >= MinPts): # 若 P' 也为 核心对象
                NeighborPts = addNeighborPts(NeighborPts, NeighborPts_i) #增加P' Eps邻域内的点到 点 P 的邻域元素 NeighborPts中

            # 若 P' 不属于任何一个已有类(将当前邻域内元素添加到核心对象 P 的所属簇)
            if (isNoBelongsToAnyCluster(Cluster, Cluster_P, NeighborPts[i]) == True):
                Cluster_P += [NeighborPts[i]]

        i = i + 1
        # 若所有 NeighborPts 均已遍历，退出while
        if (i >= len(NeighborPts)):
            break

    Cluster += [Cluster_P]
    return classification, Cluster
```

# 4. DBSCAN算法执行、参数调整并分析
## 4.1. 显示聚类前后对比图函数
```Python
# 显示聚类前后对比图（最多表示8种颜色的集群）
def showClusterImage(data, Cluster, Eps, MinPts):
    num_Cluster = len(Cluster) # 分类个数

    # 绘制第 i 个类的 颜色列表
    # b--blue, c--cyan, g--green, k--black
    # m--magenta, r--red, w--white, y--yellow
    color = ['b', 'c', 'g', 'k', 'm', 'r', 'w', 'y']
    # 绘制第 i 个类的 形状列表
    mark = ['.', 'o', '^', '1', '8', 's', 'p', '*', 'h', '+', 'D']
    if num_Cluster > len(color):
        print('Sorry! Your len(Cluster)=', len(Cluster), ' is too large!( > len(color)=', len(color), ')')
        return 1

    # 绘制图片
    fig = plt.figure(figsize=(10, 4), facecolor='white')
    fig.suptitle('Eps='+str(Eps)+', MinPts='+str(MinPts)+'  Result Cluster='+str(len(Cluster)), fontsize=12, color='k')
    fig.gca().xaxis.set_major_locator(plt.NullLocator())
    fig.gca().yaxis.set_major_locator(plt.NullLocator())


    # 创建子图1: 绘制原图
    ax1 = fig.add_subplot(1, 2, 1)
    len_data = len(data)
    x = []
    y = []
    for i in range(len_data):
        x += [data[i][0]]
        y += [data[i][1]]
    ax1.scatter(x, y, s=4, c='k')
    # 设置标题并加上轴标签
    ax1.set_title('Original Graph', fontsize=10, color='k')
    # 设置坐标的取值范围
    ax1.axis(getMinMaxXandY(data))


    # 创建子图2: 绘制DBSCAN
    ax2 = fig.add_subplot(1, 2, 2)
    # 分别绘制不同 类别点
    for i in range(len(Cluster)):
        # 提取第 i 个类别的(x, y)坐标
        x = []
        y = []
        for j in range(len(Cluster[i])):
            x += [data[Cluster[i][j]][0]]
            y += [data[Cluster[i][j]][1]]
        # 对第 i 个类别内所有点 以不同颜色绘制
        ax2.scatter(x, y, s=4, c=color[i], marker=mark[i])
    ax2.set_title('DBSCAN Graph', fontsize=10, color='k')
    # 设置坐标的取值范围
    ax2.axis(getMinMaxXandY(data))

    plt.show() # 显示绘制图像
```
## 4.2. 主函数
```Python
# main函数
if __name__ == '__main__':
    # 加载long.mat数据
    data = loadDataFile('long.mat')
    data = data['long1'] #Eps=0.15， MinPts=8，最终分类数：2
    
    # DBSCAN两个重要参数
    Eps = 0.15 #邻域半径
    MinPts = 8 #邻域内元素个数（包括点P）
    Cluster = DBSCAN(data, Eps, MinPts) # 执行 DBSCAN 算法，返回聚类后的下标二维数组
    print('All Done')
    PrintCluster(Cluster) # 打印簇信息
    showClusterImage(data, Cluster, Eps, MinPts) # 绘制基于密度的DBSCAN算法后的效果图
```

## 4.3. long.mat文件的DBSCAN算法聚类效果
尝试设置Eps#邻域半径、MinPts#邻域内元素个数（包括点P）两个参数，由于Eps及MinPts两个参数没设置好导致被分成许多类，不方便绘图显示每个类。调试参数时也确认了两个参数设置的重要性，参数对分类结果的影响如下：
- 当设置Eps=0.08, MinPts=7时已经能够成功绘制图形，但数据被分成6个类，效果不是很理想，如下图所示
![Eps=0.08,MinPts=7的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_longEps=0.08MinPts=7ResultCluster=6.png)
分析：虽然能从图中明确看出被分成6个类，但视觉分析应该分成2个类更合适，间接说明分类数过多，表明在扩展其中两个大类时与另外两个类“断开了”，下面分别尝试增加领域半径Eps值、减小MinPts#邻域内元素个数，尝试让小类与大类“连接”起来。
- 当只增加领域半径Eps值，MinPts不变，设置Eps=0.1, MinPts=7，分类结果如下图所示
![Eps=0.1,MinPts=7的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_longEps=0.1MinPts=7ResultCluster=3.png)
分析：增加领域半径Eps值已有明显效果，此时分类数为3，继续尝试增大领域半径Eps值
- 继续增大Eps值直到Eps=0.18, MinPts=7时才能被分为两类，分类结果如下图所示
![Eps=0.18,MinPts=7的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_longEps=0.18MinPts=7ResultCluster=2.png)
分析：虽然此时按密度被成功聚类为2类，但相比之下每个类变得更“松散”，包括了许多不需要的边界非核心对象
- 当只减小MinPts，领域半径Eps值不变，设置Eps=0.08, MinPts=5时，数据分类数为5，如下图所示
![Eps=0.08,MinPts=5的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_longEps=0.08MinPts=5ResultCluster=5.png)
分析：一味只减少MinPts并没有得到很好的聚类结果，尝试减少MinPts并不能实现只分为两类的效果
- 综合调节Eps邻域半径大小与MinPts邻域内元素个数，设置Eps=0.15, MinPts=8时分类数为2，分类结果如下图所示
![Eps=0.15,MinPts=8的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_longEps=0.15MinPts=8ResultCluster=2.png)
分析：联合调整参数Eps和MinPts比只更改单一变量更难调节，在能够分类成2个类的结果下，Eps邻域半径越小、MinPts邻域内元素个数越小，得到的聚类内部对象间隔越“紧密”


## 4.4. 其他文件数据的DBSCAN聚类结果
由于调整Eps#邻域半径、MinPts#邻域内元素个数参数方法与上面一致，为直观显示效果，只给出聚类较理想的结果图及其对应Eps、MinPts参数

### 4.4.1. moon.mat文件的DBSCAN算法聚类效果
当设置Eps=0.11, MinPts=5时，数据被分成2个类，效果较理想，如下图所示
![Eps=0.11,MinPts=5的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_moonEps=0.11MinPts=5ResultCluster=2.png)

### 4.4.2. sizes5.mat文件的DBSCAN算法聚类效果
当设置Eps=1.32, MinPts=10时，数据分类数Cluster=4，效果较理想，如下图所示
![Eps=1.32,MinPts=10的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_sizes5Eps=1.32MinPts=10ResultCluster=4.png)

### 4.4.3. smile.mat文件的DBSCAN算法聚类效果
当设置Eps=0.08, MinPts=10时，数据分类数Cluster=3，效果较理想，如下图所示
![Eps=0.08,MinPts=10的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_smileEps=0.08MinPts=10ResultCluster=3.png)

### 4.4.4. spiral.mat文件的DBSCAN算法聚类效果
当设置Eps=1, MinPts=8时，数据分类数Cluster=2，效果较理想，如下图所示
![Eps=1,MinPts=8的效果图](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DataMining_DBSCAN_spiralEps=1MinPts=8ResultCluster=2.png)


{% note success %}
**备注**
**运行平台**：Arch Linux
**运行环境**：Intellij IDEA
**待聚类数据集文件**：[long.mat](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/long.mat)、[moon.mat](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/moon.mat)、[sizes5.mat](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/sizes5.mat)、[smile.mat](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/smile.mat)、[spiral.mat](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/spiral.mat)
**源代码**：[DensityBasedClustering.py](https://eisenhao.coding.net/p/eisenhao/d/eisenhao/git/raw/master/uploads/DensityBasedClustering.py)
{% endnote %}
