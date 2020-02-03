## 1.概述

#### PCL中的基本接口程序如下：

1. 创建处理对象：（过滤/特征估计/分割）
2. 使用*setInputCloud*通过输入点云数据，处理模块
3. 设置算法相关参数
4. 调用计算（或过滤/分割等）得到输出
***
#### PCL模块化设计

1. filter
2. features
3. I/O
4. segmentation
5. surface
6. register
7. keypoints
8. range
***

## 2.安装

#### Ubuntu 安装

```
sudo repository
sudo apt-get update
sudo apt-get install libpcl-all

```

***
#### 工程设置


在*source*文件集下，创建*pcd_write.cpp*的单独的*cpp*文件,然后在该文件家中新建一个名为CMakeLists.txt的文件.

CMakeLists文件的编写
```
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)//要求最低版本
project(MY_GRAND_PROJECT)//工程命名
find_package(PCL 1.3 REQUIRED COMPONENT common io)//模块化需求
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})
add_executable(pcd_write pcd_write.cpp)
target_link_libraries(pcd_write ${PCL_COMMON_LIBRARIES}${PCL_IO_LIBRARIES})
```
编译过程
```
    mkdir biuld && cd build
    cmake ..
    make
    ./pcd_write
```


## PCL基础
#### 可用的PointT类型
* PointXYZ 成员变量 float x,y,z
   
利用points[i] data[0]或points[i].x来访问点的x坐标值

* PointXYZI 成员变量 float x,y,z,intensity

POINTXYZI结构体定义
```
union
{
    
    float data[4];
    struct
    {
        float x;
        float y;
        float z;
    };
    
};

union
{
    struct
    {
        float intensity;
    };
    float data_c[4];
};

```
#### 在模板中使用point类型

## 输入/输出(I/O)

OpenNI 框架
* 应用层
* 中间件接口层
* 硬件设备层

#### PCL中I/O模块及类介绍

classpcl::FileReader
类FileReader定义来PCD文件的读取接口,主要用作其他读取类的父类
> PCDReader PLYReader 均继承FileReader
class pcl::FileWriter
与FileReader对应

class pcl::Grabber
类Grabber为PCL对应的设备驱动接口的积累定义

pcl::PCDGrabber<PointT>继承pcl::PCDGrabberBase继承pcl::Grabber



boost::signals2::connectionregisterCallback(const boost::function<T>&callback)
>提供回调函数指针,当获取每帧图像或云数据时都会启动回调函数


```
int pcl::io::loadPCDFile(const std::string &file_name,pcl::PointCloud<PointT>&cloud)
```
打开任何类型的PCD点云文件,file_name为文件名,cloud存储读取的点云数据

``` 
int pcl::io::savePCDFile(const std::string & file_name,const sensor_msgs::PointCloud2&cloud,constEigen::Vector4f & origin = Eigen::Vector4f::Zero(),const Eigen::Quaternionf & orientation=Eigen::Quaternionf::Identity(),const bool binary_mode=false)
```
保存点云到PCD文件,file_name文件名,cloud需要保存的点云数据,origin为获点云的原点,orientation为获取点云的方向,binary_mode设置是否保存为二进制格式,默认为false.

### PCD文件
* VERSOIN 指定PCD文件版本
* FIELDS 指定一个点可以油的每个唯独和字段的名字
* SIZE 用字节数指定每个维度的大小
* TYPE 用一个字符指定每个字符的类型
* COUNT 指定每一个唯独包含的元素数目
* WIDTH 用点的数量表示点云数据集的宽度
* HEIGHT 用点的数目表示点云数据集的高度 为1时,表示无序点云
* VIEWPOINT 指定数据集中点云的获取视点
* POINTS 指定点云中点的总数
* DATA 指定存储点云数据的shujuleiixng


####Grabber中的关键函数
boost::bind相对复杂,可以注册下面几类回调函数:

```
void (const boost::shared_ptr<constpcl::PointCloud<pcl::PointXYZRGB>&)
void (const boost::shared_ptt<constpcl::PointCloud<pcl::PointXYZ>>&)
void (const boost::shared_ptr<openni_wrapper::DepthImage>&)

```

开始和停止数据流

registerCallback将返回一个boost::signals2::connection对象

```
boost::signals2::connection = interface(regsterCallback(f));
if(c.connected())
c.disconnect();

```

## kd-tree模块

class pcl::KdTree<PointT>

pcl::KdTree<PointT>是 KdTreeFLANN<PoinT> 与 pcl::KdTreeFLANN<PointT>的基类

---

## visualization模块

pcl_visualization依赖于pcl_common/pcl_range_image/pcl_kdtree/pcl_IO模块以及VTK外部开源可视化库

***

`class pcl::visualization::CloudViewer`

类CloudViewer实现创建点云可视化的窗口,以及相关的可视化功能
类CloudViewer关键成员函数:
```
CloudViewer(const std::string & window_name)
//窗口名 windows_name

void showCloud(const ColorACloud::ConstPtr &cloud,const std::string&cloudname="cloud")
//可视化点云窗口中显示点云,多个点云用键值cloudname来限定

void runOnVisualizationThread(VizCallable x,const std::string &key="callable")
//在窗口运行期间处理x回调函数,key为键值标识此回调函数,直到窗口关闭

void runOnVisualizationThreadOnce(VizCallable x)
//只调用一次回调函数

```

`class pcl::visualization::FloatImageUtils`

类FloatImageUtils针对二维浮点数组的可视化类

`class pcl::visualization::PCLVisualizer`

类PCLVisualizer为PCL可视化3D点云的主要类,其内部实现类添加各种3D对象以及交互实现等

类PCLVisualizer的关键函数说明:
```
PCLVisualizer(int &argc,char ** argv,const stdd::string &name=" ",PCLVisualizerInteractorStyle  * style=PCLVisualizerInteractorStyle::New(),const bool create_interactor=true)

//重构函数,其中name为创建窗口名,style为交互类实现,默认为PCLVisualizerInteractorStyle对象,create_interactor设置是否重建交互对象,默认是创建的.

void setFullScreen(bool mode)
//设置是否全屏显示

void setWindowBorders(bool mode)
//设置是否油窗口边沿

boost::signals2::connection registerKeyboardCallback(boost::function(void(constpcl::visualization::KeyboardEvent &)>cb)
//注册键盘事件回调函数

boost::signals2::connection registerMouseCallback(void(*callback)(const-pcl::visualization::MouseEvent&,void *),void *cookie=NULL)
//注册鼠标事件回调函数

void spin()
//调用内部渲染函数,重新渲染输出


void spinOnce(int time=1,bool force-redraw=false)
//调用内部渲染函数一次,重新渲染输出时间不大于time,单位ms,force_redraw设置是否强制重新绘制


void addCoordinateSystem(double scale=1.0,int viewport=0)
//在坐标原点(0,0,0)添加指示坐标系,viewport为需要添加的视口,默认在所有视口中添加,scale设置指示坐标周的放大系数

void addCoordinateSystm(double scale,float x,float y,float z,int viewport=0)
//在坐标(x,y,z)添加指示坐标轴,wiewport为需要添加的视口,默认在所有视口中都添加,scale设置指示坐标轴的放大系数

bool removeCoordinateSystem(int viewport = 0)
//删除前面添加的指示坐标系

bool removeAllPointClouds(int viewport=0)
//在viewport子还定的视口中删除所有点云

void setBackgroundColor(const double &r,const double &g,const double &b,int viewport=0)
//设置指定viewport视口的背景色



bool addPointCloud(const typename pcl::PointCloud<PointT>:ConstPtr&cloud,const std::string &id="cloud",int viewport = 0)
//在指定的iewport内添加显示点云cloud,id为点云的ID标志

bool updatePointCloud(const typename pcl::PointCloud<PointT>::ConstPtr &cloud,constPointCloudGeometryHandler<PointT>&geometry_handler,const std::string &id="cloud")
//刷新当前指定的id对应点云的数据以及显示,geometry_handler为提取点的处理对象


bool updatePoinitCloud(const typename pcl::PointCloud<PointT>::ConstPtr &cloud,constPointCloudHandler<PointT>&color_handler,const std::string &id="cloud")
//刷新当前指定的id对应点云的数据以及显示,color_handler为提取要色的处理对象


```
重要的方法

` class pcl::visualization::PointCloudColorHandler<PointT>`
> 类PointCloudColorHandler实现从点云获取RGB的处理过程的基类,其继承关系

