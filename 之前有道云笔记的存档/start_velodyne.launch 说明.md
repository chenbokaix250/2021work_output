```

<launch>
    <arg name="velodyne64_calibration_online" default="true" />   //在线标定
    <!--If 'velodyne64_calibration_online' is true, 'velodyne64_calibration_file' will not use  -->
    <arg name="velodyne64_calibration_file" default="$(find velodyne_pointcloud)/params/64E_S3_calibration_example.yaml"/>
    <arg name="extrinsics_velodyne64" default="$(find velodyne_pointcloud)/params/velodyne64_novatel_extrinsics_example.yaml"/>
    <arg name="velodyne64_frame_id" default="velodyne64"/> //frame_ID设置为 velodyne64
    <arg name="organized" default="false"/>
    <arg name="min_range" default="0.9" />//最小距离 0.9m
    <arg name="max_range_64" default="70.0" />//最大距离 70m
    <arg name="rpm" default="600"/>默认转速 600
    <!-- 64E_S3D_STRONGEST | 64E_S3D_LATEST | 64E_S3D_DUAL -->
    <arg name="model" default="64E_S3D_STRONGEST" />//默认模式 STRONGEST模式
    <!-- beijing    UTC+8:00 -->//北京时间
    <!-- california UTC-8:00 -->//加州时间
    <arg name="time_zone" default="-8" />//时区
    <!-- 100ms -->
    <arg name="tf_query_timeout" default="0.1"/>//tf查询超时 0.1s

  <include file="$(find velodyne_pointcloud)/launch/nodelet_manager.launch">
  //位置  apollo/modules/drivers/velodyne/velodyne_pointcloud/launch/nodelet_manager.launch  -->velodyne_nodelet_manager  
  //其中(find velodyne_pointcloud)duiiyng的是apollo/modules/drivers/velodyne/velodyne_pointcloud
  </include>
    <!--  HDL64E -->
    <!--  driver nodelets -->
  <include file="$(find velodyne_driver)/launch/driver_nodelet.launch">
    <arg name="node_name" value="sensor_velodyne64_driver"/>//节点名称
    <arg name="model" value="$(arg model)"/>//工作模式
    <arg name="rpm" value="$(arg rpm)"/>//工作转速
    <arg name="frame_id" value="$(arg velodyne64_frame_id)"/>//frame_id
    <arg name="topic" value="/apollo/sensor/velodyne64/VelodyneScanUnified"/>    //topic
  </include>
  
  <!-- start cloud nodelet using test calibration file -->//利用test标定文件
  <include file="$(find velodyne_pointcloud)/launch/convert_nodelet.launch">
    <arg name="node_name" value="sensor_velodyne64_convert"/>
    <arg name="model" value="$(arg model)"/>
    <arg name="calibration_online" value="$(arg velodyne64_calibration_online)" />
    <arg name="calibration" default="$(arg velodyne64_calibration_file)" />
    <arg name="organized" default="$(arg organized)"/>
    <arg name="min_range" default="$(arg min_range)" />
    <arg name="max_range" default="$(arg max_range_64)" />
    <arg name="time_zone" default="$(arg time_zone)" />
    <arg name="topic_pointcloud" default="/apollo/sensor/velodyne64/PointCloud2"/>
    <arg name="topic_packets" default="/apollo/sensor/velodyne64/VelodyneScanUnified"/>
  </include>
  
   <!-- start 64 compensator nodelet -->//补偿器
  <include file="$(find velodyne_pointcloud)/launch/compensator_nodelet.launch"> //打开补偿其节点
    <arg name="node_name" value="sensor_velodyne64_compensator"/>
    <arg name="child_frame_id" value="$(arg velodyne64_frame_id)"/>
    <arg name="tf_query_timeout" value="$(arg tf_query_timeout)"/>
    <arg name="topic_pointcloud" value="/apollo/sensor/velodyne64/PointCloud2"/>
    <arg name="topic_compensated_pointcloud" value="/apollo/sensor/velodyne64/compensator/PointCloud2"/>
  </include>

  <node pkg="velodyne_pointcloud" type="extrinsics_broadcaster.py"
    args="$(arg extrinsics_velodyne64)" name="static_transform_velodyne64" />

</launch>
```


start_velodyne.launch 打开了:
* nodelet_manager.launch
* driver_nodelet.launch
* convert_nodelet.launch
* compensator_nodelet.launch

pkg 节点包  type 节点类型  name 节点基名称  args 传递参数到节点  machine 指定机器上启动节点

pkg与type定义了ros应该运行哪个程序来启动这个节点


##### nodelet_manager.launch
```
<launch>
  <node pkg="nodelet" type="nodelet" name="velodyne_nodelet_manager" output="screen"
        args="manager" />
</launch>
```
其中 nodelet节点运行的是:

> velodyne_nodelet_manager 定义来源于 apollo/modules/monitor/conf/monitor_conf.pb.txt

```
modules {
  name: "velodyne"
  process_conf {
    process_cmd_keywords: "velodyne_nodelet_manager"
  }
}
```
这个作用?


##### driver_nodelet.launch
```
<launch>

  <!-- start load driver nodelet -->
  <arg name="model" default="64E_S3D_STRONGEST" />
  <arg name="ip" default=""/>
  <arg name="firing_data_port" default=""/>
  <arg name="rpm" default="600.0" />
  <arg name="frame_id" default="velodyne64" />
  <arg name="topic" default="/apollo/sensor/velodyne64/VelodyneScanUnified" />
  <arg name="node_name" default="driver_nodelet"/>

  <node pkg="nodelet" type="nodelet" name="$(arg node_name)"
        args="load velodyne_driver/DriverNodelet velodyne_nodelet_manager" output="screen" >
    <param name="model" value="$(arg model)"/>
    <param name="rpm" value="$(arg rpm)"/>
    <param name="frame_id" value="$(arg frame_id)"/>
    <param name="topic" value="$(arg topic)"/>    
    <param name="ip" value="$(arg ip)"/>
    <param name="firing_data_port" value="$(arg firing_data_port)"/>
  </node>    

</launch>

```
driver_nodelet 为节点名称 传入的参数有 model/rpm/frame_id/topic/ip/firing_data_port

driver_nodelet建立在  `apollo/modules/drivers/velodyne/velodyne_driver/src/driver/CMakeLists.txt`中完成

>其中 *add_library* 使用指定的源文件向工程中添加一个库。

建立的文件有:
  driver_nodelet.cpp
  driver.cpp 
  driver16.cpp
  # driver32.cpp
  driver64.cpp
链接时,引用了 velodyne_input

velodyne_input来自于`apollo/modules/drivers/velodyne/velodyne_driver/src/lib/CMakeLists.txt`
建立的文件有:
  velodyne_input 
  input.cpp
  socket_input.cpp
  # pcap_input.cpp



#### convert_nodelet.launch

```
<launch>
  <arg name="model" default="64E_S3D_STRONGEST" />
  <arg name="calibration_online" default="true" />
  <!--If 'calibration_online' is true, 'calibration' will not use -->
  <arg name="calibration" default="" />
  <arg name="min_range" default="0.9" />
  <arg name="max_range" default="70.0" />
  <arg name="organized" default="false"/>
  <arg name="topic_pointcloud" default="/apollo/sensor/velodyne64/PointCloud2"/>
  <arg name="topic_packets" default="/apollo/sensor/velodyne64/VelodyneScanUnified"/>
  <arg name="node_name" default="convert_nodelet"/>

  <node pkg="nodelet" type="nodelet" name="$(arg node_name)"
        args="load velodyne_pointcloud/ConvertNodelet velodyne_nodelet_manager" output="screen">
    <param name="calibration_online" value="$(arg calibration_online)"/>
    <param name="calibration" value="$(arg calibration)"/>
    <param name="min_range" value="$(arg min_range)"/>
    <param name="max_range" value="$(arg max_range)"/>
    <param name="model" value="$(arg model)"/>
    <param name="organized" value="$(arg organized)"/>
    <param name="topic_pointcloud" value="$(arg topic_pointcloud)"/>
    <param name="topic_packets" value="$(arg topic_packets)"/>
  </node>
</launch>

```

convert_nodelet建立在 `apollo/modules/drivers/velodyne/velodyne_pointcloud/CMakeLists.txt`
建立的文件有:
`convert.cpp`

#### compensator_nodelet.launch

```
<launch>
  <arg name="topic_pointcloud" default="/apollo/sensor/velodyne64/PointCloud2"/>
  <arg name="topic_compensated_pointcloud" default="/apollo/sensor/velodyne64/compensator/PointCloud2"/>
  <arg name="node_name" default="compensator_nodelet"/>
  <arg name="child_frame_id" default="velodyne64"/>
  <arg name="tf_query_timeout" default="0.1"/>
  <node pkg="nodelet" type="nodelet" name="$(arg node_name)"
        args="load velodyne_pointcloud/CompensatorNodelet velodyne_nodelet_manager" output="screen">
    <param name="topic_pointcloud" value="$(arg topic_pointcloud)"/>
    <param name="topic_compensated_pointcloud" value="$(arg topic_compensated_pointcloud)"/>
    <param name="child_frame_id" value="$(arg child_frame_id)"/>
    <param name="tf_query_timeout" value="$(arg tf_query_timeout)"/>
  </node>
</launch>

```

compensator_nodelet.launch建立在`apollo/modules/drivers/velodyne/velodyne_pointcloud/CMakeLists.txt`
建立的文件有:
    compensator_nodelet.cpp
    compensator.cpp
    

