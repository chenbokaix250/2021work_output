Ubuntu16.04

ROS-kinetic

opencv3.3.1

video-stream-opencv

一个USB摄像头


video-stream-opencv是USB摄像头驱动，关于它的介绍，请看github:https://github.com/ros-drivers/video_stream_opencv

安装video-stream-opencv:
```
cd ~/catkin_ws/src/
git clone https://github.com/ros-drivers/video_stream_opencv.git
cd ~/catkin_ws/
catkin_make
```

在终端输入:`rosrun video_stream_opencv test_video_resource.py`

#### opencv格式与ros格式之间的相互转换
ROS image消息类型到opencv类型的转换:
`cv_image = bridge.imgmsg_to_cv2(image_message, desired_encoding="passthrough")`
Opencv类型到ROS Image类型的转换:
`image_message = cv2_to_imgmsg(cv_image, encoding="passthrough")`

#### 目标

使用Opencv获取图片，通过ROS的publisher（web_cam）发布图片到image_topic主题下，然后有一个新的listener（image-converter）订阅这个topic,并在图片中的制定位置画出一个实心圆。

![image](https://img-blog.csdn.net/20180103141508581?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvR3B3bmVy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

#### 发布者
a.py
```
#! /usr/bin/env python2
# -*- coding: utf-8 -*-
"""

Copyright (c) 2015 PAL Robotics SL.
Released under the BSD License.

Created on 7/14/15

@author: Sammy Pfeiffer

test_video_resource.py contains
a testing code to see if opencv can open a video stream
useful to debug if video_stream does not work
"""

import sys
import signal
import cv2
import rospy
from cv_bridge import CvBridge, CvBridgeError
from sensor_msgs.msg import Image


def quit(signum, frame):
    print ''
    print 'stop fusion'
    sys.exit()


if __name__ == '__main__':
    signal.signal(signal.SIGINT, quit)
    signal.signal(signal.SIGTERM, quit)
    # 参数的长度
    if len(sys.argv) < 2:
        print "You must give an argument to open a video stream."
        print "  It can be a number as video device, e.g.: 0 would be /dev/video0"
        print "  It can be a url of a stream,        e.g.: rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov"
        print "  It can be a video file,             e.g.: myvideo.mkv"
        exit(0)

    resource = sys.argv[1]
    # If we are given just a number, interpret it as a video device
    if len(resource) < 3:
        resource_name = "/dev/video" + resource
        resource = int(resource)
    else:
        resource_name = resource
    print "Trying to open resource: " + resource_name
    cap = cv2.VideoCapture(resource)
    if not cap.isOpened():
        print "Error opening resource: " + str(resource)
        print "Maybe opencv VideoCapture can't open it"
        exit(0)
    bridge = CvBridge()
    publisher = rospy.Publisher('image_topic', Image, queue_size=10)
    rospy.init_node('web_cam')
    print "Correctly opened resource, starting to show feed."
    rval, frame = cap.read()

    while rval:
        # 将opencv格式的图片转换为ROS可接受的msg
        image_message = bridge.cv2_to_imgmsg(frame, encoding="bgr8")
        try:
            publisher.publish(image_message)
        except CvBridgeError as e:
            print(e)
        rval, frame = cap.read()
```

#### 订阅者

订阅者的作用就是上边说的从image-topic中订阅消息，然后将其转换为opencv格式的图片，然后在图片中画出一个实心圆

```
#!/usr/bin/env python
import roslib

roslib.load_manifest('video_stream_opencv')
import rospy
import cv2
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError


class image_converter:

    def __init__(self):
        self.bridge = CvBridge()
        self.image_sub = rospy.Subscriber("image_topic", Image, self.callback)

    def callback(self, data):
        try:
            cv_image = self.bridge.imgmsg_to_cv2(data, "bgr8")
        except CvBridgeError as e:
            print(e)

        (rows, cols, channels) = cv_image.shape
        if cols > 60 and rows > 60:
            cv2.circle(cv_image, (150, 150), 20, (30, 144, 255), -1)
        cv2.imshow("Image window", cv_image)
        cv2.waitKey(3)


if __name__ == '__main__':
    ic = image_converter()
    rospy.init_node('image_converter')
    try:
        rospy.spin()
    except KeyboardInterrupt:
        print("Shutting down")
    cv2.destroyAllWindows()
```

#### 运行

启动终端 roscoe
启动pubisher rosrun video_stream_opencv test_video_resource.py 0
启动Subscriber rosrun video_stream_opencv web_cam_listenert.py

![image](https://img-blog.csdn.net/20180103150245311?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvR3B3bmVy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)

启动一个新的调用rqt_graph rqt_graoh 
![image](https://img-blog.csdn.net/20180103150440061?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQvR3B3bmVy/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast)


#### 遇到的问题:

1.cmake中的py节点编译中出现的问题

```
cmake_minimum_required(VERSION 2.8.3)
project(video_stream_opencv)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  cv_bridge
  image_transport
  camera_info_manager
  sensor_msgs
)


find_package(OpenCV)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(video_stream src/video_stream.cpp)
target_link_libraries(video_stream ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})

install(TARGETS video_stream
    RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(PROGRAMS
  scripts/a.py

  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(PROGRAMS
  scripts/b.py

  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
```
> install(PROGRAMS
    scripts/xxxx.py
    DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
    
 
   
    

chmod +x a.py
chmod +x b.py