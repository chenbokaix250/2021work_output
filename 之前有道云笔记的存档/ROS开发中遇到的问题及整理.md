>2018-4-17 完成雷达在ros上PCL算法工程的搭建

ros用节点区分

cmakelists完成projects和name的构建

peojects是catkin_create_pkg构建的 

name是add_execuble得到的

利用rosrun运行节点

catkin_make编译

!!!!一定要source devel/setup.bas

利用rqt_graph查看节点加载情况


![image](http://note.youdao.com/noteshare?id=93851b3f68a6f0b9436974d83f9721fa)

利用rostopic echo Node查看节点的打印情况




雷达链接时,先查看enp0s25的加载情况

利用ping 192.168.1.201 查看雷达设置 将conf中的mode更改为strongest

run ROS的velodyne_points节点 完成driver个节点的运行

利用 rosrun rviz rviz完成rviz的加载 


ros变成中的一些记录:

`ros::init(argc,argv,"Node")  //Node 为需要初始化的节点`

`ros::NodeHandle n //建立处理对象`

订阅者 subscriber
 
 `sub = n.subscribe("Node",time,callback)    //节点 周期 回调函数`
发布者 advertise

 `pub = n.advertise<type>('Name',time)  //类型 节点名 周期`
 
从velodyne_points上读到的msg类型为 const sensor_msgs::PointCloud2 

回调函数的写法:

`void chatterCallback(const sensor_msgs::PointCloud2ConstPtr& msg)`

ROS与PCL之间转换的函数

sensor_msgs::PointCloud2与pcl::PointCloud之间的转换

std_msgs:Header 对应 pcl::Header类型 包括消息被发送的时间和序列号以及框名

pcl_conversions命名空间提供的函数:

    void fromPCL(const <PCL Type> &, <ROS Message type> &);
    void moveFromPCL(<PCL Type> &, <ROS Message type> &);
    void toPCL(const <ROS Message type> &, <PCL Type> &);
    void moveToPCL(<ROS Message type> &, <PCL Type> &); 
    
    这里,PCL类型必须被替换成先前制定的PCL类型和ROS里面的相应类型  常用的sensor_msgs::PointCloud2类型
    
    ```
    void toROSMsg(const pcl::PointCloud<T> &, sensor_msgs::PointCloud2 &);
    void fromROSMsg(const sensor_msgs::PointCloud2 &, pcl::PointCloud<T>&);
    void moveFromROSMsg(sensor_msgs::PointCloud2 &, pcl::PointCloud<T> &);
    
    ```
    
    move版本为浅拷贝,使源数据作废 而正常版本执行完全拷贝.
    
    


PCL分割为几个模块的库:

Filters(滤波器)

Features(特征)

Keypoints(关键点)

Registration(注册)

KdTree:k-dimension tree(k维的树)

OcTree(八叉树)

Segmetation(分割)

Sample Consensus(采样一致)

Surface(表面)

Range Image(范围图)

I/O(输入输出)

Visualization(可视化)

Common(基础)

Search(搜索)



PCL中的可视化

pcl::visualization::CloudViewer viewer(NAME);

包含#include <pcl/visualization/pcl_visualizer.h>

创建PointXYZ泛型的PointCloud类型的Ptr 利用fromROSMsg接收点云数据

处理后利用viewer.showCloud()进行显示


 
 


###

>2018-4-21
卡在pcl_visualizer如何动态加载的问题上