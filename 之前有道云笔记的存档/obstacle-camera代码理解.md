#### yolo_camera_detector.cc

* init完成model加载/work_root的确定/
* yolo_root的路径 apollo/modules/perception/model/yolo_camera_detector
* 获取yolo_root和yolo_config的绝对路径
>GetAbsolutePath方法 来自apollo/modules/common/util/file.cc

FLAGS_yolo_config_filename 对应 yolo_config_filename 来自
>modules/perception/obstacle/camera/detector/yolo_camera_detector/yolo_camera_detector.cc
`DEFINE_string(yolo_config_filename, "config.pt", "Yolo config filename.");`
config.pt来自apollo/modules/perception/model/yolo_camera_detector/config.pt
```
model_param {
  model_name: "yolo3d_1128"
  proto_file: "deploy.pt"
  weight_file: "deploy.md"
  offset_ratio: 0.28843
  confidence_threshold: 0.5
  min_2d_height: 17
  min_3d_height: 0.5
  model_type: Caffe
  cropped_ratio: 0.71157
  resized_width: 960
  aligned_pixel: 32
}
net_param {
  loc_blob: "loc_pred"
  obj_blob: "obj_pred"
  cls_blob: "cls_pred"
  ori_blob: "ori_pred"
  dim_blob: "dim_pred"
  lof_blob: "lof_pred"
  lor_blob: "lor_pred"
  seg_blob: "seg_prob"
  input_blob: "data"
}
nms_param {
  type: "NormalNMS"
  threshold: 0.4
  sigma: 0.4
  inter_cls_nms_thresh: 1
  cross_class_merge_thresh: 1
}

```

然后开始初始化cnn深度学习网络

net_param接收yolo_param参数
model_param接收yolo_param参数

利用确定GetAbsolutePath方法确定以下参数:
* model_root --- yolo3d_1128
* proto_file --- deploy.pt
* weight_file --- deploy.md
* feature_file --- ???
* model_type -- Caffe


创建input和output参数用于接受net的参数

cnnadapter是整个网络的灵魂,链接整个网络
`std::shared_ptr<CNNAdapter> cnnadapter_;`
类型为CNNAdapter,其定义来自于apollo/modules/perception/obstacle/camera/common/cnn_adapter.cc

CNNCaffe继承了CNNAdapter,实现了init方法(apollo/modules/perception/obstacle/camera/common/cnn_adapter.cc)





#### geometry_camera_converter.cc

识别的obj传入函数Convert
CheckSizeSanity根据type分类~利用std::max确定尺寸
CheckTruncation根据obj利用盒子模型截取

找到左上角点和右下角点
todo


