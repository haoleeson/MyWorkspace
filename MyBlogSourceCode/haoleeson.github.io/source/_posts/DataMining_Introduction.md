layout: post
title: 数据挖掘简介与发展动向
date: 2018/9/27 19:20:30
updated: 2019/2/18 13:21:45
comments: true
tags:
- 数据挖掘
categories:
- 算法

---
<img src="../../../../uploads/DataMining_Introduction.jpg" class="full-image" />

{% centerquote %}
Data mining, the science of extracting useful knowledge from such huge data repositories, has emerged as a young and interdisciplinary field in computer science.  -- by **KDD**
{% endcenterquote %}

# 1. 数据挖掘简介

<!-- more -->

- 数据挖掘是一个动态的、强势快速扩展的领域。可简要将数据挖掘研究的主要问题分为五组：挖掘方法、用户交互、有效性与可伸缩性、数据类型的多样性、数据挖掘与社会。
- 数据挖掘吸纳了诸如**统计学**、**机器学习**、**模式识别**、**数据库和数据仓库**、**信息检索**、**可视化**、**算法**、**高性能计算**和许多应用领域的大量技术。

## 1.1. 数据挖掘的意义

- 利用大数据帮助做出**预测**或**决策**
- 发现数据中潜在的**有趣模式**或**知识**

# 2. 最新技术与发展动向

## 2.1. 数据挖掘最新技术

- 超越传统技术和数据分析工具的能力的数据集催生了许多新的技术和工具--by[Information granularity, big data, and computational intelligence](https://link.springer.com/content/pdf/10.1007/978-3-319-08254-7.pdf)

面对数据挖掘中3V的挑战（即：超大数据量、多样化的数据种类、处理数据的速度要求），如大型零售商的客户交易，天气监测，情报收集等数据集快速超越传统技术和数据分析工具的能力等问题，驱使数据可视化，采集和序列化中诞生了许多新的技术和工具。

### 2.1.1. 数据预处理技术

数据清理、数据集成、数据归约、数据变换和数据离散化。

- Deren Li methods 2015，为了揭示空间数据挖掘的各向异性，挖掘视图方法利用尺度、层次和粒度来区分不同的需求。Deren Li方法对数据进行预处理，为进一步的知识发现做准备，方法是选择一个权重进行迭代，以便尽可能多地清理观察到的空间数据。--by[Spatial data mining](https://link.springer.com/content/pdf/10.1007/978-3-662-48538-5.pdf)

### 2.1.2. 数据仓库、OLAP、数据立方体技术

**数据仓库**：是一种数据库，它与单位的操作数据库分别维护。数据仓库的建立为工商企业主管提供了体系结构和工具，以便他们系统地组织、理解和使用数据进行决策。

**OLAP**：OLAP是在线分析处理的缩写。OLAP实现业务数据的多维分析，并提供复杂计算、趋势分析和复杂数据建模的能力。

**数据立方体**：一种多维数据模型。数据立方体创建了灵活而强有力的手段，对数据的子集分组和聚集。它们使得用户可以在多维组合和变化的聚集粒度上探索数据。这种能力极大地开阔了分析的范围，有助于从数据中有效地发现有趣的模式和知识。

### 2.1.3. Apriori算法及其变形

Apriori是一种用于在事务数据库上进行频繁项集挖掘和关联规则学习的算法。 它通过识别数据库中的频繁单个项目并将它们扩展到越来越大的项目集来进行，只要这些项目集在数据库中经常出现。

### 2.1.4. 基于约束模式挖掘和挖掘近似模式

一种好的启发式方法是让用户说明他们对挖掘导致的有趣模式的直观或期望，作为限制搜索空间的约束条件。这种策略称为基于约束的挖掘。

### 2.1.5. 分类

**基本分类方法**：包括决策树归纳、贝叶斯分类和基于规则的分类。

**高级分类方法**：贝叶斯信念网络、后向传播的神经网络技术、支持向量机、使用频繁模式的分类、k-最邻近分类、基于案例的推理、遗传算法、模糊集方法、多类分类、半监督分类、主动学习和迁移学习。

#### 2.1.5.1. 数据挖掘中的分类算法对比

分类是一种重要的数据挖掘技术，具有广泛的应用前景。分类用于找出在给定数据集中每个数据实例在哪个组中相关。分类算法主要有：**C4.5**、**ID3**、**k近邻分类器**、**朴素贝叶斯**、**SVM**、**ANN**等。分类技术一般采用统计方法、机器学习方法和神经网络方法进行分类。Nikam对不同的分类算法及其特点和局限性进行了全面的综述。

-- [A comparative study of classification techniques in data mining algorithms](https://pdfs.semanticscholar.org/7c97/57ee09afa570db37f04e3b6cc4da0e2f3571.pdf)

![AdvantagesAndDisadvantagesOfClassificationAlgorithm](../../../../uploads/AdvantagesAndDisadvantagesOfClassificationAlgorithm.png)

- 基于**神经网络**和**遗传算法**的数据挖掘技术

**Ali, Sayyed Muzammil**概述了常见的知识发现任务以及解决这些任务的方法。总结了数据挖掘的概念，阐述了数据挖掘对其方法论的意义。详细研究了基于神经网络和遗传算法的数据挖掘技术，综述了实现神经网络和遗传算法数据挖掘的关键技术和方法。

-- [data mining Techniques](http://www.academia.edu/download/33555810/V3I4201499a89.pdf)

### 2.1.6. 聚类分析

**基本聚类分析**：

- k-均值和k-中心点划分算法、凝聚的与分裂的层次聚类算法、
- 基于密度的DBSCAN、OPTICS、DENCLUE聚类分析
- 基于网络的STING、CLIQUE聚类分析

**高级聚类分析**：

- 基于概率模型的模糊簇、期望最大化算法的聚类分析
- 子空间聚类方法、双聚类（聚类高维数据）
- SCAN算法（用于聚类图数据）
- 具有约束的COP-k-均值算法

- 数据挖掘问题的**多目标进化算法**的最新进展

**Mukhopadhyay, Anirban**对数据挖掘问题的多目标进化算法的最新进展进行了全面的综述。本文第一部分给出了多目标优化和数据挖掘的一些基本概念。随后，对两大数据挖掘任务特征选择和分类的多目标演化方法进行了研究。在本文的第二部分中，我们调查了用于聚类、关联规则挖掘等多个数据挖掘任务的不同多目标进化算法，并对该领域未来的研究范围进行了一般性讨论。

-- [A Survey of Multiobjective Evolutionary Algorithms for data mining: Part I.](https://ieeexplore.ieee.org/iel7/4235/4358751/06658835.pdf)

### 2.1.7. 基于随机选择选项的算法

有时基于**随机选择选项**的算法收效良好。在数据挖掘和控制领域，当一个问题需要“蛮力”选择选项时，基于**随机选择选项**的算法在有限的时间内提供了一定概率的良好结果，并显著减少了操作量。

-- [A comparative study of classification techniques in data mining algorithms](https://pdfs.semanticscholar.org/7c97/57ee09afa570db37f04e3b6cc4da0e2f3571.pdf)

### 2.1.8. 流算法

- **APSO加速粒子群优化算法**

**Fong, Simon**为解决当涉及到在高维数据上的挖掘时，获得最优特征子集的搜索空间以指数级增长，这导致了计算上的一个棘手需求这一问题，**提出了一种新的轻量级特征选择方法**。该特征选择是为了实时挖掘流数据，采用加速粒子群优化算法(APSO)，在合理的处理时间内提高了分析精度。

-- [Accelerated PSO swarm search feature selection for data stream mining big data](https://ieeexplore.ieee.org/iel7/4629386/4629387/07115942.pdf)

### 2.1.9. 分布式数据挖掘

**Le-Khac, Nhien-An**提出了一个新的框架，开发新的和创新的数据挖掘技术，以处理非常大的分布式异构数据集在商业和学术应用。详细介绍了其中的主要组件及其接口，允许用户在Globus ToolKit、DGET等网格平台上高效地开发和实现其数据挖掘应用程序技术。

 -- [ADMIRE framework: Distributed data mining on data grid platforms](https://arxiv.org/abs/1703.09756)

**Janez Kranjc**介绍了一种分布式计算平台，利用最新的软件技术和计算范式开发出了支持大数据挖掘的平台。这个平台称为ClowdFlows，它是一个基于云的web应用程序，具有图形用户界面，支持数据挖掘工作流的构建和执行，其中包括作为工作流组件使用的web服务。

 -- [ClowdFlows: Online workflows for distributed big data mining](https://www.sciencedirect.com/science/article/pii/S0167739X16302709)

## 2.2. 数据挖掘发展动向

### 2.2.1. 与物联网相结合

对许多人来说，物联网生成或捕获的海量数据被认为具有非常有用和有价值的信息。数据挖掘无疑将在使这种系统足够智能以提供更方便的服务和环境方面发挥关键作用。
**Chun-Wei Tsai**从物联网开始讨论，简要回顾了“物联网数据”和“物联网数据挖掘”的特点，最后，讨论了该领域的变化、潜力、开放问题和未来趋势。

-- [data mining for Internet of Things: A survey.](https://ieeexplore.ieee.org/iel7/9739/6734839/06674155.pdf)

### 2.2.2. 基于云计算的数据挖掘更低成本

数据挖掘技术和应用程序可以有效地用于云计算范式。云计算是一种能够支持广泛应用的通用技术。基于云计算的数据挖掘技术的实现将允许用户从几乎集成的数据仓库中检索有意义的信息，从而**降低基础设施和存储的成本，并且可以从云检索有用的和潜在的信息。

-- [A review on data mining based cloud computing](http://ijrise.org/asset/archive/15SANKALP1.pdf)

### 2.2.3. 与统计与机器学习结合

-- [Data mining for business analytics: concepts, techniques, and applications in R](https://books.google.com/books?hl=en&lr=&id=ETwuDwAAQBAJ&oi=fnd&pg=PR19&dq=data+mining+Development+trend&ots=2NWgjl2RLK&sig=sQBatbtbXqXyebsmDBRzPVYNL_8)

### 2.2.4. 数据挖掘实现的集成库及平台化

- **SPMF——一个开源数据挖掘库** 2014

**Fournier-Viger**提供了一个用Java实现的跨平台库——**SPMF**，一个开源数据挖掘库**，提供了超过55种数据挖掘算法的实现。
SPMF专门用于发现事务和序列数据库中的模式，如频繁项目集、关联规则和顺序模式。
源代码可以集成到其他Java程序中。
此外，SPMF还提供了命令行界面和简单的图形界面来进行快速测试。

-- [SPMF: a Java open-source pattern mining library](http://www.jmlr.org/papers/volume15/fournierviger14a/fournierviger14a.pdf)

- **SAMOA——一个挖掘大数据流的平台** 2015

**Morales GD**提供了一个挖掘大数据流的平台——**SAMOA**。它提供了一组分布式流算法，用于最常见的数据挖掘和机器学习任务，如分类、聚类和回归，以及开发新算法的编程抽象。它具有一个可插入的体系结构，允许它在多个分布式流处理引擎(如Storm、S4和Samza)上运行。萨摩亚是用Java编写的，是开源的，可以在http://samoa-project.net的Apache Software License version 2.0下访问。

-- [SAMOA: scalable advanced massive online analysis.](http://www.jmlr.org/papers/volume16/morales15a/morales15a.pdf)

- 与应用相结合 
- 研制和开发数据挖掘标准 
- 支持移动环境  


# 3. 应用领域及行业应用
## 3.1. 应用领域

**数据挖掘有许多成功的应用，如电子商务、Web搜索、生物信息学、卫生保健信息学、商务智能、金融、数字图书馆和政府等。**


## 3.2. 行业应用
### 3.2.1. 动态资源的新闻识别

**Kalmegh, Sushilkumar**讨论了动态资源的新闻识别可以通过所提出的模型来完成，使用REPTree、Simple Cart和RandomTree三种分类器来分析数据集。结果表明，随机树算法在对新闻进行分类时表现最佳。REPTree和Simple Cart算法的整体性能是不可接受的，因为可以看出，这两种算法都只能正确地对政治新闻进行分类。

-- [Analysis of WEKA data mining algorithm REPTree, Simple CART and RandomTree for classification of Indian news](https://pdfs.semanticscholar.org/26d6/73f140807942313545489b38241c1f0401d0.pdf)

### 3.2.2. 教育数据挖掘(EDM)领域
- 教育数据挖掘和学习分析

**Sin, Katrina**近年来，学习管理系统在教育中的应用越来越多。学生们已经开始使用移动电话，主要是智能手机，它们已经成为他们日常生活的一部分，以获取在线内容。学生的在线活动产生了大量未使用的数据，由于传统的学习分析无法处理这些数据，这些数据被浪费了。这使得大数据技术和工具渗透到教育中，处理大量的数据。本研究探讨了大数据技术在教育领域的最新应用，并对教育数据挖掘和学习分析方面的文献进行了综述。

-- [APPLICATION OF BIG data IN EDUCATION data mining AND LEARNING ANALYTICS--A LITERATURE REVIEW.](http://www.academia.edu/download/51542496/APPLICATION_OF_BIG_DATA_IN_EDUCATION_DAT.pdf)

- 挖掘学生入学率、考勤记录以及他们的考试数据，使之有利于教育质量的改进与提高。

--  [A systematic review on educational data mining](https://ieeexplore.ieee.org/iel7/6287639/6514899/07820050.pdf)

### 3.2.3. 地理信息科学和遥感方面

- 空间数据挖掘应用于**地理信息科学和遥感方面**

**Li, Deren**提供了空间数据挖掘在地理信息科学和遥感方面的应用实例。实践项目包括用于维护公共安全的时空视频数据挖掘、用于评估叙利亚危机严重程度的夜间灯光序列图像挖掘、以及在政府“一带一路”项目中的应用。

-- [Spatial data mining](https://link.springer.com/content/pdf/10.1007/978-3-662-48538-5.pdf)

### 3.2.4. 医疗大数据

- 医疗大数据创新路径包括三个阶段：疾病早期发现、诊断、治疗和预后阶段、生命健康促进阶段和护理阶段。
- 研究热点主要集中在三个维度：疾病维度(如流行病学、乳腺癌、肥胖、糖尿病)、技术维度(如数据挖掘、机器学习)、健康服务维度(如定制服务、养老护理)

 -- [Visualizing the knowledge structure and evolution of big data research in healthcare informatics](https://www.sciencedirect.com/science/article/pii/S1386505616302556)
- 与云技术结合提供医疗服务

**Zhang, Yin**提出了一个基于云和大数据分析技术的以患者为中心的医疗应用和服务的网络物理系统，称为Health-CPS。该系统由具有统一标准的数据采集层、用于分布式存储和并行计算的数据管理层和面向数据的服务层组成。研究结果表明，云技术和大数据技术可以提高医疗系统的性能，使人们可以享受各种智能医疗应用和服务。

 -- [Health-CPS: Healthcare cyber-physical system assisted by cloud and big data](https://ieeexplore.ieee.org/abstract/document/7219371/)

- 医学大数据研究的文献计量分析与可视化 --[**A bibliometric analysis** and **visualization** of **medical big data research**](https://www.mdpi.com/2071-1050/10/1/166)
- 预测和解决乳腺癌生存率 --[Data mining techniques: To predict and resolve breast cancer survivability](https://papers.ssrn.com/sol3/papers.cfm?abstract_id=2994925)

### 3.2.5. 能源评估
- 全球水资源趋势和可持续发展的未来前景 --[Global water **trends** and future scenarios for sustainable development: The case of Russia](https://www.sciencedirect.com/science/article/pii/S0959652617321182)
- 对智能电网环境下用电量数据的数据质量分析 --[data quality of electricity consumption data in a smart grid environment](https://www.sciencedirect.com/science/article/pii/S1364032116307109)

### 3.2.6. 业务运营和风险管理
- 工业系统的可靠性和安全性以及它们的操作风险管理 --[Recent development in big data analytics for business operations and risk management](https://ieeexplore.ieee.org/abstract/document/7378465/)
- 业务分析的数据挖掘 --[Data mining for business analytics: concepts, techniques, and applications in R](https://books.google.com/books?hl=en&lr=&id=ETwuDwAAQBAJ&oi=fnd&pg=PR19&dq=data+mining+Development+trend&ots=2NWgjl2RLK&sig=sQBatbtbXqXyebsmDBRzPVYNL_8)

### 3.2.7. 用于保险行业
数据挖掘技术在人寿保险中的应用 --[Applications of Data mining techniques in life insurance](https://www.researchgate.net/institution/Chh_Shahu_Institute_of_Business_Education_Research/publications)

### 3.2.8. 用于政府机构
- 可持续自然资源管理评价污染防治 --[How would big data support societal development and environmental sustainability? Insights and practices](https://www.sciencedirect.com/science/article/pii/S0959652616317115)
