>#include <memory> C++标准头文件,用于定义C++标准中的智能指针,内存分配器与垃圾回收有关的函数

>#include <mutex>
用于多线程编程,防止两条线程同时对同一公共资源进行读写的机制

>#include <utility>
头文件定义重载的关系运算符,简化关系运算符的写入,定义了pair类型,该类型是一种模板类型,可以存储一对值.

>std::ifstream 从已有的文件读取内容



>ConfigManager ConfigManager(){};
完成work_root的参数传递

>ConfigManager::Init(){};
锁定线程,执行InitInternal(){};

>ConfigManager::InitInternal(){};
如果初始化标志位为1,返回true


`ModelConfigMapIterator`由`typedef ModelConfigMap::iterator ModelConfigMapIterator;`定义
而`ModelConfigMap`是由`typedef std::unordered_map<std::string, ModelConfig*> ModelConfigMap;`定义

>ConfigManager::InitInternal(){};
对`model_config_map_`做清除
通过`GetAbsolutePath`函数获取prefix/relative_path (GetAbsolutePath原型在file.cc)
`MultiModelConfigProto`来自于>apollo/modules/perception/lib/config_manager/proto/config_schema.proto
```
message MultiModelConfigProto {
    repeated ModelConfigProto model_configs = 1;
}

message ModelConfigFileListProto {
    repeated string model_config_path = 1;
}
```

>ConfigManager::Reset() {};
重置初始化状态

>ModelConfig::Reset(const ModelConfigProto& proto) {};
对proto中的值进行重置

***

## Google Protocol Buffer
Google Protocol Buffer( 简称 Protobuf) 是 Google 公司内部的混合语言数据标准.
它是一种轻便高效的结构化数据存储格式，可以用于结构化数据串行化，或者说序列化。方便文件的存储与网络传输.

1. 写一个proto的文件,定义你需要的数据结构
2. 使用想要的语言的proto文件编辑器把写的proto文件编译为目标语言的相关类
3. 把生成的类包含在程序中,即可使用它


* message 是消息定义的关键字
* required 表示这个字段必须的，必须在序列化的时候被赋值。
* optional 代表这个字段是可选的，可以为0个或1个但不能大于1个。
* ==repeated 则代表此字段可以被重复任意多次包括0次。==
* int32和string 字段的类型。后面是我们定义的字段名。


编译时,利用 `protoc --cpp_out= $DIR  xxx.proto`进行编译
编译后得到`xxx.pb.cc`和 `xxx.pb.h`两个文件
在程序中引用`xxx.pb.h`完成对于结构的引用

例子中利用 write和read去引用访问
需要先实例化对象 利用对象进行操作

>todo