>perception/lib/base/concurrent_queue.h
---
std::mutex的成员函数
* lock()调用线程将锁住该互斥量
* unlock()解锁,释放对互斥量的所有权
*try_lock()尝试锁住互斥量
对于mutex的二次开发
>perception/lib/base/mutex.h 同上

>perception/lib/base/noncopyable.h

define DISALLOW_COPY
define DISALLOW_ASSIGN
define DISALLOW_COPY_AND_ASSIGN
define DISALLOW_IMPLICIT_CONSTRUCTORS

>perception/lib/base/registerer.h

define REGISTER_REGISTERER(base_class) class base_class##Registerer

define REGISTER_CLASS(clazz, name) class ObjectFactory##name : public apollo::perception::ObjectFactory

inline函数: RegisterFactory##name

>perception/lib/base/singleton.h

singleton单线程模式

>perception/lib/base/thread.h
多线程方法


>perception/obstacle/base/hdmap_struct.h

HdmapStructPtr
HdmapStructConstPtr

>perception/obstacle/base/object_supplement.h
>perception/obstacle/base/object.h
>perception/obstacle/base/types.h


>perception/obstacle/common/hungarian_bigraph_matcher.h 匈牙利算法
>perception/obstacle/common/pose_util.h 
* ReadPoseFile 
* ReadPoseFileMat12  
* LoadExtrinsic  



>perception/obstacle/lidar/dummy/dummy_algorithms.h
* Filter
* Detect
* Segment
* BuildObject
通过dummy_algorithms连接到interface的方法上.

>perception/obstacle/lidar/interface/

* base_ground_detector
struct GroundDetectorOptions
class BaseGroundDetector Detect 
#define REGISTER_GROUNDDETECTOR(name) REGISTER_CLASS(BaseGroundDetector, name)

```
//Register plugin.
REGISTER_OBJECTBUILDER(MyObjectBuilder);

BaseObjectBuilder* object_builder = BaseObjectBuilderRegisterer:get_instance_by_name("MyObjectBuilder");
```
* base_object_builder
struct BaseObjectBuilder
SetDefaultValue(pcl_util::PointCloudPtr cloud,
               std::shared_ptr<Object> obj,
               Eigen::Vector4f* min_pt,
               Eigen::Vector4f* max_pt){};
* base_object_filter
struct ObjectFilterOptions
* base_roi_filter
* base_segmentation
struct SegmentationOptions
struct TrackerOptions

>perception/obstacle/lidar/object_builder/min_box


class MinBoxObjectBuilder : public BaseObjectBuilder


---
eigen教程

Eigen是C++中可以用来调用并进行矩阵计算的一个库，简单了说它就是一个c++版本的matlab包。

Eigen库被分为一个Core模块和其他一些模块，每个模块有一些相应的头文件。 为了便于引用，Dense模块整合了一系列模块；Eigen模块整合了所有模块。一般情况下，include<Eigen/Dense> 就够了。


---