## 滤波

PCL中点云滤波方案
1. 点云数据密度不规则需要平滑
2. 音王遮挡等问题造成离群点需要去除
3. 大量数据需求进行下采样
4. 噪声数据需要去除


***

pcl_filters库提供类对噪声和离群点去除的具体实现.filter模块依赖于:

* pcl::common
* pcl::sample_consensus
* pcl::search
* pcl::kdtree
* pcl::octree


## 点云分割

聚类分割的基本原理为:考察m个数据点,在m维空间内定义点与点之间某种性质的亲疏聚类,设m个数据点组成n类,然后将具有最小距离的两类合为一类,并重新计算类与类之间的距离,迭代直到任意两类之间的距离大于指定的阈值,或者类的个数小于指定的数目,完成分割.


Segmentation库提供类点云分割的基础数据结构和部分通用的分割算法.依赖于pcl::common pcl::search pcl::sample_consensus pcl::kdtree pcl::octree


Segmentation 模块中类的介绍

