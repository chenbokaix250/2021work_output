>auto/ros/src/computing/perception
```
.
├── detection
│   ├── fusion_tools
│   │   └── packages
│   │       ├── pixel_cloud_fusion
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── include
│   │       │   │   └── pixel_cloud_fusion
│   │       │   │       └── pixel_cloud_fusion.h
│   │       │   ├── launch
│   │       │   │   └── pixel_cloud_fusion.launch
│   │       │   ├── package.xml
│   │       │   ├── README.md
│   │       │   └── src
│   │       │       ├── pixel_cloud_fusion.cpp
│   │       │       └── pixel_cloud_fusion_node.cpp
│   │       └── range_vision_fusion
│   │           ├── CHANGELOG.rst
│   │           ├── CMakeLists.txt
│   │           ├── include
│   │           │   └── range_vision_fusion
│   │           │       └── range_vision_fusion.h
│   │           ├── launch
│   │           │   └── range_vision_fusion.launch
│   │           ├── package.xml
│   │           ├── README.md
│   │           └── src
│   │               ├── range_vision_fusion.cpp
│   │               └── range_vision_fusion_node.cpp
│   ├── lidar_detector
│   │   └── packages
│   │       ├── lidar_apollo_cnn_seg_detect
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── include
│   │       │   │   ├── cluster2d.h
│   │       │   │   ├── cnn_segmentation.h
│   │       │   │   ├── disjoint_set.h
│   │       │   │   ├── feature_generator.h
│   │       │   │   ├── pcl_types.h
│   │       │   │   └── util.h
│   │       │   ├── launch
│   │       │   │   └── lidar_apollo_cnn_seg_detect.launch
│   │       │   ├── models
│   │       │   ├── nodes
│   │       │   │   ├── cluster2d.cpp
│   │       │   │   ├── cnn_segmentation.cpp
│   │       │   │   ├── feature_generator.cpp
│   │       │   │   └── lidar_apollo_cnn_seg_detect_node.cpp
│   │       │   ├── package.xml
│   │       │   └── README.md
│   │       ├── lidar_euclidean_cluster_detect
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── include
│   │       │   │   ├── cluster.h
│   │       │   │   ├── gencolors.cpp
│   │       │   │   └── gpu_euclidean_clustering.h
│   │       │   ├── interface.yaml
│   │       │   ├── launch
│   │       │   │   ├── euclidean_clustering_Exp.launch
│   │       │   │   └── lidar_euclidean_cluster_detect.launch
│   │       │   ├── nodes
│   │       │   │   └── lidar_euclidean_cluster_detect
│   │       │   │       ├── cluster.cpp
│   │       │   │       ├── gpu_euclidean_clustering.cu
│   │       │   │       └── lidar_euclidean_cluster_detect.cpp
│   │       │   └── package.xml
│   │       ├── lidar_fake_perception
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── include
│   │       │   │   └── lidar_fake_perception.h
│   │       │   ├── interface.yaml
│   │       │   ├── launch
│   │       │   │   └── lidar_fake_perception.launch
│   │       │   ├── nodes
│   │       │   │   ├── lidar_fake_perception.cpp
│   │       │   │   └── lidar_fake_perception_node.cpp
│   │       │   ├── package.xml
│   │       │   └── README.md
│   │       ├── lidar_naive_l_shape_detect
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── include
│   │       │   │   └── lidar_naive_l_shape_detect.h
│   │       │   ├── interface.yaml
│   │       │   ├── launch
│   │       │   │   └── lidar_naive_l_shape_detect.launch
│   │       │   ├── nodes
│   │       │   │   └── lidar_naive_l_shape_detect
│   │       │   │       ├── lidar_naive_l_shape_detect.cpp
│   │       │   │       └── lidar_naive_l_shape_detect_node.cpp
│   │       │   ├── package.xml
│   │       │   └── README.md
│   │       └── lidar_point_pillars
│   │           ├── CHANGELOG.rst
│   │           ├── CMakeLists.txt
│   │           ├── include
│   │           │   └── lidar_point_pillars
│   │           │       ├── anchor_mask_cuda.h
│   │           │       ├── common.h
│   │           │       ├── nms_cuda.h
│   │           │       ├── point_pillars.h
│   │           │       ├── point_pillars_ros.h
│   │           │       ├── postprocess_cuda.h
│   │           │       ├── preprocess_points_cuda.h
│   │           │       ├── preprocess_points.h
│   │           │       └── scatter_cuda.h
│   │           ├── launch
│   │           │   └── lidar_point_pillars.launch
│   │           ├── nodes
│   │           │   ├── anchor_mask_cuda.cu
│   │           │   ├── lidar_point_pillars_node.cpp
│   │           │   ├── nms_cuda.cu
│   │           │   ├── point_pillars.cpp
│   │           │   ├── point_pillars_ros.cpp
│   │           │   ├── postprocess_cuda.cu
│   │           │   ├── preprocess_points.cpp
│   │           │   ├── preprocess_points_cuda.cu
│   │           │   └── scatter_cuda.cu
│   │           ├── package.xml
│   │           ├── README.md
│   │           └── test
│   │               ├── data
│   │               │   └── dummy.onnx
│   │               └── src
│   │                   └── test_point_pillars.cpp
│   ├── lidar_tracker
│   │   └── packages
│   │       ├── lidar_imm_ukf_pda_track
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── include
│   │       │   │   ├── imm_ukf_pda.h
│   │       │   │   └── ukf.h
│   │       │   ├── launch
│   │       │   │   └── imm_ukf_pda_track.launch
│   │       │   ├── nodes
│   │       │   │   └── imm_ukf_pda
│   │       │   │       ├── imm_ukf_pda.cpp
│   │       │   │       ├── imm_ukf_pda_main.cpp
│   │       │   │       └── ukf.cpp
│   │       │   ├── package.xml
│   │       │   └── README.md
│   │       └── lidar_kf_contour_track
│   │           ├── CHANGELOG.rst
│   │           ├── CMakeLists.txt
│   │           ├── include
│   │           │   ├── lidar_kf_contour_track_core.h
│   │           │   ├── PolygonGenerator.h
│   │           │   └── SimpleTracker.h
│   │           ├── interface.yaml
│   │           ├── launch
│   │           │   └── lidar_kf_contour_track.launch
│   │           ├── nodes
│   │           │   └── lidar_kf_contour_track
│   │           │       ├── lidar_kf_contour_track_core.cpp
│   │           │       ├── lidar_kf_contour_track.cpp
│   │           │       ├── PolygonGenerator.cpp
│   │           │       └── SimpleTracker.cpp
│   │           ├── package.xml
│   │           └── README.md
│   ├── object_filter
│   │   └── packages
│   │       ├── lidar_shape_estimation
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── include
│   │       │   │   └── lidar_shape_estimation
│   │       │   │       ├── model_interface.hpp
│   │       │   │       ├── node.hpp
│   │       │   │       └── shape_estimator.hpp
│   │       │   ├── launch
│   │       │   │   ├── shape_estimation_clustering.launch
│   │       │   │   ├── shape_estimation_fusion.launch
│   │       │   │   └── shape_estimation_tracking.launch
│   │       │   ├── package.xml
│   │       │   ├── README.md
│   │       │   ├── src
│   │       │   │   ├── main.cpp
│   │       │   │   ├── model
│   │       │   │   │   ├── bounding_box.cpp
│   │       │   │   │   ├── bounding_box.hpp
│   │       │   │   │   ├── convex_hull.cpp
│   │       │   │   │   ├── convex_hull.hpp
│   │       │   │   │   ├── cylinder.cpp
│   │       │   │   │   └── cylinder.hpp
│   │       │   │   ├── node.cpp
│   │       │   │   └── shape_estimator.cpp
│   │       │   └── test
│   │       │       ├── src
│   │       │       │   └── test_lidar_shape_estimation.cpp
│   │       │       └── test_lidar_shape_estimation.test
│   │       └── roi_object_filter
│   │           ├── CHANGELOG.rst
│   │           ├── CMakeLists.txt
│   │           ├── include
│   │           │   └── roi_object_filter
│   │           │       └── roi_object_filter.h
│   │           ├── package.xml
│   │           ├── README.md
│   │           ├── src
│   │           │   ├── roi_object_filter.cpp
│   │           │   └── roi_object_filter_node.cpp
│   │           └── test
│   │               ├── src
│   │               │   └── test_roi_object_filter.cpp
│   │               └── test_roi_object_filter.test
│   ├── trafficlight_recognizer
│   │   ├── CHANGELOG.rst
│   │   ├── CMakeLists.txt
│   │   ├── include
│   │   │   ├── Context.h
│   │   │   └── TrafficLight.h
│   │   ├── interface.yaml
│   │   ├── launch
│   │   │   ├── feat_proj.launch
│   │   │   ├── roi_extractor.launch
│   │   │   ├── traffic_light_recognition.launch
│   │   │   ├── traffic_light_recognition_mxnet.launch
│   │   │   └── traffic_light_recognition_ssd.launch
│   │   ├── lib
│   │   │   └── Context.cpp
│   │   ├── nodes
│   │   │   ├── feat_proj
│   │   │   │   ├── feat_proj.cpp
│   │   │   │   └── Rate.h
│   │   │   ├── label_maker
│   │   │   │   ├── custom_graphics_view.cpp
│   │   │   │   ├── custom_graphics_view.h
│   │   │   │   ├── file_system_operator.cpp
│   │   │   │   ├── file_system_operator.h
│   │   │   │   ├── label_maker.cpp
│   │   │   │   ├── label_maker_gui.cpp
│   │   │   │   ├── label_maker_gui.h
│   │   │   │   ├── label_maker_gui.ui
│   │   │   │   └── label_maker.pro
│   │   │   ├── region_tlr
│   │   │   │   ├── region_tlr.cpp
│   │   │   │   ├── RegionTLR.h
│   │   │   │   ├── TrafficLightDetector.cpp
│   │   │   │   └── TrafficLightDetector.h
│   │   │   ├── region_tlr_mxnet
│   │   │   │   ├── mxnet_traffic_light_recognizer.cpp
│   │   │   │   ├── mxnet_traffic_light_recognizer.h
│   │   │   │   ├── README.md
│   │   │   │   ├── region_tlr_mxnet.cpp
│   │   │   │   └── region_tlr_mxnet.h
│   │   │   ├── region_tlr_ssd
│   │   │   │   ├── README.md
│   │   │   │   ├── region_tlr_ssd.cpp
│   │   │   │   ├── region_tlr_ssd.h
│   │   │   │   ├── traffic_light_recognizer.cpp
│   │   │   │   └── traffic_light_recognizer.h
│   │   │   ├── roi_extractor
│   │   │   │   ├── roi_extractor.cpp
│   │   │   │   └── roi_extractor.h
│   │   │   ├── tlr_tuner
│   │   │   │   ├── mainwindow.cpp
│   │   │   │   ├── mainwindow.h
│   │   │   │   ├── mainwindow.ui
│   │   │   │   ├── qt_test.pro
│   │   │   │   ├── qt_test.pro.user
│   │   │   │   ├── tlr_tuner.cpp
│   │   │   │   ├── tunerBody.cpp
│   │   │   │   └── tunerBody.h
│   │   │   └── tl_switch
│   │   │       ├── README.md
│   │   │       └── tl_switch.cpp
│   │   └── package.xml
│   ├── vision_detector
│   │   ├── libs
│   │   │   └── dpm_ttic
│   │   │       ├── CHANGELOG.rst
│   │   │       ├── CMakeLists.txt
│   │   │       ├── common
│   │   │       │   ├── common.cpp
│   │   │       │   └── common.hpp
│   │   │       ├── cpu
│   │   │       │   ├── detect.cpp
│   │   │       │   ├── detect.hpp
│   │   │       │   ├── dt.cpp
│   │   │       │   ├── dt.hpp
│   │   │       │   ├── fconvsMT.cpp
│   │   │       │   ├── fconvsMT.hpp
│   │   │       │   ├── featurepyramid.cpp
│   │   │       │   ├── featurepyramid.hpp
│   │   │       │   ├── get_boxes.cpp
│   │   │       │   ├── get_boxes.hpp
│   │   │       │   ├── load_model.cpp
│   │   │       │   ├── load_model.hpp
│   │   │       │   ├── main.cpp
│   │   │       │   ├── MODEL_info.h
│   │   │       │   ├── nms.cpp
│   │   │       │   ├── nms.hpp
│   │   │       │   ├── resize.cpp
│   │   │       │   ├── resize.hpp
│   │   │       │   ├── switch_float.h
│   │   │       │   ├── tracking.cpp
│   │   │       │   └── tracking.hpp
│   │   │       ├── gpu
│   │   │       │   ├── cuda_util.cpp
│   │   │       │   ├── cuda_util.hpp
│   │   │       │   ├── detect.cpp
│   │   │       │   ├── detect.hpp
│   │   │       │   ├── drvapi_error_string.h
│   │   │       │   ├── dt_GPU.cpp
│   │   │       │   ├── dt_GPU.hpp
│   │   │       │   ├── fconvsMT.cpp
│   │   │       │   ├── fconvsMT.hpp
│   │   │       │   ├── featurepyramid.cpp
│   │   │       │   ├── featurepyramid.hpp
│   │   │       │   ├── for_use_GPU.h
│   │   │       │   ├── get_boxes.cpp
│   │   │       │   ├── get_boxes.hpp
│   │   │       │   ├── GPU_function.cu
│   │   │       │   ├── GPU_init.cpp
│   │   │       │   ├── GPU_init.hpp
│   │   │       │   ├── load_model.cpp
│   │   │       │   ├── load_model.hpp
│   │   │       │   ├── MODEL_info.h
│   │   │       │   ├── multithreading.cpp
│   │   │       │   ├── multithreading.h
│   │   │       │   ├── nms.cpp
│   │   │       │   ├── nms.hpp
│   │   │       │   ├── obstacle_detection.cpp
│   │   │       │   ├── resize_GPU.cc
│   │   │       │   ├── resize_GPU.cpp
│   │   │       │   ├── resize_GPU.hpp
│   │   │       │   ├── switch_float.h
│   │   │       │   ├── switch_release.h
│   │   │       │   ├── tracking.cpp
│   │   │       │   └── tracking.hpp
│   │   │       ├── include
│   │   │       │   └── libdpm_ttic
│   │   │       │       └── dpm_ttic.hpp
│   │   │       ├── package.xml
│   │   │       └── util
│   │   │           └── capability_version_checker.cpp
│   │   └── packages
│   │       ├── vision_darknet_detect
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── darknet
│   │       │   │   ├── cfg
│   │       │   │   │   ├── coco.names
│   │       │   │   │   ├── voc.names
│   │       │   │   │   ├── yolov2.cfg
│   │       │   │   │   ├── yolov2-tiny.cfg
│   │       │   │   │   ├── yolov3.cfg
│   │       │   │   │   ├── yolov3-tiny.cfg
│   │       │   │   │   └── yolov3-voc.cfg
│   │       │   │   └── src
│   │       │   │       ├── activation_kernels.cu
│   │       │   │       ├── activation_layer.c
│   │       │   │       ├── activation_layer.h
│   │       │   │       ├── activations.c
│   │       │   │       ├── activations.h
│   │       │   │       ├── avgpool_layer.c
│   │       │   │       ├── avgpool_layer.h
│   │       │   │       ├── avgpool_layer_kernels.cu
│   │       │   │       ├── batchnorm_layer.c
│   │       │   │       ├── batchnorm_layer.h
│   │       │   │       ├── blas.c
│   │       │   │       ├── blas.h
│   │       │   │       ├── blas_kernels.cu
│   │       │   │       ├── box.c
│   │       │   │       ├── box.h
│   │       │   │       ├── classifier.h
│   │       │   │       ├── col2im.c
│   │       │   │       ├── col2im.h
│   │       │   │       ├── col2im_kernels.cu
│   │       │   │       ├── connected_layer.c
│   │       │   │       ├── connected_layer.h
│   │       │   │       ├── convolutional_kernels.cu
│   │       │   │       ├── convolutional_layer.c
│   │       │   │       ├── convolutional_layer.h
│   │       │   │       ├── cost_layer.c
│   │       │   │       ├── cost_layer.h
│   │       │   │       ├── crnn_layer.c
│   │       │   │       ├── crnn_layer.h
│   │       │   │       ├── crop_layer.c
│   │       │   │       ├── crop_layer.h
│   │       │   │       ├── crop_layer_kernels.cu
│   │       │   │       ├── cuda.c
│   │       │   │       ├── cuda.h
│   │       │   │       ├── darknet.h
│   │       │   │       ├── data.c
│   │       │   │       ├── data.h
│   │       │   │       ├── deconvolutional_kernels.cu
│   │       │   │       ├── deconvolutional_layer.c
│   │       │   │       ├── deconvolutional_layer.h
│   │       │   │       ├── demo.c
│   │       │   │       ├── demo.h
│   │       │   │       ├── detection_layer.c
│   │       │   │       ├── detection_layer.h
│   │       │   │       ├── dropout_layer.c
│   │       │   │       ├── dropout_layer.h
│   │       │   │       ├── dropout_layer_kernels.cu
│   │       │   │       ├── gemm.c
│   │       │   │       ├── gemm.h
│   │       │   │       ├── gru_layer.c
│   │       │   │       ├── gru_layer.h
│   │       │   │       ├── im2col.c
│   │       │   │       ├── im2col.h
│   │       │   │       ├── im2col_kernels.cu
│   │       │   │       ├── image.c
│   │       │   │       ├── image.h
│   │       │   │       ├── l2norm_layer.c
│   │       │   │       ├── l2norm_layer.h
│   │       │   │       ├── layer.c
│   │       │   │       ├── layer.h
│   │       │   │       ├── list.c
│   │       │   │       ├── list.h
│   │       │   │       ├── local_layer.c
│   │       │   │       ├── local_layer.h
│   │       │   │       ├── logistic_layer.c
│   │       │   │       ├── logistic_layer.h
│   │       │   │       ├── lstm_layer.c
│   │       │   │       ├── lstm_layer.h
│   │       │   │       ├── matrix.c
│   │       │   │       ├── matrix.h
│   │       │   │       ├── maxpool_layer.c
│   │       │   │       ├── maxpool_layer.h
│   │       │   │       ├── maxpool_layer_kernels.cu
│   │       │   │       ├── network.c
│   │       │   │       ├── network.h
│   │       │   │       ├── normalization_layer.c
│   │       │   │       ├── normalization_layer.h
│   │       │   │       ├── option_list.c
│   │       │   │       ├── option_list.h
│   │       │   │       ├── parser.c
│   │       │   │       ├── parser.h
│   │       │   │       ├── region_layer.c
│   │       │   │       ├── region_layer.h
│   │       │   │       ├── reorg_layer.c
│   │       │   │       ├── reorg_layer.h
│   │       │   │       ├── rnn_layer.c
│   │       │   │       ├── rnn_layer.h
│   │       │   │       ├── route_layer.c
│   │       │   │       ├── route_layer.h
│   │       │   │       ├── shortcut_layer.c
│   │       │   │       ├── shortcut_layer.h
│   │       │   │       ├── softmax_layer.c
│   │       │   │       ├── softmax_layer.h
│   │       │   │       ├── stb_image.h
│   │       │   │       ├── stb_image_write.h
│   │       │   │       ├── tree.c
│   │       │   │       ├── tree.h
│   │       │   │       ├── upsample_layer.c
│   │       │   │       ├── upsample_layer.h
│   │       │   │       ├── utils.c
│   │       │   │       ├── utils.h
│   │       │   │       ├── yolo_layer.c
│   │       │   │       └── yolo_layer.h
│   │       │   ├── interface.yaml
│   │       │   ├── launch
│   │       │   │   ├── vision_yolo2_detect.launch
│   │       │   │   └── vision_yolo3_detect.launch
│   │       │   ├── package.xml
│   │       │   ├── README.md
│   │       │   └── src
│   │       │       ├── gencolors.cpp
│   │       │       ├── rect_class_score.h
│   │       │       ├── vision_darknet_detect.cpp
│   │       │       ├── vision_darknet_detect.h
│   │       │       └── vision_darknet_detect_node.cpp
│   │       ├── vision_dpm_ttic_detect
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── data
│   │       │   │   ├── car_2008.xml
│   │       │   │   ├── car_comp.csv
│   │       │   │   ├── car_part.csv
│   │       │   │   ├── car_root.csv
│   │       │   │   ├── car.xml
│   │       │   │   ├── person_comp.csv
│   │       │   │   ├── person_part.csv
│   │       │   │   ├── person_root.csv
│   │       │   │   └── person.xml
│   │       │   ├── interface.yaml
│   │       │   ├── launch
│   │       │   │   └── vision_dpm_ttic_detect.launch
│   │       │   ├── nodes
│   │       │   │   └── vision_dpm_ttic_detect
│   │       │   │       └── vision_dpm_ttic_detect.cpp
│   │       │   └── package.xml
│   │       ├── vision_lane_detect
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── interface.yaml
│   │       │   ├── nodes
│   │       │   │   └── vision_lane_detect
│   │       │   │       ├── utils.h
│   │       │   │       └── vision_lane_detect.cpp
│   │       │   └── package.xml
│   │       ├── vision_segment_enet_detect
│   │       │   ├── CHANGELOG.rst
│   │       │   ├── CMakeLists.txt
│   │       │   ├── include
│   │       │   │   └── vision_segment_enet_detect.h
│   │       │   ├── launch
│   │       │   │   └── vision_segment_enet_detect.launch
│   │       │   ├── nodes
│   │       │   │   └── vision_segment_enet_detect
│   │       │   │       ├── vision_segment_enet_detect.cpp
│   │       │   │       └── vision_segment_enet_detect_node.cpp
│   │       │   ├── package.xml
│   │       │   └── README.md
│   │       └── vision_ssd_detect
│   │           ├── CHANGELOG.rst
│   │           ├── CMakeLists.txt
│   │           ├── include
│   │           │   ├── gencolors.cpp
│   │           │   ├── rect_class_score.h
│   │           │   └── vision_ssd_detect.h
│   │           ├── interface.yaml
│   │           ├── launch
│   │           │   └── vision_ssd_detect.launch
│   │           ├── package.xml
│   │           ├── README.md
│   │           └── src
│   │               ├── vision_ssd_detect.cpp
│   │               └── vision_ssd_detect_node.cpp
│   ├── vision_tracker
│   │   └── packages
│   │       └── vision_beyond_track
│   │           ├── CHANGELOG.rst
│   │           ├── CMakeLists.txt
│   │           ├── include
│   │           │   ├── detection.h
│   │           │   └── vision_beyond_track.h
│   │           ├── launch
│   │           │   └── vision_beyond_track.launch
│   │           ├── lib
│   │           │   ├── clipper.cpp
│   │           │   ├── clipper.hpp
│   │           │   ├── hungarian.cpp
│   │           │   └── hungarian.h
│   │           ├── package.xml
│   │           ├── README.md
│   │           └── src
│   │               ├── gencolors.cpp
│   │               ├── vision_beyond_track.cpp
│   │               └── vision_beyond_track_node.cpp
│   └── visualizers
│       └── packages
│           ├── detected_objects_visualizer
│           │   ├── CHANGELOG.rst
│           │   ├── CMakeLists.txt
│           │   ├── include
│           │   │   ├── visualize_detected_objects.h
│           │   │   └── visualize_rects.h
│           │   ├── models
│           │   │   ├── bike.dae
│           │   │   ├── box.dae
│           │   │   ├── bus.dae
│           │   │   ├── car.dae
│           │   │   ├── person.dae
│           │   │   └── truck.dae
│           │   ├── package.xml
│           │   ├── README.md
│           │   └── src
│           │       ├── visualize_detected_objects.cpp
│           │       ├── visualize_detected_objects_main.cpp
│           │       ├── visualize_rects.cpp
│           │       └── visualize_rects_main.cpp
│           └── integrated_viewer
│               ├── CHANGELOG.rst
│               ├── CMakeLists.txt
│               ├── include
│               │   └── gencolors.cpp
│               ├── lib
│               │   └── convert_image.h
│               ├── node
│               │   ├── data_rate_checker_plugin
│               │   │   ├── data_rate_checker_form.ui
│               │   │   ├── data_rate_checker_plugin.cpp
│               │   │   └── data_rate_checker_plugin.h
│               │   ├── image_viewer_plugin
│               │   │   ├── autoware_logo.png
│               │   │   ├── car.png
│               │   │   ├── draw_lane.cpp
│               │   │   ├── draw_lane.h
│               │   │   ├── draw_points.cpp
│               │   │   ├── draw_points.h
│               │   │   ├── draw_rects.cpp
│               │   │   ├── draw_rects.h
│               │   │   ├── image_viewer_form.ui
│               │   │   ├── image_viewer_plugin.cpp
│               │   │   ├── image_viewer_plugin.h
│               │   │   └── pedestrian.png
│               │   └── traffic_light_plugin
│               │       ├── form.ui
│               │       ├── traffic_light_plugin.cpp
│               │       └── traffic_light_plugin.h
│               ├── package.xml
│               └── rviz_plugin_description.xml
├── localization
│   ├── lib
│   │   ├── gnss
│   │   │   ├── CHANGELOG.rst
│   │   │   ├── CMakeLists.txt
│   │   │   ├── include
│   │   │   │   └── gnss
│   │   │   │       └── geo_pos_conv.hpp
│   │   │   ├── package.xml
│   │   │   └── src
│   │   │       └── geo_pos_conv.cpp
│   │   ├── ndt_cpu
│   │   │   ├── CHANGELOG.rst
│   │   │   ├── CMakeLists.txt
│   │   │   ├── include
│   │   │   │   └── ndt_cpu
│   │   │   │       ├── debug.h
│   │   │   │       ├── NormalDistributionsTransform.h
│   │   │   │       ├── Octree.h
│   │   │   │       ├── Registration.h
│   │   │   │       ├── SymmetricEigenSolver.h
│   │   │   │       └── VoxelGrid.h
│   │   │   ├── package.xml
│   │   │   └── src
│   │   │       ├── NormalDistributionsTransform.cpp
│   │   │       ├── Octree.cpp
│   │   │       ├── Registration.cpp
│   │   │       └── VoxelGrid.cpp
│   │   ├── ndt_gpu
│   │   │   ├── CHANGELOG.rst
│   │   │   ├── CMakeLists.txt
│   │   │   ├── include
│   │   │   │   └── ndt_gpu
│   │   │   │       ├── common.h
│   │   │   │       ├── debug.h
│   │   │   │       ├── MatrixDevice.h
│   │   │   │       ├── Matrix.h
│   │   │   │       ├── MatrixHost.h
│   │   │   │       ├── NormalDistributionsTransform.h
│   │   │   │       ├── Registration.h
│   │   │   │       ├── SymmetricEigenSolver.h
│   │   │   │       └── VoxelGrid.h
│   │   │   ├── package.xml
│   │   │   └── src
│   │   │       ├── MatrixDevice.cu
│   │   │       ├── MatrixHost.cu
│   │   │       ├── NormalDistributionsTransform.cu
│   │   │       ├── Registration.cu
│   │   │       ├── SymmetricEigenSolver.cu
│   │   │       └── VoxelGrid.cu
│   │   ├── ndt_tku
│   │   │   ├── CHANGELOG.rst
│   │   │   ├── CMakeLists.txt
│   │   │   ├── include
│   │   │   │   ├── algebra.h
│   │   │   │   └── ndt.h
│   │   │   ├── package.xml
│   │   │   └── src
│   │   │       ├── algebra.cpp
│   │   │       ├── manage_ND.cpp
│   │   │       └── newton.cpp
│   │   └── pcl_omp_registration
│   │       ├── CHANGELOG.rst
│   │       ├── CMakeLists.txt
│   │       ├── include
│   │       │   └── pcl_omp_registration
│   │       │       ├── impl
│   │       │       │   ├── ndt.hpp
│   │       │       │   └── registration.hpp
│   │       │       ├── ndt.h
│   │       │       └── registration.h
│   │       ├── package.xml
│   │       └── src
│   │           └── ndt.cpp
│   └── packages
│       ├── autoware_connector
│       │   ├── CHANGELOG.rst
│       │   ├── CMakeLists.txt
│       │   ├── interface.yaml
│       │   ├── launch
│       │   │   ├── can2odom.launch
│       │   │   └── vel_pose_connect.launch
│       │   ├── nodes
│       │   │   ├── can_odometry
│       │   │   │   ├── can_odometry_core.cpp
│       │   │   │   ├── can_odometry_core.h
│       │   │   │   └── can_odometry_node.cpp
│       │   │   └── can_status_translator
│       │   │       ├── can_status_translator_core.cpp
│       │   │       ├── can_status_translator_core.h
│       │   │       └── can_status_translator_node.cpp
│       │   └── package.xml
│       ├── gnss_localizer
│       │   ├── CHANGELOG.rst
│       │   ├── CMakeLists.txt
│       │   ├── interface.yaml
│       │   ├── launch
│       │   │   ├── fix2tfpose.launch
│       │   │   └── nmea2tfpose.launch
│       │   ├── nodes
│       │   │   ├── fix2tfpose
│       │   │   │   └── fix2tfpose.cpp
│       │   │   └── nmea2tfpose
│       │   │       ├── nmea2tfpose_core.cpp
│       │   │       ├── nmea2tfpose_core.h
│       │   │       └── nmea2tfpose_node.cpp
│       │   └── package.xml
│       └── lidar_localizer
│           ├── CHANGELOG.rst
│           ├── CMakeLists.txt
│           ├── interface.yaml
│           ├── launch
│           │   ├── approximate_ndt_mapping.launch
│           │   ├── icp_matching.launch
│           │   ├── ndt_mapping.launch
│           │   ├── ndt_mapping_tku.launch
│           │   ├── ndt_matching.launch
│           │   ├── ndt_matching_monitor.launch
│           │   ├── ndt_matching_tku.launch
│           │   └── ndt_matching_tku_org.launch
│           ├── nodes
│           │   ├── approximate_ndt_mapping
│           │   │   └── approximate_ndt_mapping.cpp
│           │   ├── icp_matching
│           │   │   └── icp_matching.cpp
│           │   ├── ndt_mapping
│           │   │   └── ndt_mapping.cpp
│           │   ├── ndt_mapping_tku
│           │   │   ├── mapping.cpp
│           │   │   └── ndt_mapping_tku.cpp
│           │   ├── ndt_matching
│           │   │   └── ndt_matching.cpp
│           │   ├── ndt_matching_monitor
│           │   │   ├── ndt_matching_monitor.cpp
│           │   │   ├── ndt_matching_monitor.h
│           │   │   ├── ndt_matching_monitor_node.cpp
│           │   │   └── README.md
│           │   ├── ndt_matching_tku
│           │   │   └── ndt_matching_tku.cpp
│           │   └── queue_counter
│           │       └── queue_counter.cpp
│           └── package.xml
├── prediction
│   └── motion_predictor
│       └── packages
│           └── naive_motion_predict
│               ├── CHANGELOG.rst
│               ├── CMakeLists.txt
│               ├── include
│               │   └── naive_motion_predict.h
│               ├── interface.yaml
│               ├── launch
│               │   └── naive_motion_predict.launch
│               ├── nodes
│               │   └── naive_motion_predict
│               │       ├── naive_motion_predict.cpp
│               │       └── naive_motion_predict_node.cpp
│               ├── package.xml
│               └── README.md
└── semantics
    └── packages
        ├── costmap_generator
        │   ├── CHANGELOG.rst
        │   ├── CMakeLists.txt
        │   ├── include
        │   │   └── costmap_generator
        │   │       ├── costmap_generator.h
        │   │       ├── objects_to_costmap.h
        │   │       └── points_to_costmap.h
        │   ├── interface.yml
        │   ├── launch
        │   │   └── costmap_generator.launch
        │   ├── nodes
        │   │   └── costmap_generator
        │   │       ├── costmap_generator.cpp
        │   │       ├── costmap_generator_node.cpp
        │   │       ├── objects_to_costmap.cpp
        │   │       └── points_to_costmap.cpp
        │   ├── package.xml
        │   ├── README.md
        │   └── test
        │       └── src
        │           ├── test_costmap_generator.cpp
        │           └── test_costmap_generator.hpp
        ├── object_map
        │   ├── CHANGELOG.rst
        │   ├── CMakeLists.txt
        │   ├── config
        │   │   ├── grid_map_filter.yaml
        │   │   └── potential.yaml
        │   ├── include
        │   │   └── object_map
        │   │       ├── object_map_utils.cpp
        │   │       └── object_map_utils.hpp
        │   ├── interface.yaml
        │   ├── launch
        │   │   ├── grid_map_filter.launch
        │   │   ├── laserscan2costmap.launch
        │   │   ├── points2costmap.launch
        │   │   ├── potential_field.launch
        │   │   └── wayarea2grid.launch
        │   ├── nodes
        │   │   ├── grid_map_filter
        │   │   │   ├── grid_map_filter.cpp
        │   │   │   ├── grid_map_filter.h
        │   │   │   └── grid_map_filter_node.cpp
        │   │   ├── laserscan2costmap
        │   │   │   └── laserscan2costmap.cpp
        │   │   ├── points2costmap
        │   │   │   └── points2costmap.cpp
        │   │   ├── potential_field
        │   │   │   └── potential_field.cpp
        │   │   └── wayarea2grid
        │   │       ├── wayarea2grid.cpp
        │   │       ├── wayarea2grid.h
        │   │       └── wayarea2grid_node.cpp
        │   ├── package.xml
        │   └── README.md
        └── road_occupancy_processor
            ├── CHANGELOG.rst
            ├── CMakeLists.txt
            ├── doc
            │   └── road_occupancy_processor.jpg
            ├── include
            │   └── road_occupancy_processor
            │       └── road_occupancy_processor.h
            ├── interface.yaml
            ├── launch
            │   └── road_occupancy_processor.launch
            ├── package.xml
            ├── README.md
            └── src
                ├── road_occupancy_processor.cpp
                └── road_occupancy_processor_node.cpp

215 directories, 618 files
```



### vision_detector的文件结构
```
.
├── libs
│   └── dpm_ttic
│       ├── CHANGELOG.rst
│       ├── CMakeLists.txt
│       ├── common
│       │   ├── common.cpp
│       │   └── common.hpp
│       ├── cpu
│       │   ├── detect.cpp
│       │   ├── detect.hpp
│       │   ├── dt.cpp
│       │   ├── dt.hpp
│       │   ├── fconvsMT.cpp
│       │   ├── fconvsMT.hpp
│       │   ├── featurepyramid.cpp
│       │   ├── featurepyramid.hpp
│       │   ├── get_boxes.cpp
│       │   ├── get_boxes.hpp
│       │   ├── load_model.cpp
│       │   ├── load_model.hpp
│       │   ├── main.cpp
│       │   ├── MODEL_info.h
│       │   ├── nms.cpp
│       │   ├── nms.hpp
│       │   ├── resize.cpp
│       │   ├── resize.hpp
│       │   ├── switch_float.h
│       │   ├── tracking.cpp
│       │   └── tracking.hpp
│       ├── gpu
│       │   ├── cuda_util.cpp
│       │   ├── cuda_util.hpp
│       │   ├── detect.cpp
│       │   ├── detect.hpp
│       │   ├── drvapi_error_string.h
│       │   ├── dt_GPU.cpp
│       │   ├── dt_GPU.hpp
│       │   ├── fconvsMT.cpp
│       │   ├── fconvsMT.hpp
│       │   ├── featurepyramid.cpp
│       │   ├── featurepyramid.hpp
│       │   ├── for_use_GPU.h
│       │   ├── get_boxes.cpp
│       │   ├── get_boxes.hpp
│       │   ├── GPU_function.cu
│       │   ├── GPU_init.cpp
│       │   ├── GPU_init.hpp
│       │   ├── load_model.cpp
│       │   ├── load_model.hpp
│       │   ├── MODEL_info.h
│       │   ├── multithreading.cpp
│       │   ├── multithreading.h
│       │   ├── nms.cpp
│       │   ├── nms.hpp
│       │   ├── obstacle_detection.cpp
│       │   ├── resize_GPU.cc
│       │   ├── resize_GPU.cpp
│       │   ├── resize_GPU.hpp
│       │   ├── switch_float.h
│       │   ├── switch_release.h
│       │   ├── tracking.cpp
│       │   └── tracking.hpp
│       ├── include
│       │   └── libdpm_ttic
│       │       └── dpm_ttic.hpp
│       ├── package.xml
│       └── util
│           └── capability_version_checker.cpp
└── packages
    ├── vision_darknet_detect
    │   ├── CHANGELOG.rst
    │   ├── CMakeLists.txt
    │   ├── darknet
    │   │   ├── cfg
    │   │   │   ├── coco.names
    │   │   │   ├── voc.names
    │   │   │   ├── yolov2.cfg
    │   │   │   ├── yolov2-tiny.cfg
    │   │   │   ├── yolov3.cfg
    │   │   │   ├── yolov3-tiny.cfg
    │   │   │   └── yolov3-voc.cfg
    │   │   └── src
    │   │       ├── activation_kernels.cu
    │   │       ├── activation_layer.c
    │   │       ├── activation_layer.h
    │   │       ├── activations.c
    │   │       ├── activations.h
    │   │       ├── avgpool_layer.c
    │   │       ├── avgpool_layer.h
    │   │       ├── avgpool_layer_kernels.cu
    │   │       ├── batchnorm_layer.c
    │   │       ├── batchnorm_layer.h
    │   │       ├── blas.c
    │   │       ├── blas.h
    │   │       ├── blas_kernels.cu
    │   │       ├── box.c
    │   │       ├── box.h
    │   │       ├── classifier.h
    │   │       ├── col2im.c
    │   │       ├── col2im.h
    │   │       ├── col2im_kernels.cu
    │   │       ├── connected_layer.c
    │   │       ├── connected_layer.h
    │   │       ├── convolutional_kernels.cu
    │   │       ├── convolutional_layer.c
    │   │       ├── convolutional_layer.h
    │   │       ├── cost_layer.c
    │   │       ├── cost_layer.h
    │   │       ├── crnn_layer.c
    │   │       ├── crnn_layer.h
    │   │       ├── crop_layer.c
    │   │       ├── crop_layer.h
    │   │       ├── crop_layer_kernels.cu
    │   │       ├── cuda.c
    │   │       ├── cuda.h
    │   │       ├── darknet.h
    │   │       ├── data.c
    │   │       ├── data.h
    │   │       ├── deconvolutional_kernels.cu
    │   │       ├── deconvolutional_layer.c
    │   │       ├── deconvolutional_layer.h
    │   │       ├── demo.c
    │   │       ├── demo.h
    │   │       ├── detection_layer.c
    │   │       ├── detection_layer.h
    │   │       ├── dropout_layer.c
    │   │       ├── dropout_layer.h
    │   │       ├── dropout_layer_kernels.cu
    │   │       ├── gemm.c
    │   │       ├── gemm.h
    │   │       ├── gru_layer.c
    │   │       ├── gru_layer.h
    │   │       ├── im2col.c
    │   │       ├── im2col.h
    │   │       ├── im2col_kernels.cu
    │   │       ├── image.c
    │   │       ├── image.h
    │   │       ├── l2norm_layer.c
    │   │       ├── l2norm_layer.h
    │   │       ├── layer.c
    │   │       ├── layer.h
    │   │       ├── list.c
    │   │       ├── list.h
    │   │       ├── local_layer.c
    │   │       ├── local_layer.h
    │   │       ├── logistic_layer.c
    │   │       ├── logistic_layer.h
    │   │       ├── lstm_layer.c
    │   │       ├── lstm_layer.h
    │   │       ├── matrix.c
    │   │       ├── matrix.h
    │   │       ├── maxpool_layer.c
    │   │       ├── maxpool_layer.h
    │   │       ├── maxpool_layer_kernels.cu
    │   │       ├── network.c
    │   │       ├── network.h
    │   │       ├── normalization_layer.c
    │   │       ├── normalization_layer.h
    │   │       ├── option_list.c
    │   │       ├── option_list.h
    │   │       ├── parser.c
    │   │       ├── parser.h
    │   │       ├── region_layer.c
    │   │       ├── region_layer.h
    │   │       ├── reorg_layer.c
    │   │       ├── reorg_layer.h
    │   │       ├── rnn_layer.c
    │   │       ├── rnn_layer.h
    │   │       ├── route_layer.c
    │   │       ├── route_layer.h
    │   │       ├── shortcut_layer.c
    │   │       ├── shortcut_layer.h
    │   │       ├── softmax_layer.c
    │   │       ├── softmax_layer.h
    │   │       ├── stb_image.h
    │   │       ├── stb_image_write.h
    │   │       ├── tree.c
    │   │       ├── tree.h
    │   │       ├── upsample_layer.c
    │   │       ├── upsample_layer.h
    │   │       ├── utils.c
    │   │       ├── utils.h
    │   │       ├── yolo_layer.c
    │   │       └── yolo_layer.h
    │   ├── interface.yaml
    │   ├── launch
    │   │   ├── vision_yolo2_detect.launch
    │   │   └── vision_yolo3_detect.launch
    │   ├── package.xml
    │   ├── README.md
    │   └── src
    │       ├── gencolors.cpp
    │       ├── rect_class_score.h
    │       ├── vision_darknet_detect.cpp
    │       ├── vision_darknet_detect.h
    │       └── vision_darknet_detect_node.cpp
    ├── vision_dpm_ttic_detect
    │   ├── CHANGELOG.rst
    │   ├── CMakeLists.txt
    │   ├── data
    │   │   ├── car_2008.xml
    │   │   ├── car_comp.csv
    │   │   ├── car_part.csv
    │   │   ├── car_root.csv
    │   │   ├── car.xml
    │   │   ├── person_comp.csv
    │   │   ├── person_part.csv
    │   │   ├── person_root.csv
    │   │   └── person.xml
    │   ├── interface.yaml
    │   ├── launch
    │   │   └── vision_dpm_ttic_detect.launch
    │   ├── nodes
    │   │   └── vision_dpm_ttic_detect
    │   │       └── vision_dpm_ttic_detect.cpp
    │   └── package.xml
    ├── vision_lane_detect
    │   ├── CHANGELOG.rst
    │   ├── CMakeLists.txt
    │   ├── interface.yaml
    │   ├── nodes
    │   │   └── vision_lane_detect
    │   │       ├── utils.h
    │   │       └── vision_lane_detect.cpp
    │   └── package.xml
    ├── vision_segment_enet_detect
    │   ├── CHANGELOG.rst
    │   ├── CMakeLists.txt
    │   ├── include
    │   │   └── vision_segment_enet_detect.h
    │   ├── launch
    │   │   └── vision_segment_enet_detect.launch
    │   ├── nodes
    │   │   └── vision_segment_enet_detect
    │   │       ├── vision_segment_enet_detect.cpp
    │   │       └── vision_segment_enet_detect_node.cpp
    │   ├── package.xml
    │   └── README.md
    └── vision_ssd_detect
        ├── CHANGELOG.rst
        ├── CMakeLists.txt
        ├── include
        │   ├── gencolors.cpp
        │   ├── rect_class_score.h
        │   └── vision_ssd_detect.h
        ├── interface.yaml
        ├── launch
        │   └── vision_ssd_detect.launch
        ├── package.xml
        ├── README.md
        └── src
            ├── vision_ssd_detect.cpp
            └── vision_ssd_detect_node.cpp

32 directories, 221 files


```

