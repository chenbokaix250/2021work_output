### yolov3 的移植
[github工程地址](https://github.com/leggedrobotics/darknet_ros.git)

利用下命令安装
```
git clone --recursive https://github.com/leggedrobotics/darknet_ros.git`
cd ..
catkin_make -DCMAKE_BUILD_TYPE=Release
```

进入路径 `catkin_workspace/src/darknet_ros/darknet_ros/yolo_network_config`
下载weights和cfg文件中的内容


进入路径`catkin_workspace/src/darknet_ros/darknet_ros/config`
对于`ros.yaml`
```
subscribers:
  camera_reading:
    topic: /usb_cam/image
    queue_size: 1
```

`roslaunch usb_cam usb_cam-test.launch `
`roslaunch darknet_ros darknet_ros.launch`

datknet中publish的topic有:
```
/datknent_ros/bounding_boxes  
/darkent_ros/check_for_objects/cancel
/darkent_ros/check_for_objects/feedback
/darkent_ros/check_for_objects/goal
/darkent_ros/check_for_objects/result
/darkent_ros/check_for_objects/status
/darkent_ros/detection_image
/darkent_ros/found_object

```

found_object包含的数据结构 Int8 属于 std_msgs.msg
`from std_msgs.msg import Int8`

bounding_boxes包含的数据结构是BoundingBoxes 来自msg中的定义
msg's add: darkent_ros/darknet_ros_msgs/msg
BoundingBoxes.msg:
```
Header header //消息时间戳
Header image_header //图片消息时间戳
BoundingBox[] bounding_boxes //障碍信息
```
其中BoundingBoxp[]来自 BoundingBox.msg:
```
string Class //种类
float64 probability //置信度
int64 xmin //box信息
int64 ymin
int64 xmax
int64 ymax
```
---

### msg的创建与编写
重点在 接受 这种msg时,需要利用他的数据结构

需要创建msg类型
1. 创建msg文件夹 存档msg文件<复制msg到该文件夹>
2. 编辑msg文件
3. 修改package.xml文件 确保包含一下两个语句
```
  <build_depend>message_generation</build_depend>
  <run_depend>message_runtime</run_depend>
  <exec_depend>message_runtime</exec_depend>//版本不同 用run_depend exec_depend区分
```
4. 修改CMakeLists.tx文件 需要确保依赖关系运行
```
catkin_package(
...
CATKIN_DEPENDS message_runtime
...
)
```
5. 然后对add_message_files()代码块取消注释并填写信息
```
 add_message_files(
   FILES
   BoundingBoxes.msg
   BoundingBox.msg
 )
```

6. generate_messages()
```
 generate_messages(
   DEPENDENCIES
   std_msgs  # Or other packages containing msgs
 )
 ```
7. 查看msg定义是否成功

`rosmsg show [message type]`
`rosmsg show yolo_listener/BoundingBoxes 或者 BoundingBox`

8. 增加新的消息后 需要重新对package进行编译 catkin_make
9. 在代码中使用自定义的msg
* C++ 中需要include msg的头文件:
`#include <package_name/message_name.h>`
`#include <yolo_listener/BoundingBoxes>`
  命名空间的写法:
    `package_name::message_name::ConstPtr& input`
* python 中需要import的头文件写法:
    `from package_name.msg import message_name`
中断函数中利用 data.xxx 来接受message中的数据类型

---


### launch的记录与写法

* 使用
 `roslaunch package_name file.launch
* 编写
 roslaunch文件是使用XML语言来描述节点以及相关参数的设置和软件的启动的

标签说明
<launch> roslaunch根元素
<node> 启动节点
<param> 对参数服务器进行参数设置
<remap> 声明映射名
<machine> 声明要启动的机器
<rosparam> 使用rosparam文件启动设置ROS参数
<include> 包含其他的roslaunch文件
<env> 位启动节点制定一个环境变量
<test> 启动一个测试节点
<arg> 声明一个提要
<group> 共享一个名称空间或重新映射组封闭元素

##### 以下详细描述 node标签的用法

pkg=”mypackage”—–节点所在的包

type=”nodetype”—–节点的类型。必须有一个对应的可执行文件名称相同的。

name=”nodename”—–节点的名称。名称不能包含一个名称空间，需使用ns属性代替。

args=”arg1 arg2 arg3”(可选)—–将参数传递给节点。

machine=”machine-name”(可选)—–指定的机器上启动节点。

respawn=”true”(可选)—–如果节点自动退出则重新启动节点。

respawn_delay=”30” (可选, 默认为 0)—–如果重启为真，在尝试重启之前，档检测到节点故障后则等待延时30秒。

required=”true”(可选)—如果节点死亡，则杀死整个launch

ns=”foo”(可选)—–启动节点在foo命名空间

output = "screen" (可选)—–打印信息终端显示

例子 对于工程yolo_listener中
```
.
├── CMakeLists.txt
├── launch
│   └── yolo_listener.launch
├── msg
│   ├── BoundingBoxes.msg
│   └── BoundingBox.msg
├── package.xml
└── src
    ├── listener_box.py
    ├── listener_num.py
    └── listener_test.py

3 directories, 8 files
```
python中:
```
<node name="yololistenerNUM" pkg="yolo_listener" type="listener_num.py"  output="screen">
	</node>
```
如果是在c++中: 执行文件是 listener_num.cpp
```
<node name="yololistenerNUM" pkg="yolo_listener" type="listener_num"  output="screen">
	</node>
```
cpp可以省略 

