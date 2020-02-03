
### usb_cam的运行状态
perception.sh
```
run perception "$@"
```
进入
perception.cc


Status Perception::Init


FLAGS_perception_adapter_config_filename->modules/perception/conf/adapter.conf

RegistAllOnboardClass()->注册 shareddata && 注册 subnode

eg:RegisterFactoryLidarObjectData()  RegisterFactoryCameraObjectData
eg:RegisterFactoryLidarProcessSubnode)() RegisterFactoryCameraProcessSubnode()


object_shared_data.h中注册
```
REGISTER_SHAREDDATA(LidarObjectData);
REGISTER_SHAREDDATA(RadarObjectData);
REGISTER_SHAREDDATA(CameraObjectData);
REGISTER_SHAREDDATA(CIPVObjectData);
```

shared_data.h中调用
```
#define REGISTER_SHAREDDATA(name) REGISTER_CLASS(SharedData, name)

//register.h中

得到RegisterFactory##name 所以得到了:


RegisterFactoryLidarObjectData();

```
```

REGISTER_GROUNDDETECTOR(DummyGroundDetector);


#define REGISTER_GROUNDDETECTOR(name) REGISTER_CLASS(BaseGroundDetector, name)

//name->detect(what) 
//regitster.h 中 #define REGISTER_CLASS中inline函数的调用 RegisterFactory##name
//得到了

        RegisterFactoryDummyGroundDetector()
        当instantbyname时,就实例化了name的对象

```
```
//BaseGroundDetector用的是detect(what)

REGISTER_REGISTERER(BaseGroundDetector);

//register.h中 #define REGISTER_REGISTERER(base_class)  class base_class##Registerer{}...

```

config_manager->config_manager.cc 配置初始化
利用protobuf完成config的管理



Perception::Start()/Stop()

dag_streaming_.Start()

>dag_streaming.cc
```
void DAGStreaming::Schedule(){
    
  monitor_->Start();
  // start all subnodes.
  for (auto& pair : subnode_map_) {
    pair.second->Start();
  }

  AINFO << "DAGStreaming start to schedule...";

  for (auto& pair : subnode_map_) {
    pair.second->Join();
  }

  monitor_->Join();
  AINFO << "DAGStreaming schedule exit.";
}
```

>dag_streaming.h

std::unique_ptr<DAGStreamingMonitor> monitor_;
static std::map<std::string, SubnodeID> subnode_name_map_;
利用map 按照ID启动节点 >dag_streaming.config

>apollo/modules/perception/conf/dag_streaming.config
包括:
* LidarProcessSubnode
* RadarProcessSubnode
* FusionSubnode
* TLPreprocessorSubnode

理解dag_streaming.config 描述的是 数据流向

subnode包括:激光雷达 毫米波雷达 红绿灯 融合

edge描述的是节点之间的链接关系:

*  64-Lidar LidarProcessSubnode -> FusionSubnode
*  Radar RadarProcessSubnode -> FusionSubnode
*  TLPreprocessorSubnode -> TLProcSubnode

>tl_preprocessor_subnode.cc

TLPreprocessorSubnode的`方法
* InitInternal 完成初始化和校验以及调试的错误上报
* InitSharedData preprocessing_data_ 是TLPreprocessingData的实例对象,在tl_preprocessor_subnode.h完成实例化

preprocessor_为TLPreprocessor的实例对象,在tl_preprocessor_subnode.h完成实例化

* InitPreprocessor,完成预处理 如果preprocessor_未完成初始化,则上报
* InitHdmap,初始化HDmap模块
* AddDataAndPublishEvent,传递key&data给preprocessing_data_ 
利用event的Publish发出

* SubLongFocusCamera
* SubShortFocusCamera  切换Adapter的通道

* SubCameraImage sub_camera_image_start_ts获取采集时间 image接受cv的图像 保存image中
