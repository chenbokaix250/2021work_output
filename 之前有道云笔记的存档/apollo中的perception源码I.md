>perception/perception.h

```
class Perception : public common::ApolloApp {
 public:
  std::string Name() const override;//模块名
  common::Status Init() override;//初始化
  common::Status Start() override;//模块工作内容
  void Stop() override;//清理函数

 private:
  DAGStreaming dag_streaming_;
  void RegistAllOnboardClass();
};
```
执行`apollo/modules/perception/main.cc`时
APOLLO_MAIN的函数原型在`apollo/modules/common/apollo_app.h`

---
此处用到了define的多行定义  
`
```
#include <string>  
#include <string.h>  
#include <iostream>  
using namespace std;  
#define mydefine(arg1,arg2,...) do {  \  
    printf("Hello");\  
    printf("World");\  
    printf(arg1);\  
    printf(arg2);\  
}while(0)  
  
int main()  
{  
    mydefine(" I ","am");     
    return 0;  
}  
```
关键是要在每一个换行的时候加上一个"\"
---
APP实例化的apollo_app_即为返回的perception 
调用Spin() apollo/modules/common/apollo_app.cc

Spin对应的perception继承自apollo_app.Spin的方法在apollo_app

---
### ROS中的 spinning
##### 最简单最常用的单线程为：ros::spin()
```
ros::init(argc, argv, "my_node");
ros::NodeHandle nh;
ros::Subscriber sub = nh.subscribe(...);
...
ros::spin();
```
##### 周期性的 ros::spinOnce()
```
ros::Rate r(10); // 10 hz
while (should_continue)
{
  ... do some work, publish some messages, etc. ...
  ros::spinOnce();
  r.sleep();
}
```
##### ros::MultiThreadedSpinner
```
ros::MultiThreadedSpinner spinner(4); // Use 4 threads
spinner.spin(); // spin() will not return until the node has been shutdown
```
阻塞式线程，类似于ros::spin(),你可以在它的构造器上指定一定数量的线程数，但如果不指定或设置为0，则会在每个CPU上执行一个线程。

##### ros::AsyncSpinner
```
ros::AsyncSpinner spinner(4); // Use 4 threads
spinner.start();
ros::waitForShutdown();
```
一个更有用的线程。它不用spin() 回调，而用start()和stop()，当它销毁时候就会自动关闭.

##### 回调序列
```
#include <ros/callback_queue.h>
ros::CallbackQueue my_queue;
```
CallbackQueue 有两种方法调用回调函数： callAvailable() 和callOne()。

callavailable()调用队列里所有的。callone()只会调用回调在队列最旧的。

callAvailable()和callOne()都会有一个超时选项，在返回前，它会在超时时间内等待回调有效。

如果是0，同时队列没有回调，则直接返回。

##### 高级回调序列

```
ros::AsyncSpinner spinner(0, &my_callback_queue);
spinner.start();

my_callback_queue.callAvailable(ros::WallDuration());

ros::AsyncSpinner spinner(0, &my_callback_queue);
spinner.start();

ros::MultiThreadedSpinner spinner(0);
spinner.spin(&my_callback_queue);
```
---

Perception执行Init时的过程:

RegistAllOnboardClass()

实例 config_manager

dag_config_path 获取执行路径 config_path

RegistAllOnboardClass中的函数来自register.h的宏定义

eg:
 RegisterFactoryLidarObjectData();
 RegisterFactoryLidarProcessSubnode();


```
#define REGISTER_CLASS(clazz, name)                                           \
  class ObjectFactory##name : public apollo::perception::ObjectFactory {      \
   public:                                                                    \
    virtual ~ObjectFactory##name() {}                                         \
    virtual perception::Any NewInstance() {                                   \
      return perception::Any(new name());                                     \
    }                                                                         \
  };                                                                          \
  inline void RegisterFactory##name() {                                       \
    perception::FactoryMap &map = perception::GlobalFactoryMap()[#clazz];     \
    if (map.find(#name) == map.end()) map[#name] = new ObjectFactory##name(); \
  }
```


RegisterFactoryLidarProcessSubnode() 是由 #define REGISTER_SUBNODE(name) REGISTER_CLASS(Subnode, name)
宏定义决定的 name即为LidarProcessSubnode 从而REGISTER_CLASS(Subnode,LidarProcessSubnode)作用RegisterFactory##name的inline函数 


RegisterFactoryLidarObjectData() 是由 #define REGISTER_SHAREDDATA(name) REGISTER_CLASS(SharedData, name)
宏定义决定的 name即为LidarObjectData 
从而REGISTER_CLASS(SharedData, LidarObjectData)作用RegisterFactory##name的inline函数 


>perception/common/perception_gflags.h
gflags是一套命令行参数处理的开源库,暂时支持的类型:
```
DEFINE_bool: boolean
DEFINE_int32: 32-bit integer
DEFINE_int64: 64-bit integer
DEFINE_uint64: unsigned 64-bit integer
DEFINE_double: double
DEFINE_string: C++ string
```
利用gflag提供的宏定义参数该宏的3个参数分别为命令行参数名,参宿默认值,参宿的帮助信息
```
DEFINE_bool(big_menu, true, "Include 'advanced' options in the menu listing");
DEFINE_string(languages, "english,french,german", "comma-separated list of languages to offer in the 'lang' menu");
```

>perception/common/convex_hullxy.h
凸包:将最外层的点连接起来构成的凸多边形，它能包含点集中所有的点。
点云中使用的点包围函数库


>perception/common/geometry_util.h
* TransformPointCloud
* GetCloudMinMax3D
* ComputeBboxSizeCenter
* GetCloudBarycenter
* TransAffineToMatrix4
* ComputeMostConsistentBboxDirection
* VectorCosTheta2dXy
* VectorTheta2dXy
计算点云变换的相关方法

>perception/common/graph_util.h

* ConnectedComponentAnalysis

>perception/common/pcl_types.h 
pcl结构与类型

>perception/common/sequence_type_fuser/base_type_fuser.h
作为MyTypeFuser的基类

>perception/common/sequence_type_fuser/fuser_util.h
std::vector与Eigen::Matrix 的相互转换
* FromStdVector
* FromEigenVector
* ToLog
* ToExp
* Normalize
* NormalizeRow
* PrintProbability
加载单个HUOQU多个矩阵
* LoadSingleMatrix
* LoadSingleMatrixFile
* LoadMultipleMatricesFile

>perception/common/sequence_type_fuser/object_sequence.h
* AddTrackedFrameObjects
* GetTrackInTemporalWindow
* RemoveStaleTracks
处理帧数据 添加 获取 移除

>perception/common/sequence_type_fuser/sequence_type_fuser.h
继承base_type_fuser


---
c++ map常见用法

1. 声明: `#include <map>` 
```
//头文件
#include<map>

map<int, string> ID_Name;

// 使用{}赋值是从c++11开始的，因此编译器版本过低时会报错，如visual studio 2012
map<int, string> ID_Name = {
                { 2015, "Jim" },
                { 2016, "Tom" },
                { 2017, "Bob" } };
```
2. 插入操作 
* 使用[]进行单个插入 ID
```
map<int, string> ID_Name;

// 如果已经存在键值2015，则会作赋值修改操作，如果没有则插入
ID_Name[2015] = "Tom";
```
* 使用insert进行单个和多个插入
```
// 插入单个键值对，并返回插入位置和成功标志，插入位置已经存在值时，插入失败
pair<iterator,bool> insert (const value_type& val);

//在指定位置插入，在不同位置插入效率是不一样的，因为涉及到重排
iterator insert (const_iterator position, const value_type& val);

// 插入多个
void insert (InputIterator first, InputIterator last);

//c++11开始支持，使用列表插入多个   
void insert (initializer_list<value_type> il);
```
3. 容量查询
```
// 查询map是否为空
bool empty();

// 查询map中键值对的数量
size_t size();

// 查询map所能包含的最大键值对数量，和系统和应用库有关。
// 此外，这并不意味着用户一定可以存这么多，很可能还没达到就已经开辟内存失败了
size_t max_size();

// 查询关键字为key的元素的个数，在map里结果非0即1
size_t count( const Key& key ) const; //
```


4. 迭代器 begin/end rbegin/rend
5. 删除与交换
```
// 删除迭代器指向位置的键值对，并返回一个指向下一元素的迭代器
iterator erase( iterator pos )

// 删除一定范围内的元素，并返回一个指向下一元素的迭代器
iterator erase( const_iterator first, const_iterator last );

// 根据Key来进行删除， 返回删除的元素数量，在map里结果非0即1
size_t erase( const key_type& key );

// 清空map，清空后的size为0
void clear();
```

6. 顺序比较
```
// 比较两个关键字在map中位置的先后
key_compare key_comp() const;
```
```
map<char,int> mymap;
map<char,int>::key_compare mycomp = mymap.key_comp();

mymap['a']=100;
mymap['b']=200;
mycomp('a', 'b');  // a排在b前面，因此返回结果为true
```
7. 查找
```
// 关键字查询，找到则返回指向该关键字的迭代器，否则返回指向end的迭代器
// 根据map的类型，返回的迭代器为 iterator 或者 const_iterator
iterator find (const key_type& k);
const_iterator find (const key_type& k) const;
```
---

