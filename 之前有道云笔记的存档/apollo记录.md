### 关于apollo运行的一些记录


----apollo/modules/perception/main.cc

`APOLLO_MAIN(apollo::perception::Perception);`
命名空间中的类
----apollo/modules/common/apollo_app.h
```
#define APOLLO_MAIN(APP)                                       \
  int main(int argc, char **argv) {                            \
    google::InitGoogleLogging(argv[0]);                        \
    google::ParseCommandLineFlags(&argc, &argv, true);         \
    signal(SIGINT, apollo::common::apollo_app_sigint_handler); \
    APP apollo_app_;                                           \
    ros::init(argc, argv, apollo_app_.Name());                 \
    apollo_app_.Spin();                                        \
    return 0;                                                  \
  }
```
#define 多行定义 
  apollo_app_ 就是 perception子类 
  Name()方法返回的就是perception
  
Spin()方法来自 ApolloApp 而class ApolloApp是class perceptio的父类

----apollo/modules/common/apollo_app.cc
```
int ApolloApp::Spin() {
  auto status = Init();
  if (!status.ok()) {
    AERROR << Name() << " Init failed: " << status;
    return -1;
  }

  std::unique_ptr<ros::AsyncSpinner> spinner;
  if (callback_thread_num_ > 1) {
    spinner = std::unique_ptr<ros::AsyncSpinner>(
        new ros::AsyncSpinner(callback_thread_num_));
  }

  status = Start();
  if (!status.ok()) {
    AERROR << Name() << " Start failed: " << status;
    return -2;
  }
  ExportFlags();
  if (spinner) {
    spinner->start();
  } else {
    ros::spin();
  }
  ros::waitForShutdown();
  Stop();
  AINFO << Name() << " exited.";
  return 0;
}

```
然而 .h文件中对应的 init/start/stop方法是虚函数 要在子类中实现
```
virtual apollo::common::Status Init() = 0;

virtual apollo::common::Status Start() = 0;

virtual void Stop() = 0;
```
所以对应的perception对象 即在class perception中实现
init方法
```
Status Perception::Init() {
  AdapterManager::Init(FLAGS_perception_adapter_config_filename);

  RegistAllOnboardClass();
  if (!dag_streaming_.Init(FLAGS_dag_config_path)) {
    AERROR << "Failed to init DAGStreaming. dag_config_path:"
           << FLAGS_dag_config_path;
    return Status(ErrorCode::PERCEPTION_ERROR, "failed to Init DAGStreaming.");
  }
  callback_thread_num_ = 5;

  return Status::OK();
}
```
start和stop方法
```
Status Perception::Start() {
  dag_streaming_.Start();
  return Status::OK();
}

void Perception::Stop() {
  dag_streaming_.Stop();
  dag_streaming_.Join();
}
```
***
### perception的init过程
涉及到 类Status
将Init()的返回值定义为Status类型 在return时 
* 重构ErrorCode(有误)
* 返回Status::OK(无误)

init中先去执行AdapterManager的Init方法,参数为FLAGS_perception_adapter_config_filename
其参数的定义来自 
----apollo/modules/perception/common/perception_gflags.h 对应到.c中
```
DEFINE_string(perception_adapter_config_filename,
              "modules/perception/conf/adapter.conf",
              "The adapter config filename");
```
Adapter执行时,参数值即从modules/perception/conf/adapter.conf中进行读取
执行
apollo/modules/common/adapters/adapter_manager.cc
中的void AdapterManager::Init(const std::string &adapter_config_filename)()函数后
再执行void AdapterManager::Init(const AdapterManagerConfig &configs)();
这里有一个多态的概念.
在其中利用swith-case对config的type进行查找,然后对相应配置操作
例如`EnablePointCloud(FLAGS_pointcloud_topic, config);`
???????????????????//
利用单例模式 实例化对象
`void Perception::RegistAllOnboardClass()`
完成对
* LidarObjectData
* RadarObjectData
* CameraObjectData
* CameraSharedData
* CIPVObjectData
* LaneSharedData
* FusionSharedData
* SceneSharedData
* TLPreprocessingData 的实例化
相应Subnode的实例化:
Lidar64ProcessSubnode 等

然后对dag_streaming.config进行校验:
FLAGS_dag_config_path位置:
```
DEFINE_string(dag_config_path, "modules/perception/conf/dag_streaming.config",
              "Onboard DAG Streaming config.");
```
----apollo/modules/perception/onboard/dag_streaming.cc中
校验Event_manager 执行
----apollo/modules/perception/onboard/event_manager.cc中的Init
创建EventMeta的event_meta去接收event_pb的信息
包括(id/name/from_node/to_node) 返回的true再返回到perception.cc中返回
`Status::OK()`完成初始化.
***
### perception的start过程:
```
Status Perception::Start() {
  dag_streaming_.Start();
  return Status::OK();
}
```
perception.h中private 实例化了DAGStreaming类的dag_streaming_实例对象;
----apollo/modules/perception/onboard/dag_streaming.h中
`class DAGStreaming : public Thread`
Start方法也继承自Thread中

----apollo/modules/perception/lib/base/thread.cc中
Thread::Start()
`int result = pthread_create(&tid_, &attr, &ThreadRunner, this);`

Stop方法实现在
----apollo/modules/perception/onboard/dag_streaming.cc中实现
`pthread_cancel(pair.second->Tid());`主要方法


-----apollo/modules/perception/onboard/dag_streaming.h中
出现了`class DAGStreamingMonitor;`
而 `DAGStreaming`继承了Thread 又生产了
`std::unique_ptr<DAGStreamingMonitor> monitor_;`
而`DAGStreamingMonitor`是不允许COPY和ASSIGN的
`DISALLOW_COPY_AND_ASSIGN(DAGStreamingMonitor);`

----apollo/modules/perception/onboard/dag_streaming.cc中
```
DAGStreaming::DAGStreaming()
    : Thread(true, "DAGStreamingThread"),
      inited_(false),
      monitor_(new DAGStreamingMonitor(this)) {}
```
创建了minitor_则是Thread的子类对象 执行start方法

----apollo/modules/perception/onboard/dag_streaming.h中

subnode_map_是一个 `map<SubnodeID, std::unique_ptr<Subnode>>`
而subnode_name_map_ 是`map<std::string, SubnodeID>`

auto& pair将subnode_map_中的Start均执行
而内容就是----apollo/modules/perception/onboard/proto/dag_streaming.config

例如 当执行 
```
subnodes {
        id: 1
        name: "Lidar64InputNode"
    }
``` 
执行Thread中的Start方法 而subnode_map_内容来自
`bool DAGStreaming::InitSubnodes(const DAGConfig& dag_config) {}`

其中 DAGConfig来自
----apollo/modules/perception/onboard/proto/dag_config.proto
`message DAGConfig{...}`
通过InitSubnodes()函数:
`subnode_map_.emplace(subnode_id, std::unique_ptr<Subnode>(inst));`
emplace 约等于 push_back 将 id 和 指针传入
name在subnode_name_map_中


---

### 屡一下REGISTER的相关内容

----apollo/modules/perception/obstacle/lidar/dummy/dummy_algorithms.h
`REGISTER_OBJECTFILTER(DummyObjectFilter);`
来自定义:
----apollo/modules/perception/obstacle/lidar/interface/base_object_filter.h
`#define REGISTER_OBJECTFILTER(name) REGISTER_CLASS(BaseObjectFilter, name)`

REGISTER_CLASS(BaseObjectFilter, name) 中的BaseObjectFilter 是由 REGISTER_REGISTERER临时生成的 定义来自
----apollo/modules/perception/lib/base/registerer.h

REGISTER_CLASS的定义来自:
----apollo/modules/perception/lib/base/registerer.h

```
class ObjectFactoryDummyObjectFilter:public apollo::perception::ObjectFactory{
    public:                                                                   \
    virtual ~ObjectFactoryDummyObjectFilter() {}                              \
    virtual perception::Any NewInstance() {                                   \
      return perception::Any(new DummyObjectFilter());
}
```
完成了DummyObjectFilter对象的实例化
而DummyObjectFilter需要做的工作是
----apollo/modules/perception/obstacle/lidar/dummy/dummy_algorithms.h
其继承了BaseObjectFilter 
----apollo/modules/perception/obstacle/lidar/interface/base_object_filter.h
```
class BaseObjectFilter {
 public:
  BaseObjectFilter() {}
  virtual ~BaseObjectFilter() {}

  virtual bool Init() = 0;

  virtual bool Filter(const ObjectFilterOptions &obj_filter_options,
                      std::vector<std::shared_ptr<Object>> *objects) = 0;

  virtual std::string name() const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(BaseObjectFilter);
};
```
所以DummyObjectFilter需要实现 init/filter/name等方法.
而重写的方法在
----apollo/modules/perception/obstacle/lidar/dummy/dummy_algorithms.cc中

```
bool DummyObjectFilter::Filter(const ObjectFilterOptions &obj_filter_options,
                               std::vector<std::shared_ptr<Object>> *objects) {
  return result_object_filter_;
}
```


####  RegisterFactoryLidar64ProcessSubnode()的过程

 RegisterFactoryLidar64ProcessSubnode();是new了ObjectFactoryLidar64ProcessSubnode类
 在注册时生成对象如下:
 
 ----apollo/modules/perception/obstacle/onboard/lidar_process_subnode.h中
 REGISTER_SUBNODE(Lidar64ProcessSubnode);相当于 
 实例化了 perception Lidar64ProcessSubnode;
 ----apollo/modules/perception/obstacle/onboard/lidar_process_subnode.h中
 class Lidar64ProcessSubnode : public LidarProcessSubnode (){};
 
 
 而对于LidarProcessSubnode的结构图如下:
 ![LidarProcessSubnode](https://file.tink.im/selif/z6bvgkpu.png)
***
