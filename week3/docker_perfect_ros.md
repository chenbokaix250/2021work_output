# mac一个相对完美的ros解决方案

下载ROS的Docker镜像，由于在使用ROS时会需要gazebo, rviz, rqt等工具来仿真或者查看当前状态等，所以不能直接使用ros官方提供的Docker镜像，那个镜像无法打开GUI程序。所以这里有两个选择：

1. 解决Docker打开GUI程序的显示问题。网上有各种教学说通过配置各种软件来实现这个需求，我也不在此细说（没有试过，大概率会碰到各种坑）。

2. https://hub.docker.com/r/yz16/my_ros 利用这个dockerhub 



开始使用这个Docker镜像:

1.生成Container

```
docker run --name ros_env \
--mount type=bind,source=/Users/godz/ros_workspace,target=/root/ros_workspaces \
-itd -p 6080:80 yz16/my_ros
```

2.浏览器打开 [http://127.0.0.1:6080](https://link.zhihu.com/?target=http%3A//127.0.0.1%3A6080/vnc.html%3Fautoconnect%3D1%26autoscale%3D0%26quality%3D3) 可以获取

![](https://pic4.zhimg.com/v2-626ca25920735eb8c07d95d8fa8ded2f_r.jpg)

这里说明一点：虽然Docker说是可以看做精简版的虚拟机，但是并不能真的当虚拟机使用，由于Docker的层的机制，导致每次往Container里增加东西或者删除文件，只会不断增加Docker image的层数（文件越来越大）。所以正确的使用方法是把Container当做一个处理文件的程序（类比Word软件和*.docx文件），将我们主机的文件系统挂载到Container当中。



#### 不用了直接

```
docker stop ros_env
```

#### 需要时直接运行

```
docker start ros_env
```

其实在任何平台上都是可行的，只要能跑Docker，易于部署。关于图像质量不高，这个可以通过配置noVNC的参数来提高，暂时还没折腾。由于在调试真机的时候，基本都是机器人上一个主机开着roscore，然后一堆传感器接到机器人上，自己的电脑都是通过连到机器人上面的roscore来调试的，所以不会存在传感器和Docker之间数据传输配置什么的问题。



可以通过这个链接查看docker命令的使用和理解:

https://yeasy.gitbooks.io/docker_practice/appendix/command/