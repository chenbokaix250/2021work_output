init中传递 
* CameraObjectData给cam_obj_data_
* CameraSharedData给cam_shared_data_

执行标定初始化
执行modules初始化:完成了以下节点的启动:
* YoloCameraDetector
* GeometryCameraConverter
* CascadedCameraTracker
* FlatCameraTransformer
* ObjectCameraFilter


执行回调函数AddImageFrontCallback与AddChassisCallback

ImgCallback的内容:
利用msg接收近景摄像头最近的目标
利用timestamp接收事件戳
创建img的cv对象 将msg的消息类型转化为cv::Mat类型

创建objects与mask

利用以下参数接受处理结果
* detector_
* converter_
* tracker_
* transformer_
* filter_


* detector中Multitask的函数入口在apollo/modules/perception/obstacle/camera/detector/yolo_camera_detector/yolo_camera_detector.cc中
* converter_中Convert的函数入口在apollo/modules/perception/obstacle/camera/converter/geometry_camera_converter.cc
* tracker_中Associate的函数入口在apollo/modules/perception/obstacle/camera/tracker/cascaded_camera_tracker.cc
* transformer_中Transform的函数入口在apollo/modules/perception/obstacle/camera/transformer/flat_camera_transformer.cc
* filter_中Filter的函数入口在apollo/modules/perception/obstacle/camera/filter/object_camera_filter.cc


创建out_objs利用VisualObjToSensorObj/PublishPerceptionPb和PublishDataAndEvent发出

