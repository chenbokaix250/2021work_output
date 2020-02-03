>modules/common/macro.h
宏定义 DISALLOW_COPY_AND_ASSIGN

```
#define DISALLOW_COPY_AND_ASSIGN(classname) \
 private:                                   \
  classname(const classname &);             \
  classname &operator=(const classname &);
```
用于在C++中禁止class的拷贝构造函数和赋值构造函数


宏定义 DISALLOW_IMPLICIT_CONSTRUCTORS
```
#define DISALLOW_IMPLICIT_CONSTRUCTORS(classname) \
 private:                                         \
  classname();                                    \
  DISALLOW_COPY_AND_ASSIGN(classname);
```
用于禁止class的无参数构造函数

宏定义 DECLARE_SINGLETON

```
#define DECLARE_SINGLETON(classname)        \
 public:                                    \
  static classname *instance() {            \
    static classname instance;              \
    return &instance;                       \
  }                                         \
  DISALLOW_IMPLICIT_CONSTRUCTORS(classname) \
```
单例类定义，instance() 返回指向同一个class对象的指针。禁止拷贝/赋值运算符。

---
>modules/common/log.h

apollo内部使用谷歌的glog作为日志库。 
有5个日志级别，分别是DEBUG，INFO，WARNING，ERROR，FATAL
```
#define ADEBUG VLOG(4) << "[DEBUG] "
#define AINFO VLOG(3) << "[INFO] "
#define AWARN LOG(WARNING)
#define AERROR LOG(ERROR)
#define AFATAL LOG(FATAL)
```

---
>modules/common/time/time.h
apollo内部使用c++ 11的chrono库作为时间管理工具.默认精度纳秒(1e-9)

```
std::chrono::duration//表示时间间隔
std::chrono::time_point//表示时间中的一个点
```
time的全局函数

* int64_t AsInt64(const Duration &duration) //将纳秒ns转换为以PrecisionDuration为精度单位计的int64整数。
* int64_t AsInt64(const Timestamp &timestamp)  //将Timestamp(时间点)转换为64位整数表示。
* double ToSecond(const Duration &duration)  //将纳秒ns转换为秒s。
* inline double ToSecond(const Timestamp &timestamp) //将以纳秒表示的时间点ns转换为秒s
* Timestamp FromInt64(int64_t timestamp_value) //将以PrecisionDuration为精度计的int64整数转换为Timestamp(时间点)。
* Timestamp From(double timestamp_value)  //将秒s转换为时间点Timestamp。即FromInt64的特化版本：先将时间转换为ns计的64位整数nanos_value，再转换为Timestamp。

clock类中clock提供的static公有函数:
* static Timestamp Now()  //返回当前时间的最新值
* static void UseSystemClock(bool is_system_clock)//设置是否使用模拟时间
* static bool IsSystemClock() //返回是否使用系统时间
* static void SetNow(const Duration &duration) //当Clock使用mock时间时，将系统时间设定为给定值。否则抛出运行时错误。（只有模拟时间才可调整值，系统时间不可调整）


---
>modules/common/util/util.h
* MaxElement //返回最大
* MinElement //返回最小
* DistanceXY //返回距离
* uniform_slice //返回分段节点

---
>modules/common/util/string_util.h
* EndWith //返回预期正确的文件后缀 
* StartWith //返回预期正确的文件前缀
* 分解文件和print的方法
* Base64Decode 

---
>modules/common/util/file.h

template <typename MessageType> 模板类函数
* SetProtoToASCIIFile //存储message到file_name中
* GetProtoFromASCIIFile //从file_name中获取message,并给到*input上
* SetProtoToBinaryFile //以二进制形式储存message到file上
* GetProtoFromBinaryFile//解析二进制filename文件的内容，并存储到message中
* GetProtoFromFile  //从filename中获取内容
* GetContent //获取完整路径
* TranslatePath //链接前缀来获取绝对路径
* GetAbsolutePath//获取绝对路径
* PathExists //返回路径存在的bool值
* DirectoryExists //返回文件夹存在的bool值
* CopyFile //复制文件
* CopyDir  //复制文件夹
* Copy    //Both
* EnsureDirectory //确认路径存在的bool值
* RemoveAllFiles //删除文件夹中的文件
* ListSubDirectories //将文件目录splite
* GetFileName//获取文件名
* GetFileNamesInFolderById //获取文件ID

---
>modules/common/util/string_tokenizer.h
* Split 
* Next

---
>models/common/util/factory.h
创建对象的工厂模式。所有需要创建的对象使用ProductCreator函数指针创建。
默认使用unordered_map管理元素

* Register //注册某class的信息到unordered_map中，但是没有创建该class的实例对象。
* Unregister //删除已经注册的信息。
* Empty  // 不理解 与清空指针有关
* CreateObject  //创建某class的实例对象。

参数
```
template <typename IdentifierType, class AbstractProduct,
          class ProductCreator = AbstractProduct *(*)(),
          class MapContainer = std::map<IdentifierType, ProductCreator>>
```

1. 唯一标识符
2. 具有相同借口的纯虚基类
3. 函数指针,形参是空。返回值是指针，指向抽象class。
4. 按照IdentifierType存储需要创建的对象的方法。创建方法是ProductCreator


==实例化类的步骤:==

1. factory.Register("xxx_class") //注册信息
2. auto xxx_ptr = factory.CreateObject("xxx_class") //创建实例对象
3. xxx_ptr->Name() --> //得到 xxx

---

>modules/common/status/status.h
通用类,用于表示API调用的返回状态.OK或者error message/error code

成员函数:
1. ok 
2. code
3. string &error_message()
4. Save(StatusPb *status_pb)
5. string ToString()

---

>modules/common/adapters/adapter_gflags.h
用gflags的宏解析命令行参数.
声明:DECLARE_xxx(变量名)
定义:DEFINE_xxxx(变量名,默认值,help-string)

adapter_gflags.cc定义了在ROS环境下的多个topic的发布地址路径

---

>modules/common/adapters/adapter.h
Adapter是来自传感器的底层数据和Apollo各个模块交互的统一接口.
c++ 适配器模式
数据成员:
* topic_name_
* message_num
* std::list<DataPtr> data_queue_
* std::vector<Callback> receive_callbacks_
* mutable std::mutex mutex_
* bool enable_dump_
* std::string dump_path_
* uint32_t seq_num_ 
*  std::unique_ptr<D> latest_published_data_
*  double last_receive_time

构造函数的方法:(初始化了三个变量)
Adapter(const std::string& adapter_name, const std::string& topic_name,
          size_t message_num, const std::string& dump_dir = "/tmp")
          
方法:
* Empty
* OnReceive
* GetLatestObserved
* begin  end
* AddCallback
* void SetCallback(Callback callback) 设置消息到达时的回调函数。

### TODO
---

>modules/common/adapters/adapter_manager.h

AdapterManager类用于管理多个适配器,单例模式
所有的message/IO适配器均需要通过REGISTER_ADAPTER(name)在这里注册。所有的数据交互也通过AdapterManager来进行统一的管理。

完成所有适配器的注册->机制见macro.h

---
>modules/common/vehicle_state/vehicle_state.h
VehicleState类是标识车辆状态信息的class

成员变量:
* x y z //坐标
* kappa //
* roll  //侧倾角度
* pitch //俯仰角
* yaw   //偏航角度
* heading //车头转向转向
* linear_velocity //线速度 
* angular_velocity //角速度 
* linear_acceleration //线性加速度
* gear //齿轮状态
* set_linear_velocity //设置线速度
* EstimateFuturePosition //预估位置
* ComputeCOMPosition //com_pos_3d的更新(质心位置)
* vehicle_state  //车辆状态

---
>modules/common/monitor_log/monitor_log_buffer.h
存储log消息日志

REG_MSG_TYPE
AddMonitorMsgItem//msgitem = level+msg.
void printlog()
---
>modules/common/monitor_log/monitor_logger.h
* MonitorLogger
* Publish

---

>modules/common/math

* aabox2d 2D区域
* aaboxkdtree2d  kd树组成的2D区域集
* angle 角度弧度转换
* box2d 2d框
* cartesian_frenet_conversion 笛卡尔坐标系转frenet标架
* euler_angles_zxy 欧拉角
* factorial 阶乘
* hermite spline 曲线分析相关?
* integral 积分
* 